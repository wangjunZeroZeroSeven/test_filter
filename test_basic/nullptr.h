#ifndef TEST_BASIC_NULLPTR_H_
#define TEST_BASIC_NULLPTR_H_

#include <memory>
#include <mutex>
#include <iostream>

int f1(std::shared_ptr<int> sp) {
    if (!sp) {
        std::cout << "f1 empty" << std::endl;
    }
    return 0;
}

int f2(std::unique_ptr<int> up) {
    if (!up) {
        std::cout << "f2 empty" << std::endl;
    }
    return 0;
}

int f3(int* rp) {
    if (!rp) {
        std::cout << "f3 empty" << std::endl;
    }
    return 0;
}

using MuxGuard = std::lock_guard<std::mutex>;

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
{
    MuxGuard g(mutex);
    return func(ptr);
}


void test_nullptr() {
    std::mutex f1m, f2m, f3m;
    
    f1(0);
    f2(NULL);
    
    f1(nullptr);
    f2(nullptr);
    f3(nullptr);

    std::cout << "=================" << std::endl;

    // lockAndCall(f1, f1m, 0);     // 报错: error: could not convert ‘ptr’ from ‘int’ to ‘std::shared_ptr<int>’
    // lockAndCall(f2, f2m, NULL);  // 报错: error: could not convert ‘ptr’ from ‘long int’ to ‘std::unique_ptr<int>’
    lockAndCall(f1, f1m, nullptr);
    lockAndCall(f2, f2m, nullptr);
    lockAndCall(f3, f3m, nullptr);
}


#endif