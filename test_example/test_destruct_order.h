#ifndef __TEST_DESTRUCT_ORDER_H__
#define __TEST_DESTRUCT_ORDER_H__

#include <iostream>
#include <vector>
#include <map>
#include <memory>

class MA1 {
public:
    MA1(bool out) : out(out) {
        if (out) std::cout << "construct MA1" << std::endl;
    }
    ~MA1() {
        if (out) std::cout << "destruct MA1" << std::endl;
    }
private:
    bool out;
};
class MA2 {
public:
    MA2(bool out) : out(out) {
        if (out) std::cout << "construct MA2" << std::endl;
    }
    ~MA2() {
        if (out) std::cout << "destruct MA2" << std::endl;
    }
private:
    bool out;
};

class A {
public:
    A(int i, bool out): i(i), a1(out), a2(out) {
        std::cout << "construct A " << i << std::endl;
    }

    ~A() {
        std::cout << "destruct A " << i << std::endl;
    }

protected:
    int i;
    MA1 a1;
    MA2 a2;
};


class MB1 {
public:
    MB1(bool out) : out(out) {
        if (out) std::cout << "construct MB1" << std::endl;
    }
    ~MB1() {
        if (out) std::cout << "destruct MB1" << std::endl;
    }
private:
    bool out;
};
class MB2 {
public:
    MB2(bool out) : out(out) {
        if (out) std::cout << "construct MB2" << std::endl;
    }
    ~MB2() {
        if (out) std::cout << "destruct MB2" << std::endl;
    }
private:
    bool out;
};

class B: public A {
public:
    B(int i, bool out): A(i, out), b1(out), b2(out) {
        std::cout << "construct B " << i << std::endl;
    }

    ~B() {
        std::cout << "destruct B " << i << std::endl; 
    }

protected:
    MB1 b1;
    MB2 b2;
};

void test_destruct_order() 
{
    {
        std::cout << "testing derived object destruct : " << std::endl;
        B b(0, true);
    }

    {
        std::cout << "testing vector destruct: " << std::endl;
        std::vector<A> vec;
        vec.emplace_back(0, false);
        vec.emplace_back(1, false);
        vec.emplace_back(2, false);
    }

    {
        std::cout << "testing map destruct : " << std::endl;
        std::map<int, A> m;
        m.try_emplace(0, 0, false);
        m.try_emplace(1, 1, false);
        m.try_emplace(2, 2, false);
        m.try_emplace(3, 3, false);
        m.try_emplace(4, 4, false);
    }
}


#endif