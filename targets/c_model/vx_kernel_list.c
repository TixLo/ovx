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
#include "vx_kernel_list.h"

#define AIN                                         (OVX_KERNEL_ARG_IN)
#define AOUT                                        (OVX_KERNEL_ARG_OUT)
#define AOPTIN                                      (OVX_KERNEL_ARG_IN | OVX_KERNEL_ARG_OPTIONAL)
#define AOPTOUT                                     (OVX_KERNEL_ARG_OUT | OVX_KERNEL_ARG_OPTIONAL)

#define AIN_AOUT                                    {AIN, AOUT}

#define ATYPE_II                                    {VX_TYPE_IMAGE, VX_TYPE_IMAGE}

typedef struct _buildin_kernel{
    /* id for retrieving a specific kernel */
    vx_enum id;

    /* execution function */
    vx_kernel_f func;

    /* kernel name */
    vx_char* name;

    /* flags for different device type */
    vx_uint32 flags;

    /* input and output config */
    vx_uint8 arg_conf[OVX_KERNEL_MAX_ARGS];

    /* declaration type of input and output */
    vx_enum arg_type[OVX_KERNEL_MAX_ARGS];
}buildin_kernel_t;

/*
 * the naming rule of kernel executed function is according to khronos definitions in vx_api.h
 * the name of default kernel is org.khronos.openvx.XXXX,
 */
#define ORG_KERNEL(id, name, conf, type)    \
    { \
        id, \
        org_kernel_##name, \
        "org.khronos.openvx."#name, \
        OVX_KERNEL_CONF_DEVICE_CPU, \
        conf, \
        type, \
    }

//
// list of all built-in kernels
//
static buildin_kernel_t kernel_lists[] = 
{
    //
    // Common kernels in OpenVX 1.1 Specification.
    //
    ORG_KERNEL(VX_KERNEL_COLOR_CONVERT ,color_convert , AIN_AOUT , ATYPE_II)
};

static size_t buildin_kernel_count = sizeof(kernel_lists) / sizeof(kernel_lists[0]);

///////////////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////////////
vx_status publishCModelKernels(vx_target target)
{
    int i=0;

    for (i=0 ; i<buildin_kernel_count ; i++)
    {
        //get curr list item
        buildin_kernel_t *item = &kernel_lists[i];
        VX_PRINT(VX_DEBUG_INFO, "name : %s", item->name);

        // get a empty slot
        vx_kernel_t *kernel = &target->kernels[target->num_kernels];
        ownInitReference(&kernel->ref, NULL, VX_TYPE_KERNEL, NULL);
        ownIncrementReference(&kernel->ref, VX_INTERNAL);

        // setup kernel
        strncpy(kernel->name, item->name, VX_MAX_REFERENCE_NAME);
        kernel->enumeration     = item->id;
        kernel->func            = item->func;

        // increase number of kernel
        target->num_kernels++;
        if (target->num_kernels >= VX_MAX_KERNELS)
        {
            VX_PRINT(VX_DEBUG_WRN, "slots are too few to load all kernels");
            break;
        }
    }

    return VX_SUCCESS;
}

