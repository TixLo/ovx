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
#include <VX/vx.h>
#include <vx_internal.h>

int test_vxmatrix_create(void)
{
    vx_status status = VX_SUCCESS;
    vx_context context = vxCreateContext();
    if (context == NULL)
        return 0;

    vx_matrix matrix = vxCreateMatrix(context, VX_TYPE_INT8, 2, 2);

    if (!matrix)
    {
        vxReleaseContext(&context);
        return 0;
    }

    vxReleaseMatrix(&matrix);
    vxReleaseContext(&context);
    return 1;
}

int test_vxmatrix_readwrite(void)
{
    int i=0, j=0, ret=1;
    vx_int32 buf[2][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    vx_int32 out[2][4];
    vx_status status = VX_SUCCESS;
    vx_context context = vxCreateContext();
    if (context == NULL)
        return 0;

    vx_matrix matrix = vxCreateMatrix(context, VX_TYPE_INT32, 2, 4);

    if (!matrix)
    {
        vxReleaseContext(&context);
        return 0;
    }
    
    if (vxWriteMatrix(matrix, (void*)buf) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    if (vxReadMatrix(matrix, (void*)out) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    for (i=0 ; i<2 ; i++)
    {
        for (j=0 ; j<4 ; j++)
        {
            //VX_PRINT(VX_DEBUG_INFO, "[%d][%d], buf:%d, out:%d", i, j, buf[i][j], out[i][j]);
            if (buf[i][j] != out[i][j])
            {
                ret = 0;
                break;
            }
        }
    }

    vxReleaseMatrix(&matrix);
    vxReleaseContext(&context);
    return ret;
}

int test_vxmatrix_query(void)
{
    vx_size rows, cols, size;
    vx_enum type, pattern;
    vx_coordinates2d_t coord;
    vx_status status = VX_SUCCESS;
    vx_context context = vxCreateContext();
    if (context == NULL)
        return 0;

    vx_matrix matrix = vxCreateMatrix(context, VX_TYPE_INT32, 2, 4);

    if (!matrix)
    {
        vxReleaseContext(&context);
        return 0;
    }

    // check type    
    if (vxQueryMatrix(matrix, VX_MATRIX_TYPE, &type, sizeof(vx_enum)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (type != VX_TYPE_INT32)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    // check rows    
    if (vxQueryMatrix(matrix, VX_MATRIX_ROWS, &rows, sizeof(vx_size)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (rows != 4)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    // check cols    
    if (vxQueryMatrix(matrix, VX_MATRIX_COLUMNS, &cols, sizeof(vx_size)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (cols != 2)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    // check size    
    if (vxQueryMatrix(matrix, VX_MATRIX_SIZE, &size, sizeof(vx_size)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (size != 4 * 2 * 4)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    // check origin    
    if (vxQueryMatrix(matrix, VX_MATRIX_ORIGIN, &coord, sizeof(vx_coordinates2d_t)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (coord.x != 1 || coord.y != 2)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    // check pattern    
    if (vxQueryMatrix(matrix, VX_MATRIX_PATTERN, &pattern, sizeof(vx_enum)) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }
    if (pattern != VX_PATTERN_OTHER)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    vxReleaseMatrix(&matrix);
    vxReleaseContext(&context);
    return 1;
}

int test_vxmatrix_copy(void)
{
    int i=0, j=0, ret=1;
    vx_int32 buf[2][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    vx_int32 out[2][4];
    vx_status status = VX_SUCCESS;
    vx_context context = vxCreateContext();
    if (context == NULL)
        return 0;

    vx_matrix matrix = vxCreateMatrix(context, VX_TYPE_INT32, 2, 4);

    if (!matrix)
    {
        vxReleaseContext(&context);
        return 0;
    }
    
    if (vxCopyMatrix(matrix, (void*)buf, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    if (vxCopyMatrix(matrix, (void*)out, VX_READ_ONLY, VX_MEMORY_TYPE_HOST) != VX_SUCCESS)
    {
        vxReleaseMatrix(&matrix);
        vxReleaseContext(&context);
        return 0;
    }

    for (i=0 ; i<2 ; i++)
    {
        for (j=0 ; j<4 ; j++)
        {
            //VX_PRINT(VX_DEBUG_INFO, "[%d][%d], buf:%d, out:%d", i, j, buf[i][j], out[i][j]);
            if (buf[i][j] != out[i][j])
            {
                ret = 0;
                break;
            }
        }
    }

    vxReleaseMatrix(&matrix);
    vxReleaseContext(&context);
    return ret;
}
