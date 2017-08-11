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

/////////////////////////////////////////////////////////////////////////
// VX/vx_api.h
/////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_status VX_API_CALL vxLoadKernels(vx_context context, const vx_char *module)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxUnloadKernels(vx_context context, const vx_char *module)
{
    return 0;
}

VX_API_ENTRY vx_kernel VX_API_CALL vxGetKernelByName(vx_context context, const vx_char *name)
{
    return 0;
}

VX_API_ENTRY vx_kernel VX_API_CALL vxGetKernelByEnum(vx_context context, vx_enum kernelenum)
{
    int i=0, j=0;

    if (!ownIsValidReference((vx_reference)context))
    {
        VX_PRINT(VX_DEBUG_ERR, "context is a null pointer");
        return NULL;
    }

    ownSemWait(&((vx_reference)context)->lock);    

    for (i=0 ; i<VX_INT_MAX_NUM_TARGETS ; i++)
    {
        vx_target_t *target = &context->targets[i];
        for (j=0 ; j<target->num_kernels ; j++)
        {
            if (kernelenum == target->kernels[j].enumeration)
            {
                ownSemPost(&((vx_reference)context)->lock);    
                return &target->kernels[j];
            }
        }
    }    

    ownSemPost(&((vx_reference)context)->lock);    

    return NULL;
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryKernel(vx_kernel kernel, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseKernel(vx_kernel *kernel)
{
    return 0;
}

VX_API_ENTRY vx_kernel VX_API_CALL vxAddUserKernel(vx_context context,
                             const vx_char name[VX_MAX_KERNEL_NAME],
                             vx_enum enumeration,
                             vx_kernel_f func_ptr,
                             vx_uint32 numParams,
                             vx_kernel_validate_f validate,
                             vx_kernel_initialize_f init,
                             vx_kernel_deinitialize_f deinit)
{
    return 0;
}


VX_API_ENTRY vx_status VX_API_CALL vxFinalizeKernel(vx_kernel kernel)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxAddParameterToKernel(vx_kernel kernel, vx_uint32 index, vx_enum dir, vx_enum data_type, vx_enum state)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxRemoveKernel(vx_kernel kernel)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxSetKernelAttribute(vx_kernel kernel, vx_enum attribute, const void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_parameter VX_API_CALL vxGetKernelParameterByIndex(vx_kernel kernel, vx_uint32 index)
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////
// VX/vx_compatibility.h
/////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_kernel VX_API_CALL vxAddKernel(vx_context context,
                             const vx_char name[VX_MAX_KERNEL_NAME],
                             vx_enum enumeration,
                             vx_kernel_f func_ptr,
                             vx_uint32 numParams,
                             vx_kernel_input_validate_f input,
                             vx_kernel_output_validate_f output,
                             vx_kernel_initialize_f init,
                             vx_kernel_deinitialize_f deinit)
{
    return 0;
}
