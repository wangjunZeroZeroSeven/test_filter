#ifndef __TEST_STRUCT_H__
#define __TEST_STRUCT_H__

#include <string>

class TestEq
{
public:
    int a = 0;
    bool b = false;
    std::string s = "";
};

void test_struct_eq()
{
    TestEq t1;
    t1.a = 1;
    t1.b = true;
    t1.s = "abc";

    TestEq t2;
    t2.a = 1;
    t2.b = true;
    t2.s = "abc";

    // bool ret1 = (t1 == t2);

    // t2.b = false;

    // bool ret2 = (t1 == t2);

    // int a = 0;
}

#endif
