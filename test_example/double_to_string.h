#ifndef __DOUBLE_TO_STRING_H__
#define __DOUBLE_TO_STRING_H__

#include <string>
#include <iomanip>
#include <iostream>


std::string double_to_string(double val) {
    std::ostringstream stringStream;
    stringStream << std::setprecision(3) << val;
    return stringStream.str();
}

void test_double_to_string() {
    std::cout << "test_double_to_string : " << double_to_string(3.14) << " " << double_to_string(5) <<
    " " << double_to_string(2.53656) << "  " << double_to_string(0.555555)  << " " << double_to_string(12345.1234) << std::endl;

}


#endif