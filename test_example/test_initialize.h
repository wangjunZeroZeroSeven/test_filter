#ifndef TEST_INITIALIZE_H_
#define TEST_INITIALIZE_H_

#include <iostream>

class A {
public:
    A(){ std::cout << " member constructor !" << std::endl; };
    ~A(){ std::cout << " member deconstructor !" << std::endl; };
};

class B {
public:
    B() {
        std::cout << " class constructor !" << std::endl;
    }

    ~B() {
        std::cout << " class deconstructor !" << std::endl;
    }

private:
    A a;
};

void test_initialize() {
    B b;
}


#endif