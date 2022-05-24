#ifndef DERIVE_PRIVATE_H_
#define DERIVE_PRIVATE_H_

#include <iostream>

class Base
{
private:
    virtual void f() {
        std::cout << "base method called" << std::endl;
    }
};

class Derived : public Base
{
public:
    void print() {
        f();
    }

private:
    virtual void f() {
        std::cout << "derived method called" << std::endl;
    }
};

void test_derive_private() {
    Derived d;
    d.print();
}


#endif