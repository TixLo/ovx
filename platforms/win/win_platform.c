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

/* initialized flag */
static vx_bool platform_inited = vx_false_e;

/* mutex lock for context protection */
static vx_sem_t context_lock;

static void vxInitPlatform(void)
{
    if (platform_inited == vx_true_e)
        return;

    platform_inited = vx_true_e;

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
    vxInitPlatform();

    vx_context context = (vx_context)VX_MEM_CALLOC(1, sizeof(vx_context_t));
    if (!context)
        return NULL;

    return context;
}
