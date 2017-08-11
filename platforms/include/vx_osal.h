/* 
 * Copyright (c) 2012-2016 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
 * KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
 * SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
 *    https://www.khronos.org/registry/
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#ifndef _OPENVX_INT_OSAL_H_
#define _OPENVX_INT_OSAL_H_

/*!
 * \file
 * \brief The internal operating system abstraction layer.
 * \author Erik Rainey <erik.rainey@gmail.com>
 *
 * \defgroup group_int_osal Internal OSAL API
 * \ingroup group_internal
 * \brief The Internal Operating System Abstraction Layer API.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Creates a semaphore object and sets to a given count.
 * \ingroup group_int_osal
 */
vx_bool ownCreateSem(vx_sem_t *sem, vx_uint32 count);

/*! \brief Releases a semaphore object.
 * \ingroup group_int_osal
 */
void ownDestroySem(vx_sem_t *sem);

/*! \brief
 * \ingroup group_int_osal
 */
vx_bool ownSemPost(vx_sem_t *sem);

/*! \brief
 * \ingroup group_int_osal
 */
vx_bool ownSemWait(vx_sem_t *sem);

/*! \brief
 * \ingroup group_int_osal
 */
vx_bool ownSemTryWait(vx_sem_t *sem);

#ifdef __cplusplus
}
#endif

#endif
