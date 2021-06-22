#ifndef __VISIT_VARIANT_H__
#define __VISIT_VARIANT_H__
#include <optional>
#include <variant>
#include <iostream>


class A {

};

class B {

};

class C {

};

class D {

};

using AB = std::variant<A, B>;
using CD = std::variant<C, D>;

using AD = std::variant<AB, CD>;

void test_visit_variant()
{
    AD a = A();
    std::visit([&](auto&& arg){
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<A, T>) {
            std::cout << "it is A" << std::endl;
        }
        else if constexpr (std::is_same_v<AB, T>) {
            std::cout << "it is AB" << std::endl;
        }

    }, a);
}

#endif