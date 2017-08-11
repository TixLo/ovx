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
#include "vx_interface.h"

///////////////////////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////////////////////
static vx_status vxCModelInit(vx_target target)
{
    return publishCModelKernels(target);
}

static vx_status vxCModelDeinit(vx_target target)
{
    VX_PRINT(VX_DEBUG_INFO,"vxCModelDeinit");
    return 0;
}

static vx_status vxCModelSupports(vx_target target,
                                  vx_char targetName[VX_MAX_TARGET_NAME],
                                  vx_char kernelName[VX_MAX_KERNEL_NAME],
                                  vx_uint32 *pIndex)
{
    VX_PRINT(VX_DEBUG_INFO,"vxCModelSupports");
    return 0;
}

static vx_action vxCModelProcess(vx_target target, vx_node_t *nodes[], vx_size startIndex, vx_size numNodes)
{
    VX_PRINT(VX_DEBUG_INFO,"vxCModelProcess");
    return 0;
}

static vx_status vxCModelVerify(vx_target target, vx_node_t *node)
{
    VX_PRINT(VX_DEBUG_INFO,"vxCModelVerify");
    return 0;
}

static vx_kernel vxCModelAddKernel(vx_target target,
                                   vx_char name[VX_MAX_KERNEL_NAME],
                                   vx_enum enumeration,
                                   vx_kernel_f func_ptr,
                                   vx_uint32 numParams,
                                   vx_kernel_validate_f validate,
                                   vx_kernel_input_validate_f input,
                                   vx_kernel_output_validate_f output,
                                   vx_kernel_initialize_f initialize,
                                   vx_kernel_deinitialize_f deinitialize)
{
    VX_PRINT(VX_DEBUG_INFO,"vxCModelAddKernel");
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// EXPORT FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
vx_target_funcs_t openvx_c_model_target = 
{
    "openvx-c_model",
    "Tix Lo",
    "Kernels with C Model implementation",
    (vx_target_init_f)     &vxCModelInit,
    (vx_target_deinit_f)   &vxCModelDeinit,
    (vx_target_supports_f) &vxCModelSupports,
    (vx_target_process_f)  &vxCModelProcess,
    (vx_target_verify_f)   &vxCModelVerify,
    (vx_target_addkernel_f)&vxCModelAddKernel
};
