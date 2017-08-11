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
#ifndef _OPENVX_DEBUG_H_
#define _OPENVX_DEBUG_H_

/*!
 * \file
 * \brief The internal debugging APIs
 */

#ifdef __cplusplus
extern "C" {
#endif

enum vx_debug_level_e {
    VX_DEBUG_NONE       = 0,
    VX_DEBUG_ERR        = 1,
    VX_DEBUG_WRN        = 2,
    VX_DEBUG_INFO       = 3,
    VX_DEBUG_MEM        = 4,
    VX_DEBUG_MAX        = 5
};

#if defined(HAVE_DEBUG)
#include <stdarg.h>

#define VX_PRINT(level, message, ...) do { vx_print(level, "[%s:%u] "message, __FUNCTION__, __LINE__, ## __VA_ARGS__); } while (0)

/*! \brief Internal Printing Function.
 * \param [in] level The debug level from \ref vx_debug_level_e.
 * \param [in] format The format string to print.
 * \param [in] ... The variable list of arguments.
 * \ingroup group_int_debug
 */
void vx_print(vx_enum level, char *format, ...);

/*! \brief Pulls the debug level level from the environment variables.
 * \ingroup group_int_debug
 */
void vx_set_debug_level_from_env(void);

#define VX_BACKTRACE(level) {                                                    \
    void *stack[50];                                                             \
    int i, cnt = backtrace(stack, dimof(stack));                                 \
    char **symbols = backtrace_symbols(stack, cnt);                              \
    vx_print(level, "------------ Backtrace[%d] ---------------", cnt);          \
    for (i = 0; i < cnt; i++) {                                                  \
        vx_print(level, "%s", (symbols ? symbols[i] : NULL));                    \
    }                                                                            \
    free(symbols);                                                               \
}

#define VX_BACKTRACE_TO_BUF(buf, size) {                                         \
    void *stack[50];                                                             \
    int i, cnt = backtrace(stack, dimof(stack));                                 \
    char **symbols = backtrace_symbols(stack, cnt);                              \
    for (i = 0; i < cnt; i++) {                                                  \
        snprintf(&buf[strlen(buf)], size-strlen(buf), "%s\n", (symbols ? symbols[i] : NULL)); \
    }                                                                            \
    free(symbols);                                                               \
}

#else//HAVE_DEBUG

#define VX_PRINT(level, message, ...) do{ if(0) vx_print(level, message, ## __VA_ARGS__); } while(0)

void vx_print(vx_enum level, char *format, ...);

void vx_set_debug_level_from_env(void);


#endif//HAVE_DEBUG

#ifdef __cplusplus
}
#endif

#endif
