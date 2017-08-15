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
#ifndef __VX_UNITTEST_H__
#define __VX_UNITTEST_H__

#if defined(HAVE_MEM_ANALYSIS)
//////////////////////////////////////////////////////////////////////
// unitest for vx_memory
///////////////////////////////////////////////////////////////////////
extern int test_vxmemory_alloc_free(void);
extern int test_vxmemory_alloc(void);
extern int test_vxmemory_free(void);
extern int test_vxmemory_checking_leakage(void);
#endif

//////////////////////////////////////////////////////////////////////
// unitest for vx_context
///////////////////////////////////////////////////////////////////////
extern int test_vxcontext_create(void);

//////////////////////////////////////////////////////////////////////
// unitest for vx_graph
///////////////////////////////////////////////////////////////////////
extern int test_vxgraph_create(void);

//////////////////////////////////////////////////////////////////////
// unitest for vx_image
///////////////////////////////////////////////////////////////////////
extern int test_vximage_create(void);

//////////////////////////////////////////////////////////////////////
// unitest for vx_matrix
///////////////////////////////////////////////////////////////////////
extern int test_vxmatrix_create(void);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// unitest for vx_logging
///////////////////////////////////////////////////////////////////////
extern int test_vxlogging_reg(void);

//////////////////////////////////////////////////////////////////////
// unitest for vx_reference
///////////////////////////////////////////////////////////////////////
extern int test_vxreference_init(void);
extern int test_vxreference_counting(void);
extern int test_vxreference_query_count(void);
extern int test_vxreference_query_type(void);
extern int test_vxreference_query_name(void);

#endif// __VX_UNITTEST_H__
