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
#include "vx_internal.h"

#define VX_BAD_MAGIC    0x0BAD0BAD

static vx_destructor_t destructors[] = 
{
    {VX_TYPE_CONTEXT        ,NULL},
    {VX_TYPE_GRAPH          ,&ownDestructGraph},
};

////////////////////////////////////////////////////////////////////////////////
// Internal Functions
////////////////////////////////////////////////////////////////////////////////
void ownInitReference(vx_reference ref, vx_context context, vx_enum type, vx_reference scope)
{
    if (!ref)
    {
        VX_PRINT(VX_DEBUG_ERR, "reference object is a NULL pointer");
        return;
    }

    ref->platform       = (context) ? context->ref.platform : NULL ;    
    ref->magic          = VX_MAGIC;
    ref->type           = type;
    ref->context        = context;
    ref->scope          = scope;
    ref->external_count = 0;
    ref->internal_count = 0;
    ref->name[0]        = 0;

    ownCreateSem(&ref->lock, 1);
}

vx_status ownReleaseReferenceInt(vx_reference *ref_ptr, vx_enum reftype)
{
    int i = 0;
    vx_status status = VX_SUCCESS;
    vx_destructor_f destructor = NULL;
    
    vx_reference ref = (ref_ptr) ? *ref_ptr : NULL ;

    if (!ownIsValidReference(ref))
        return VX_ERROR_INVALID_REFERENCE;

    if (ownDecrementReference(ref, reftype) > 0)
        return status;

    //
    // find its own destructor
    //
    for (i=0 ; i<dimof(destructors) ; i++)
    {
        if (ref->type == destructors[i].type)
        {
            destructor = destructors[i].destructor;
            break;
        }
    }

    //
    // call destructor if need
    //
    if (destructor)
        destructor(ref);

    ref->magic = VX_BAD_MAGIC;
    ownDestroySem(&ref->lock);

    VX_MEM_FREE((void*)ref);

    return status;
}

vx_bool ownIsValidReference(vx_reference ref)
{
    vx_bool valid = vx_false_e;
    if (ref == NULL)
    {
        VX_PRINT(VX_DEBUG_ERR, "ref object is a NULL pointer");
        return valid;
    }

    if (ref->magic == VX_MAGIC)
    {
        valid = vx_true_e;
    }

    return valid;
}

////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_status VX_API_CALL vxQueryReference(vx_reference ref, vx_enum attribute, void *ptr, vx_size size)
{
    vx_status status = VX_SUCCESS;
    if (!ownIsValidReference(ref))
    {
        return VX_ERROR_INVALID_REFERENCE;
    }

    switch(attribute)
    {
        case VX_REF_ATTRIBUTE_COUNT:
            if (VX_CHECK_SIZE_PARAM(size, vx_uint32))
                *(vx_uint32 *)ptr = ref->external_count;
            else
                status = VX_ERROR_INVALID_PARAMETERS;
            break;

        case VX_REF_ATTRIBUTE_TYPE:
            if (VX_CHECK_SIZE_PARAM(size, vx_enum))
                *(vx_enum *)ptr = ref->type;
            else
                status = VX_ERROR_INVALID_PARAMETERS;
            break;

        case VX_REF_ATTRIBUTE_NAME:
            if (VX_CHECK_SIZE_PARAM(size, vx_char*))
                *(vx_char **)ptr = &ref->name[0];
            else
                status = VX_ERROR_INVALID_PARAMETERS;
            break;
    
        default:
            status = VX_ERROR_NOT_SUPPORTED;
            break;
    }
    
    return status;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseReference(vx_reference* ref_ptr)
{
    vx_status status = VX_ERROR_INVALID_REFERENCE;

    vx_reference ref = (ref_ptr) ? *ref_ptr : NULL ; 
    if (!ownIsValidReference(ref))
    {
        return status;
    }

    switch (ref->type)
    {
        case VX_TYPE_CONTEXT:
            status = vxReleaseContext((vx_context*)ref_ptr);
            break;
        default:
            break;
    }

    return status;
}

VX_API_ENTRY vx_status VX_API_CALL vxRetainReference(vx_reference ref)
{
    vx_status status = VX_SUCCESS;
    if (!ownIsValidReference(ref))
    {
        return VX_ERROR_INVALID_REFERENCE;
    }
    
    ownSemWait(&ref->lock);
    ref->external_count++;
    ownSemPost(&ref->lock);
    
    return status;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetReferenceName(vx_reference ref, const vx_char *name)
{
    vx_status status = VX_SUCCESS;
    if (!ownIsValidReference(ref))
    {
        return VX_ERROR_INVALID_REFERENCE;
    }
    
    ownSemWait(&ref->lock);
    strncpy(ref->name, name, strnlen(name, VX_MAX_REFERENCE_NAME));
    ownSemPost(&ref->lock);
    
    return status;
}

vx_uint32 ownIncrementReference(vx_reference ref, vx_enum reftype)
{
    vx_uint32 count = 0u;
    if (!ownIsValidReference(ref))
    {
        return count;
    }

    ownSemWait(&ref->lock);

    if (reftype == VX_EXTERNAL || reftype == VX_BOTH)
        ref->external_count++;
    if (reftype == VX_INTERNAL || reftype == VX_BOTH)
        ref->internal_count++;
    count = ref->internal_count + ref->external_count;

    VX_PRINT(VX_DEBUG_INFO, "incremented total teference count to %u", count);
    ownSemPost(&ref->lock);

    return count;
}

vx_uint32 ownDecrementReference(vx_reference ref, vx_enum reftype)
{
    vx_uint32 count = 0u;
    if (!ownIsValidReference(ref))
    {
        return count;
    }

    ownSemWait(&ref->lock);
    if (reftype == VX_EXTERNAL || reftype == VX_BOTH)
    {
        if (ref->external_count == 0)
        {
            VX_PRINT(VX_DEBUG_ERR, "external reference count is ZERO !");
        }
        else
        {
            ref->external_count--;
        }
    }
    if (reftype == VX_INTERNAL || reftype == VX_BOTH)
    {
        if (ref->internal_count == 0)
        {
            VX_PRINT(VX_DEBUG_ERR, "internal reference count is ZERO !");
        }
        else
        {
            ref->internal_count--;
        }
    }

    count = ref->external_count + ref->internal_count;
    VX_PRINT(VX_DEBUG_INFO, "decreased total reference count to %u", count);
    ownSemPost(&ref->lock);
    return count;
}

vx_uint32 ownTotalReferenceCount(vx_reference ref)
{
    vx_uint32 count = 0u;
    if (!ownIsValidReference(ref))
    {
        return count;
    }

    ownSemWait(&ref->lock);
    count = ref->external_count + ref->internal_count;
    ownSemPost(&ref->lock);
    return count;
}


