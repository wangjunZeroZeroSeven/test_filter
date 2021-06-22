#ifndef __REMOVE_IF_H__
#define __REMOVE_IF_H__

#include "util.h"

void test_remove_if() 
{
    int x = 5;
    std::vector<int> c {1,2,3,5,4,6,7};
    auto iter = remove_if(c.begin(), c.end(), [x](int n){return n < x;});
    int a = iter - c.begin();
    std::cout << a << endl;
    c.erase(iter, c.end());

    print_vector(c);
}


#endif