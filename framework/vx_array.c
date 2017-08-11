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
VX_API_ENTRY vx_array VX_API_CALL vxCreateArray(vx_context context, vx_enum item_type, vx_size capacity)
{
    return 0;
}

VX_API_ENTRY vx_array VX_API_CALL vxCreateVirtualArray(vx_graph graph, vx_enum item_type, vx_size capacity)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseArray(vx_array *arr)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryArray(vx_array arr, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxAddArrayItems(vx_array arr, vx_size count, const void *ptr, vx_size stride)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxTruncateArray(vx_array arr, vx_size new_num_items)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxCopyArrayRange(vx_array array, vx_size range_start, vx_size range_end, vx_size user_stride, void *user_ptr, vx_enum usage, vx_enum user_mem_type)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxMapArrayRange(vx_array array, vx_size range_start, vx_size range_end, vx_map_id *map_id, vx_size *stride, void **ptr, vx_enum usage, vx_enum mem_type, vx_uint32 flags)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxUnmapArrayRange(vx_array array, vx_map_id map_id)
{
    return 0;
}
/////////////////////////////////////////////////////////////////////////
// VX/vx_compatibility.h
/////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_status VX_API_CALL vxAccessArrayRange(vx_array arr, vx_size start, vx_size end, vx_size *stride, void **ptr, vx_enum usage)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxCommitArrayRange(vx_array arr, vx_size start, vx_size end, const void *ptr)
{
    return 0;
}
