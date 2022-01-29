#ifndef UNIVERSAL_REFERENCE_H_
#define UNIVERSAL_REFERENCE_H_

#include <functional>
#include <iostream>

void func1(auto&& item1, auto&&... items) { // not fully supported yet, as there are warning about auto input for regular functions.
    std::cout << "item1: " << item1 << std::endl;
    std::cout << "more items: ";
    ((std::cout << items << " "), ...);
    std::cout << std::endl;
}

constexpr auto func2 = [](auto&& item1, auto&&... items){
    std::cout << "item1: " << item1 << std::endl;
    std::cout << "more items: ";
    ((std::cout << items << " "), ...);
    std::cout << std::endl;
};

template<typename T, typename... Args>
void func3(T&& item1, Args&&... items) {
    std::cout << "item1: " << item1 << std::endl;
    std::cout << "more items: ";
    ((std::cout << items << " "), ...);
    std::cout << std::endl;
}

#define TEST_FUNC(func)                 \
    {                                   \
        func(1);                        \
        func("aaaaa");                  \
        func("abc", "12", 45, "abc");   \
                                        \
        const int a = 56;               \
        func(a);                        \
                                        \
        const std::string s = "===";    \
        const int b = 45;               \
        func(a, s, b);                  \
    }

void test_universal_reference() {
    TEST_FUNC(func1);
    TEST_FUNC(func2);
    TEST_FUNC(func3);
}

#endif