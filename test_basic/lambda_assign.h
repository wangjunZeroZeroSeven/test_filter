#ifndef LAMBDA_ASSIGN_H_
#define LAMBDA_ASSIGN_H_

#include <iostream>
#include <functional>

void test_lambda_assign()
{    
    auto f = [](auto&& msg){ 
        std::cout << "function : " << msg << std::endl; 
    };
    
    std::function<void(std::string)> g = f;
    g("Good");
}


#endif