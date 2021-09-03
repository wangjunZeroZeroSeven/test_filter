#ifndef __TEST_REF_H__
#define __TEST_REF_H__

#include <functional>
#include <string>
#include <iostream>

class A
{
public:
    A() = delete;
    A(int t) {};
    
    virtual void render(){ std::cout << "render A" << std::endl; };
};

class B : public A
{
public:
    B(int t): A(t) {}
    virtual void render() override{ std::cout << "render B" << std::endl; };
};

void test_ref()
{
    A a(3);
    B b(3);

    A& r  = b;
    r.render();

    // 引用变量不能修改引用的对象！！
    //r = a;
    //r.render();

    // 不能用子类的引用初始化父类的引用！
    // B& br = r;
    // br.render();
}


#endif