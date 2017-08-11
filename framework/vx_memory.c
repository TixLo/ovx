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

#define MEM_BLOCK_MAGIC 0x3E303E30

#define MEM_BACKTRACE_BUF_SIZE  256

/*
 * vx_mem_block_t :
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * | magic(4) | size(4) | next(8) | backtrace(256) | used pointer(N) |
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */
struct vx_mem_block_t{
    /* keep a magic code to determinate wether pollution or not  */
    vx_uint32 magic;
    /* allocated memory size */
    vx_uint32 size;
    /* keep current call stack for debuging */
    vx_char backtrace[MEM_BACKTRACE_BUF_SIZE];
    /* prev pointer of linking list */
    struct vx_mem_block_t *prev;
    /* next pointer of linking list */
    struct vx_mem_block_t *next;
};

/* head pointer to walk through all memory block */
static struct vx_mem_block_t *head = NULL;

/* last pointer of memory block linking list */
static struct vx_mem_block_t *last = NULL;

/* keep max memory usage information */
static vx_uint32 max_mem_usage = 0;

/* keep current memory usage information */
static vx_uint32 curr_mem_usage = 0;

/////////////////////////////////////////////////////////////////////////
// Private Functions
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// vx_memory.h
/////////////////////////////////////////////////////////////////////////
void *ownMemMalloc(size_t size)
{
    // alloc requested memory and alloc extra memory for analysis
    void *ptr = malloc(size + sizeof(struct vx_mem_block_t));
    if (!ptr)
        return NULL;
    memset(ptr, 0, size + sizeof(struct vx_mem_block_t));

    // convert allocated pointer to struct vx_mem_block_t
    struct vx_mem_block_t *block = (struct vx_mem_block_t*)ptr;

    // initialize variables of memory block
    block->magic = MEM_BLOCK_MAGIC;
    block->size = (vx_uint32)size;
    block->next = NULL;
    block->prev = NULL;
    VX_BACKTRACE_TO_BUF(block->backtrace, MEM_BACKTRACE_BUF_SIZE-1);

    // keep necessary information
    curr_mem_usage += size;
    max_mem_usage = (curr_mem_usage > max_mem_usage) ? curr_mem_usage : max_mem_usage ;
    
    // add to linking list
    if (head == NULL)
    {
        head = block;
        last = block;
    }
    else
    {
        block->prev = last;
        last->next = block;
        last = block;
    }

    // return a realistic pointer to user
    ptr = (vx_char*)ptr + sizeof(struct vx_mem_block_t);
    return ptr;
}

void *ownMemCalloc(size_t nmemb, size_t size)
{
    return ownMemMalloc(nmemb * size);
}

void ownMemFree(void *ptr)
{
    if (!ptr)
        return;

    // convert allocated pointer to struct vx_mem_block_t
    struct vx_mem_block_t *block = (struct vx_mem_block_t*)((vx_char*)ptr - sizeof(struct vx_mem_block_t));

    // check memory magic
    if (block->magic != MEM_BLOCK_MAGIC)
    {
        VX_PRINT(VX_DEBUG_ERR, "Memory was already polluted!");
        assert(0);
    }

    // keep necessary information
    curr_mem_usage -= block->size;

    // remove node from linking list
    if (block == head)
    {
        head = head->next;
    }
    else if (block == last)
    {
        last->prev->next = NULL;
        last = last->prev;
    }
    else
    {
        block->next->prev = block->prev;
        block->prev->next = block->next;
    }
    
    free((void*)block);
    block = NULL;
}

vx_uint32 ownMemCurrUsage(void)
{
    return curr_mem_usage;
}

void ownMemAnalysis()
{
    int i=0;
    struct vx_mem_block_t *block = NULL;
    
    VX_PRINT(VX_DEBUG_MEM, "============ Memory Analysis Information ================");
    VX_PRINT(VX_DEBUG_MEM, "the list of currently alived memory block:");
    block = head;
    for (i=0 ; block != NULL ; block = block->next, i++)
    {
        // check memory magic
        if (block->magic != MEM_BLOCK_MAGIC)
        {
            VX_PRINT(VX_DEBUG_ERR, "Memory was already polluted!");
            assert(0);
        }
        
        // print block information
        VX_PRINT(VX_DEBUG_MEM, "[block %d]", i);
        VX_PRINT(VX_DEBUG_MEM, "\tSize : %d", block->size);
        VX_PRINT(VX_DEBUG_MEM, "\tCall Stack :\n%s", block->backtrace);
    }
    VX_PRINT(VX_DEBUG_MEM, "--------------------------------------------------------");
    VX_PRINT(VX_DEBUG_MEM, "Total memory blocks : %d", i);
    VX_PRINT(VX_DEBUG_MEM, "Current memory usage : %d bytes", curr_mem_usage);
    VX_PRINT(VX_DEBUG_MEM, "Maximum memory usage : %d bytes", max_mem_usage);
}

