#ifndef __ONE_METHOD_OVERRIDE_SAME_TWO_H__
#define __ONE_METHOD_OVERRIDE_SAME_TWO_H__

#include <iostream>

class A {
private:
    virtual void Take(int a) = 0;
};

class B {
private:
    virtual void Take(int a) = 0;
};

class C: public A, public B {
public:
    virtual void Take(int a) override {
        std::cout << "result a: " << a << std::endl;
    }
};

void test_one_method_override_same_two() {
    C c;
    c.Take(321);

    // dynamic_cast<A*>(&c)->Take(11);

    // dynamic_cast<B*>(&c)->Take(22);
}

#endif