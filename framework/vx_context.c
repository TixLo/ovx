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

////////////////////////////////////////////////////////////////////////////////
// Internal Functions
////////////////////////////////////////////////////////////////////////////////
vx_bool ownIsValidContext(vx_context context)
{
    if (!context)
        return vx_false_e;
    if (context->ref.magic != VX_MAGIC)
        return vx_false_e;
    if (context->ref.type != VX_TYPE_CONTEXT)
        return vx_false_e;
    if (context->ref.context == NULL)
        return vx_false_e;
    return vx_true_e;
}

void ownPrintContext(vx_context context)
{
    vx_uint32 i=0;

    if (!ownIsValidReference((vx_reference)context))
        return;

    VX_PRINT(VX_DEBUG_INFO, "dump reference table (Total : %d)", context->ref_num);
    for (i=0 ; i<context->ref_num ; i++)
    {
        switch (context->ref_table[i]->type)
        {
            case VX_TYPE_GRAPH: 
                VX_PRINT(VX_DEBUG_INFO, "[%d] VX_TYOE_GRAPH", i);
                break;
            case VX_TYPE_IMAGE: 
                VX_PRINT(VX_DEBUG_INFO, "[%d] VX_TYPE_IMAGE", i);
                break;
            default:
                VX_PRINT(VX_DEBUG_WRN, "[%d] Unknown type", i);
                break;
        }
    } 
}

////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_context VX_API_CALL vxCreateContext()
{
    return vxCreateContextFromPlatform(NULL);
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseContext(vx_context *context)
{
    return vxReleaseContextFromPlatform(context);
}

VX_API_ENTRY vx_context VX_API_CALL vxGetContext(vx_reference reference)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryContext(vx_context context, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetContextAttribute(vx_context context, vx_enum attribute, const void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxHint(vx_reference reference, vx_enum hint, const void* data, vx_size data_size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxDirective(vx_reference reference, vx_enum directive)
{
    return 0;
}

VX_API_ENTRY vx_enum VX_API_CALL vxRegisterUserStruct(vx_context context, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxAllocateUserKernelId(vx_context context, vx_enum * pKernelEnumId)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxAllocateUserKernelLibraryId(vx_context context, vx_enum * pLibraryId)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetImmediateModeTarget(vx_context context, vx_enum target_enum, const char* target_string)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxGetStatus(vx_reference reference)
{
    return 0;
}
