#ifndef DERIVE_PRIVATE_H_
#define DERIVE_PRIVATE_H_

#include <iostream>

class Base
{
public:
    virtual void g() = 0;

    void p() {
        std::cout << "call base private member: " << aaa << std::endl; 
    }
private:
    virtual void f() {
        std::cout << "base method called" << std::endl;
    }
    int aaa = 7;
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
        p();
    }

    void g() override {
        std::cout << "private method is called by public interface!" << std::endl;
    }
};

void test_private_call(Base& b) {
    b.g();
}

void test_derive_private() {
    Derived d;
    d.print();

    test_private_call(d);
}


#endif