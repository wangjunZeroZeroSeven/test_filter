#ifndef __METHOD_POINTER_H__
#define __METHOD_POINTER_H__

#include <functional>
#include <iostream>

class A {

public:
    void method(int a) {
        std::cout << "result a is " << a << std::endl;
    }

};

void test_method_pointer() {
    using Pointer = void (A::*)(int a);
    Pointer p = &A::method;

    A a;
    auto p2 = std::bind(p, &a, std::placeholders::_1);

    (a.*p)(1);
    p2(2);

    int r = 0;
}


#endif