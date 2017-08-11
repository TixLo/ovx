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

VX_API_ENTRY void VX_API_CALL vxAddLogEntry(vx_reference ref, vx_status status, const char *message, ...)
{
    va_list ap;
    vx_context context = NULL;
    vx_char string[VX_MAX_LOG_MESSAGE_LEN] = {0};
    vx_bool console_output = vx_true_e;

    if (!ownIsValidReference(ref))
        return;

    context = (vx_context)ref;
    if (!ownIsValidContext(context))
        return;

    if (context->log_cb == NULL || context->log_enabled == vx_false_e)
        return;

    va_start(ap, message);
    vsnprintf(string, VX_MAX_LOG_MESSAGE_LEN, message, ap);
    va_end(ap);

    if (context->log_reentrant)
        ownSemWait(&context->log_lock);

    context->log_cb(context, ref, status, string);

    if (context->log_reentrant)
        ownSemPost(&context->log_lock);
}

VX_API_ENTRY void VX_API_CALL vxRegisterLogCallback(vx_context context, vx_log_callback_f callback, vx_bool reentrant)
{
    if (!ownIsValidReference((vx_reference)context))
    {
        VX_PRINT(VX_DEBUG_WRN, "context is a null pointer");
        return;
    }

    ownSemWait(&((vx_reference)context)->lock); 

    context->log_cb = callback;
    context->log_reentrant = reentrant;
    context->log_enabled = (callback != NULL) ? vx_true_e : vx_false_e ;    

    ownSemPost(&((vx_reference)context)->lock); 
}
