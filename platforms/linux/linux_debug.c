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

#if defined(HAVE_DEBUG)

/* debug level */
static vx_uint32 vx_debug_level = 0;

/* the string of debug label for printing */
static vx_char *debug_level_str[] = 
{
    "None" ,
    "ERR " ,
    "WRN " ,
    "INFO" , 
    "MEM " 
};

/* different colors represent different debug levels */
static vx_char *debug_level_color[] = 
{
    "\x1B[0m" , //Reset
    "\x1B[31m", // Red
    "\x1B[33m", // Yellow
    "\x1B[32m", // Green
    "\x1B[35m"  // Mag
};

/* reset console color of output text */
#define RESET   "\x1B[0m"

#define WHITE   "\x1B[37m"

/////////////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////////////
void vx_print(vx_enum level, char *format, ...)
{
    if (level <= vx_debug_level)
    {
        char string[1024];
        va_list ap;
        snprintf(string, sizeof(string), "[%s%4s"RESET"]:%s\n", debug_level_color[level], debug_level_str[level], format);
        va_start(ap, format);
        vprintf(string, ap);
        va_end(ap);
    }
}

void vx_set_debug_level_from_env(void)
{
    char *str = getenv("VX_DEBUG_LEVEL");
    if (str)
        sscanf(str, "%d", &vx_debug_level);
    else
        vx_debug_level = VX_DEBUG_NONE;
}
#else//HAVE_DEBUG
void vx_print(vx_enum level, char *format, ...){}
void vx_set_debug_level_from_env(void){}
#endif//HAVE_DEBUG
