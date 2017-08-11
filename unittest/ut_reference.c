/* Copyright Statement:
 *
 * Copyright (C) 2017 Tix Lo All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <VX/vx.h>
#include <vx_internal.h>

int test_vxreference_init(void)
{
    int ret = 0;

    vx_reference ref = (vx_reference)VX_MEM_CALLOC(1, sizeof(vx_reference_t)); 
    if (ref == NULL)
        return ret;

    ownInitReference(ref, NULL, VX_TYPE_CONTEXT, NULL);

    ret = vxRetainReference(ref); //external_count -> 1, internal_count -> 0
    if (ret != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    ret = (ref->magic == VX_MAGIC) ? 1 : 0 ;

    vxReleaseReference(&ref);
    return ret;
}

int test_vxreference_counting(void)
{
    vx_status status = VX_SUCCESS;
    vx_uint32 count = 0;

    vx_reference ref = (vx_reference)VX_MEM_CALLOC(1, sizeof(vx_reference_t)); 
    if (ref == NULL)
        return -1;

    ownInitReference(ref, NULL, VX_TYPE_CONTEXT, NULL);

    status = vxRetainReference(ref); //external_count -> 1, internal_count -> 0
    if (status != VX_SUCCESS)
        goto COUNTING_BAD;

    count = ownIncrementReference(ref, VX_EXTERNAL); //external_count -> 2, internal_count -> 0
    if (count <= 0)
        goto COUNTING_BAD;

    count = ownIncrementReference(ref, VX_INTERNAL); //external_count -> 2, internal_count -> 1
    if (count <= 0)
        goto COUNTING_BAD;

    count = ownIncrementReference(ref, VX_BOTH); //external_count -> 3, internal_count -> 2
    if (count <= 0)
        goto COUNTING_BAD;

    count = ownDecrementReference(ref, VX_EXTERNAL); //external_count -> 2, internal_count -> 2
    if (count <= 0)
        goto COUNTING_BAD;

    count = ownDecrementReference(ref, VX_INTERNAL); //external_count -> 2, internal_count -> 1
    if (count <= 0)
        goto COUNTING_BAD;

    count = ownDecrementReference(ref, VX_BOTH); //external_count -> 1, internal_count -> 0
    if (count <= 0)
        goto COUNTING_BAD;

    vx_uint32 total_count = ownTotalReferenceCount(ref);
    if (total_count != 1)
    {
        status = VX_ERROR_INVALID_REFERENCE;
        goto COUNTING_BAD;
    }

    goto COUNTING_END;

COUNTING_BAD:
    status = -1;

COUNTING_END:

    vxReleaseReference(&ref);
    return (status == VX_SUCCESS) ? 1 : 0 ;
}

int test_vxreference_query_count(void)
{
    vx_status status = VX_SUCCESS;
    vx_uint32 count = 0;

    vx_reference ref = (vx_reference)VX_MEM_CALLOC(1, sizeof(vx_reference_t)); 
    if (ref == NULL)
        return -1;

    ownInitReference(ref, NULL, VX_TYPE_CONTEXT, NULL);
    status = vxRetainReference(ref); //external_count -> 1, internal_count -> 0
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    status = vxQueryReference(ref, VX_REF_ATTRIBUTE_COUNT, (void*)&count, sizeof(vx_uint32));
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }
 
    if (count != 1)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    vxReleaseReference(&ref);
    return 1;
}

int test_vxreference_query_type(void)
{
    vx_status status = VX_SUCCESS;
    vx_enum type = 0;

    vx_reference ref = (vx_reference)VX_MEM_CALLOC(1, sizeof(vx_reference_t)); 
    if (ref == NULL)
        return -1;

    ownInitReference(ref, NULL, VX_TYPE_CONTEXT, NULL);
    status = vxRetainReference(ref); //external_count -> 1, internal_count -> 0
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    status = vxQueryReference(ref, VX_REF_ATTRIBUTE_TYPE, (void*)&type, sizeof(vx_enum));
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }
 
    if (type != VX_TYPE_CONTEXT)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    vxReleaseReference(&ref);
    return 1;
}

int test_vxreference_query_name(void)
{
    vx_status status = VX_SUCCESS;
    vx_char *name = NULL;

    vx_reference ref = (vx_reference)VX_MEM_CALLOC(1, sizeof(vx_reference_t)); 
    if (ref == NULL)
        return -1;

    ownInitReference(ref, NULL, VX_TYPE_CONTEXT, NULL);
    status = vxRetainReference(ref); //external_count -> 1, internal_count -> 0
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    status = vxSetReferenceName(ref, "query_test");
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }

    status = vxQueryReference(ref, VX_REF_ATTRIBUTE_NAME, (void*)&name, sizeof(vx_char*));
    if (status != VX_SUCCESS)
    {
        vxReleaseReference(&ref);
        return 0;
    }
 
    if (strcmp(name, "query_test"))
    {
        vxReleaseReference(&ref);
        return 0;
    }

    vxReleaseReference(&ref);
    return 1;
}
