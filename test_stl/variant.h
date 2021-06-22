#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <variant>
#include <type_traits>

class A {
    int a;
};

class B {
    bool b;
};

using V = std::variant<A, B>;

void test_variant() {
    V v = A();
    using T = std::decay_t<decltype(v)>;
    bool B1 = std::is_same_v<decltype(v), A>;
    bool b1 = std::is_same_v<A, T>;

    V v2 = B();
    using R = std::decay_t<decltype(v2)>;
    bool B2 = std::is_same_v<decltype(v2), B>;
    bool b2 = std::is_same_v<B, R>;

    std::visit([](auto&& arg){
        using C = std::decay_t<decltype(arg)>;
        bool bb = std::is_same_v<C, A>;

        int r = 0;

    }, v);

    int a = 0;
}


#endif