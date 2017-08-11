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

///////////////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////////////
vx_status ownLoadTarget(vx_context_t *context, vx_target_funcs_t *target_func)
{
    int i=0;
    vx_target_t *target;

    if (!context || !target_func)
    {
        VX_PRINT(VX_DEBUG_ERR, "context or target_func is NULL pointer!");
        return VX_ERROR_INVALID_PARAMETERS;
    }

    //
    // find a empty slut for targets
    //
    for (i=0 ; i<VX_TARGET_PRIORITY_MAX ; i++)
    {
        if (context->targets[i].funcs.init == NULL)
        {
            VX_PRINT(VX_DEBUG_INFO, "found a empty slut [%d]", i);
            target = &context->targets[i];
            break;
        }
    }

    //
    // initialize specific target 
    //
    strncpy(target->funcs.name, target_func->name, strlen(target_func->name));
    strncpy(target->funcs.author, target_func->author, strlen(target_func->author));
    strncpy(target->funcs.description, target_func->description, strlen(target_func->description));
    target->funcs.init       = target_func->init;
    target->funcs.deinit     = target_func->deinit;
    target->funcs.supports   = target_func->supports;
    target->funcs.process    = target_func->process;
    target->funcs.verify     = target_func->verify;
    target->funcs.addkernel  = target_func->addkernel;

    //
    // check target_func function pointer
    //
    if (!target->funcs.init || 
        !target->funcs.deinit || 
        !target->funcs.supports ||
        !target->funcs.process || 
        !target->funcs.verify || 
        !target->funcs.addkernel)
    {
        VX_PRINT(VX_DEBUG_ERR, "invalid implementation of vx_interface!");
        return VX_ERROR_INVALID_MODULE;
    }

    VX_PRINT(VX_DEBUG_INFO, "Load Target");
    VX_PRINT(VX_DEBUG_INFO, "\tName        : %s", target->funcs.name);
    VX_PRINT(VX_DEBUG_INFO, "\tAuthor      : %s", target->funcs.author);
    VX_PRINT(VX_DEBUG_INFO, "\tDescription : %s", target->funcs.description);

    //
    // call initial function of target
    //
    if (target->funcs.init(target) != VX_SUCCESS)
    {
        VX_PRINT(VX_DEBUG_ERR, "cannot initialize target");
        return VX_ERROR_INVALID_MODULE;
    }
    return VX_SUCCESS;
}
