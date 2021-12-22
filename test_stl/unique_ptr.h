#ifndef __UNIQUE_PTR_H__
#define __UNIQUE_PTR_H__

#include <memory>
#include <iostream>
#include <functional>

std::unique_ptr<int, std::function<void(int*)>> makeCustomUniquePtr(int a) {
    return std::unique_ptr<int, std::function<void(int*)>>(new int(a), [](int* p)->void{
        if (p) {
            std::cout << "delete : " << *p << std::endl;
            delete p;
        }
    });
}

void test_custom_unique_ptr() {
    std::cout << "to test custom unique_ptr" << std::endl;
    auto ptr1 = makeCustomUniquePtr(45);
    auto ptr2 = makeCustomUniquePtr(46);
    auto ptr3 = makeCustomUniquePtr(47);
    std::cout << "construction over" << std::endl;
}



#endif