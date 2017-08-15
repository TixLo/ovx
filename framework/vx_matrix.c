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

/* registry different size for each data type */
typedef struct
{
    vx_enum data_type;
    vx_size size;
}vx_data_type_size_t;

static vx_data_type_size_t type_sizes[] = 
{
    {VX_TYPE_INT8           ,sizeof(vx_uint8)       },
    {VX_TYPE_UINT8          ,sizeof(vx_uint8)       },
    {VX_TYPE_INT16          ,sizeof(vx_uint16)      },
    {VX_TYPE_UINT16         ,sizeof(vx_uint16)      },
    {VX_TYPE_INT32          ,sizeof(vx_uint32)      },
    {VX_TYPE_UINT32         ,sizeof(vx_uint32)      },
    {VX_TYPE_FLOAT32        ,sizeof(vx_uint32)      },
    {VX_TYPE_INT64          ,sizeof(vx_uint64)      },
    {VX_TYPE_UINT64         ,sizeof(vx_uint64)      },
    {VX_TYPE_FLOAT64        ,sizeof(vx_uint64)      },
};

/////////////////////////////////////////////////////////////////////////
// vx_internal.h
/////////////////////////////////////////////////////////////////////////
void ownDestructMatrix(vx_reference ref)
{
    VX_PRINT(VX_DEBUG_INFO, "ownDestructMatrix");
}

/////////////////////////////////////////////////////////////////////////
// VX/vx_api.h
/////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_matrix VX_API_CALL vxCreateMatrix(vx_context context, vx_enum data_type, vx_size columns, vx_size rows)
{
    vx_matrix matrix = NULL;
    vx_size size = 0;
    vx_uint32 i = 0;

    if (!ownIsValidReference((vx_reference)context))
    {
        VX_PRINT(VX_DEBUG_WRN, "context is a null pointer");
        return NULL;
    }

    for (i=0 ; i<dimof(type_sizes) ; i++)
    {
        if (data_type == type_sizes[i].data_type)
        {
            size = type_sizes[i].size;
            break;
        }
    }

    if (size == 0)
    {
        VX_PRINT(VX_DEBUG_WRN, "invalied data type");
        return NULL;
    }

    if (columns == 0 || rows == 0)
    {
        VX_PRINT(VX_DEBUG_WRN, "invalied dimensions to matrix");
        return NULL;
    }

    matrix = (vx_matrix)ownCreateRef(context, VX_TYPE_MATRIX, VX_EXTERNAL, &context->ref);
    if (!matrix)
    {
        VX_PRINT(VX_DEBUG_WRN, "failed to create vx_matrix object");
        return NULL;
    }

    matrix->data_type = data_type;
    matrix->cols = columns;
    matrix->rows = rows;
    matrix->origin.x = (vx_uint32)(columns / 2);
    matrix->origin.y = (vx_uint32)(rows / 2);
    matrix->pattern = VX_PATTERN_OTHER;
    matrix->memory.ndims = 2;
    matrix->memory.nptrs = 1;
    matrix->memory.dims[0][0] = (vx_int32)size;
    matrix->memory.dims[0][1] = (vx_int32)(columns*rows);

    return matrix;
}

VX_API_ENTRY vx_status VX_API_CALL vxReleaseMatrix(vx_matrix *matrix)
{
    return ownReleaseReferenceInt((vx_reference*)matrix, VX_EXTERNAL);
}

VX_API_ENTRY vx_status VX_API_CALL vxQueryMatrix(vx_matrix mat, vx_enum attribute, void *ptr, vx_size size)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxCopyMatrix(vx_matrix matrix, void *user_ptr, vx_enum usage, vx_enum user_mem_type)
{
    return 0;
}

VX_API_ENTRY vx_matrix VX_API_CALL vxCreateMatrixFromPattern(vx_context context, vx_enum pattern, vx_size columns, vx_size rows)
{
    return 0;
}
/////////////////////////////////////////////////////////////////////////
// VX/vx_compatibility.h
/////////////////////////////////////////////////////////////////////////
VX_API_ENTRY vx_status VX_API_CALL vxReadMatrix(vx_matrix mat, void *array)
{
    return 0;
}

VX_API_ENTRY vx_status VX_API_CALL vxWriteMatrix(vx_matrix mat, const void *array)
{
    return 0;
}
