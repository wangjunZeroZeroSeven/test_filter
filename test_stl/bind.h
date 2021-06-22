#ifndef __STD_BIND_H__
#define __STD_BIND_H__
#include <functional>
#include <iostream>

void func(int a, int b = 2) {
    std::cout << "result a: " << a << ", b: " << b << std::endl;
}

void test_bind() {
    std::function<void()> f = [&](){func(1);};
    f();
}


#endif