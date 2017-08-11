/* Copyright Statement:
 *
 * Copyright (C) 2017 Tix Lo All rights reserved.
 * 
 * Permission is hereby granted, ownMemFree of charge, to any person obtaining a copy
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

/* initialized flag */
static vx_bool platform_inited = vx_false_e;

/* mutex lock for context protection */
static vx_sem_t context_lock;

/* extern function pointer of specific target from targets/XXXX/vx_interface.c */
#if defined(HAVE_C_MODEL)
extern vx_target_funcs_t openvx_c_model_target;
#endif

#if defined(HAVE_OPENCL)
extern vx_target_funcs_t openvx_opencl_target;
#endif

/* define all build-in targets, e.g. C-Model, OpenCL , ...etc. */
static vx_target_funcs_t *buildin_targets[] = 
{
#if defined(HAVE_C_MODEL)
    &openvx_c_model_target,
#endif
#if defined(HAVE_OPENCL)
    &openvx_opencl_target,
#endif
    NULL
};

///////////////////////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////////////////////
static void vxInitPlatform(void)
{
    if (platform_inited == vx_true_e)
        return;

    platform_inited = vx_true_e;

    vx_set_debug_level_from_env();

    ownCreateSem(&context_lock, 1);
}

///////////////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////////////
vx_status VX_API_CALL vxIcdGetPlatforms(vx_size capacity, vx_platform platform[], vx_size * pNumItems)
{
    return 0;
}

vx_status VX_API_CALL vxQueryPlatform(vx_platform platform, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

vx_context VX_API_CALL vxCreateContextFromPlatform(vx_platform platform)
{
    int i=0;

    vxInitPlatform();

    ownSemWait(&context_lock);

    vx_context context = (vx_context)VX_MEM_CALLOC(1, sizeof(vx_context_t));
    if (!context)
    {
        VX_PRINT(VX_DEBUG_ERR, "Out of memory!");
        ownSemPost(&context_lock);
        return NULL;
    }

    //
    // Initialize variables of vx_context
    //
    context->ref.platform = platform;
    context->log_cb = NULL;
    context->log_enabled = vx_false_e;
    context->log_reentrant = vx_false_e;
    ownCreateSem(&context->log_lock, 1);

    ownInitReference(&context->ref, context, VX_TYPE_CONTEXT, NULL); 
    ownIncrementReference(&context->ref, VX_EXTERNAL);

    //
    // Initialize image formats
    //
    if (ownInitImageFormats(context) != VX_SUCCESS)
    {
        VX_PRINT(VX_DEBUG_ERR, "cannot initialize image formats");
        ownSemPost(&context_lock);
        vxReleaseContext(&context);
        return NULL;
    }

    //
    // Load all targets
    //
    for (i=0 ; buildin_targets[i] != NULL ; i++)
    {
        vx_target_funcs_t *target_func = buildin_targets[i];
        vx_status ret = ownLoadTarget(context, target_func);
        if (ret != VX_SUCCESS)
            continue;
    }

    ownSemPost(&context_lock);
    return context;
}

vx_status VX_API_CALL vxReleaseContextFromPlatform(vx_context *context_ptr)
{
    vx_status status = VX_SUCCESS;
    vx_context context = (context_ptr) ? *context_ptr : NULL ; 
    ownSemWait(&context_lock);

    if (!ownIsValidReference((vx_reference)context))
    {
        return VX_ERROR_INVALID_REFERENCE;
    } 

    if (ownDecrementReference((vx_reference)context, VX_EXTERNAL) == 0)
    {
        //
        // TODO:FIXED ME!!
        // Deregister any log callbacks
        //
        ownDestroySem(&context->log_lock);

        //
        // TODO:FIXED ME!!
        // Unload all loaded modules
        //

        //
        // Release context resource
        //
        ownDestroySem(&((vx_reference)context)->lock);
        VX_MEM_FREE((void *)context);
        context_ptr = NULL;

        VX_PRINT(VX_DEBUG_INFO, "release context object");
    }
    else
    {
        VX_PRINT(VX_DEBUG_INFO, "context still has a %u holder", ownTotalReferenceCount((vx_reference)context));
    }

    ownSemPost(&context_lock);
    
    return status;
}
