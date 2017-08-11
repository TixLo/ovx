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

VX_API_ENTRY vx_object_array VX_API_CALL vxCreateObjectArray(vx_context context, vx_reference exemplar, vx_size count)
{
    return 0;
}

VX_API_ENTRY vx_object_array VX_API_CALL vxCreateVirtualObjectArray(vx_graph graph, vx_reference exemplar, vx_size count)
{
    return 0;
}

VX_API_ENTRY vx_reference VX_API_CALL vxGetObjectArrayItem(vx_object_array arr, vx_uint32 index)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseObjectArray(vx_object_array *arr)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryObjectArray(vx_object_array arr, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}
