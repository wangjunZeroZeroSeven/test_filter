#ifndef TEST_BASIC_TRANSFORM_H_
#define TEST_BASIC_TRANSFORM_H_

#include <iostream>

using namespace std;

int test_reference()
{
    cout<<"Hello World" << std::endl;
    
    int b = 2, c = 3;
    
    int& a = b;
    
    int& d = c;
    
    a = d;
    a = 10;
    
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << std::endl;

    return 0;
}

#endif