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

int test_vxmemory_alloc(void)
{
    vx_char *buf1 = (vx_char*)VX_MEM_MALLOC(32);
    if (buf1 == NULL)
        return 0;

    vx_char *buf2 = (vx_char*)VX_MEM_CALLOC(1, 16);
    if (buf2 == NULL)
        return 0;

    vx_uint32 total = ownMemCurrUsage();
    if (total != 48)
        return 0;

    VX_MEM_FREE(buf1);
    VX_MEM_FREE(buf2);

    return 1;
}

int test_vxmemory_alloc_free(void)
{
    vx_char *buf1 = (vx_char*)VX_MEM_MALLOC(32);
    if (buf1 == NULL)
        return 0;

    vx_char *buf2 = (vx_char*)VX_MEM_CALLOC(1, 16);
    if (buf2 == NULL)
        return 0;

    vx_char *buf3 = (vx_char*)VX_MEM_CALLOC(3, 8);
    if (buf3 == NULL)
        return 0;

    VX_MEM_FREE(buf2);

    vx_uint32 total = ownMemCurrUsage();
    if (total != 56)
        return 0;

    VX_MEM_FREE(buf1);
    VX_MEM_FREE(buf3);

    return 1;
}

int test_vxmemory_free(void)
{
    vx_char *buf1 = (vx_char*)VX_MEM_MALLOC(32);
    if (buf1 == NULL)
        return 0;

    vx_char *buf2 = (vx_char*)VX_MEM_CALLOC(1, 16);
    if (buf2 == NULL)
        return 0;

    VX_MEM_FREE(buf1);
    VX_MEM_FREE(buf2);

    vx_uint32 total = ownMemCurrUsage();
    if (total != 0)
        return 0;

    return 1;
}

int test_vxmemory_checking_leakage(void)
{
    ownMemAnalysis();
    if (ownMemCurrUsage() != 0)
        return 0;
    return 1;
}
