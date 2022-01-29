#ifndef RVALUE_H_
#define RVALUE_H_

#include <string>
#include <iostream>
#include <iomanip>

template<typename T>
class TD;

void test_rvalue() {
    std::string s = "Good";

    std::string&& r1 = std::move(s);

    std::cout << "right value address: " << std::hex << (&r1) << std::dec << std::endl;

    std::string s2 = "Bad";

    r1 = std::move(s2);

    std::cout << "right value address: " << std::hex << (&r1) << std::dec << std::endl;

    r1 = "ABC";

    std::cout << "right value address: " << std::hex << (&r1) << std::dec << std::endl;

    // & + && = &
    // std::string& r2 = s;
    // TD<decltype(r2)&&>();

    // && + & = &
    // TD<decltype(r1)&>();
}


#endif