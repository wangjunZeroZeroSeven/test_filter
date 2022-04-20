#ifndef __FUNCTION_PTR_H__
#define __FUNCTION_PTR_H__

#include <iostream>

void f1(int (*pf)(int)) {
    std::cout << pf(555) << std::endl;
}

void f2(int pf(int)) {
    std::cout << pf(666) << std::endl;
}

int multi(int a) {
    return a * 2;
}

void test_function_ptr() {
    f1(multi);
    f2(multi);
}


#endif