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
#ifndef __VX_MEMORY_H__
#define __VX_MEMORY_H__

#ifdef __cplusplus
extern "C"{
#endif

#if defined(HAVE_MEM_ANALYSIS)

/*! \brief Allocates a memory block.
 */
void *ownMemMalloc(size_t size);

/*! \brief Allocates a memory block and clean it
 */
void *ownMemCalloc(size_t nmemb, size_t size);

/*! \brief Free allocaed memory block 
 */
void ownMemFree(void *ptr);

/*! \brief Analysis of memory usage
 */
void ownMemAnalysis(void);

/*! \brief get current memory usage
 */
vx_uint32 ownMemCurrUsage(void);

#define VX_MEM_CALLOC   ownMemCalloc 
#define VX_MEM_MALLOC   ownMemMalloc
#define VX_MEM_FREE     ownMemFree

#else//HAVE_MEM_ANALYSIS

#define VX_MEM_CALLOC   calloc
#define VX_MEM_FREE     free
#define VX_MEM_MALLOC   malloc

#endif//HAVE_MEM_ANALYSIS

#ifdef __cplusplus
}
#endif

#endif// __VX_MEMORY_H__
