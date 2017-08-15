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
#include <stdio.h>
#include "seatest/seatest.h"
#include "ut.h"

#if defined(HAVE_MEM_ANALYSIS)
void test_ut_memory(void)
{
    assert_int_equal(1, test_vxmemory_alloc_free());
    assert_int_equal(1, test_vxmemory_alloc());
    assert_int_equal(1, test_vxmemory_free());
}

void test_ut_check_memory_leakage(void)
{
    assert_int_equal(1, test_vxmemory_checking_leakage());
}
#endif

void test_ut_context(void)
{
    assert_int_equal(1, test_vxcontext_create());
}

void test_ut_graph(void)
{
    assert_int_equal(1, test_vxgraph_create());
}

void test_ut_image(void)
{
    assert_int_equal(1, test_vximage_create());
}

void test_ut_matrix(void)
{
    assert_int_equal(1, test_vxmatrix_create());
}

void test_ut_logging(void)
{
    assert_int_equal(1, test_vxlogging_reg());
}

void test_ut_reference(void)
{
    assert_int_equal(1, test_vxreference_init());
    assert_int_equal(1, test_vxreference_counting());
    assert_int_equal(1, test_vxreference_query_count());
    assert_int_equal(1, test_vxreference_query_type());
    assert_int_equal(1, test_vxreference_query_name());
}

void all_tests(void)
{
    test_fixture_start();      
    run_test(test_ut_context); 
#if defined(HAVE_MEM_ANALYSIS)
    run_test(test_ut_memory); 
#endif
    run_test(test_ut_reference); 
    run_test(test_ut_graph); 
    run_test(test_ut_image); 
    run_test(test_ut_matrix); 
//    run_test(test_ut_logging); 
#if defined(HAVE_MEM_ANALYSIS)
    run_test(test_ut_check_memory_leakage);
#endif
    test_fixture_end(); 
}

int main(int argv, char **argc)
{
    return run_tests(all_tests);
}
