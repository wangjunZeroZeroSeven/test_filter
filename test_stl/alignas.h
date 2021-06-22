#ifndef __ALIGANAS_H__
#define __ALIGANAS_H__

#include <iostream>

struct alignas(8) TestAlign
{
    char buf[13];
    int t;
};

struct alignas(8) TestAlign2
{
    char buf[12];
    int t;
};

struct TestAlign3
{
    alignas(8) char buf[12];
    int t;
};

struct TestAlign4
{
    alignas(8) char buf[12];
};

struct TestAlign5
{
    int t;
    alignas(8) char buf[12];
};


//通过测试发现在类成员上使用alignas 和 在类上使用alignas效果差不多。

void test_alignas() {
    std::cout << alignof(TestAlign) << endl;
    std::cout << sizeof(TestAlign) << endl;

    std::cout << alignof(TestAlign2) << endl;
    std::cout << sizeof(TestAlign2) << endl;

    std::cout << alignof(TestAlign3) << endl;
    std::cout << sizeof(TestAlign3) << endl;

    std::cout << alignof(TestAlign4) << endl;
    std::cout << sizeof(TestAlign4) << endl;

    std::cout << alignof(TestAlign5) << endl;
    std::cout << sizeof(TestAlign5) << endl;
}

#endif