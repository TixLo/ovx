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

vx_bool ownCreateSem(vx_sem_t *sem, vx_uint32 count)
{
    *sem = CreateSemaphore(NULL, count, count, NULL);
    if (*sem == 0)
        return vx_true_e;
    else
        return vx_false_e;
}

void ownDestroySem(vx_sem_t *sem)
{
    CloseHandle(*sem);
}

vx_bool ownSemPost(vx_sem_t *sem)
{
    if (ReleaseSemaphore(*sem, 1, NULL) == TRUE)
        return vx_true_e;
    else
        return vx_false_e;
}

vx_bool ownSemWait(vx_sem_t *sem)
{
    if (WaitForSingleObject(*sem, INFINITE) == WAIT_OBJECT_0)
        return vx_true_e;
    else
        return vx_false_e;
}

vx_bool ownSemTryWait(vx_sem_t *sem)
{
    if (WaitForSingleObject(*sem, 0) == WAIT_OBJECT_0)
        return vx_true_e;
    else
        return vx_false_e;
}
