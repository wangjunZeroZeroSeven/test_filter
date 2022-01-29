#ifndef STRUCT_COMPARE_H_
#define STRUCT_COMPARE_H_

#include <iostream>
#include <cstring>
#include <type_traits>
#include <utility>

template<typename T>
bool operator==(const T& lhs, const T& rhs)
{
    std::cout << "exec equal" << std::endl;
    return std::memcmp(&lhs, &rhs, sizeof(T)) == 0;
}

template<typename T>
bool operator!=(const T& lhs, const T& rhs)
{
    std::cout << "exec unequal" << std::endl;
    return !(lhs == rhs);
}

template<typename... T, 
        typename = std::enable_if_t<std::conjunction_v<std::bool_constant<std::is_default_constructible_v<T>>...>>>
bool bindComparators() {
    bool ret = false;
    ((ret = T() != T()), ...);
    return ret;
};

struct A {
    int a = 0;
};

void test_bind_struct_type_comparator() {
    A a, b;

    bool ret = bindComparators<A>();
    std::cout << "bind " << (!ret ? "success" : "fail") << std::endl;

    a == b;
}

#endif