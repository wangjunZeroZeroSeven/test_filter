#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <assert.h>

void test_assert()
{
    // try
    // {
    //     assert(false && "abc");
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    

    assert(false && "abc");
}

#endif