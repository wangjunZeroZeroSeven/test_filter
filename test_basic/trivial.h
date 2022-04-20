#ifndef TRIVIAL_H_
#define TRIVIAL_H_

#include <iostream>
#include <type_traits>
#include <array>
 
struct A {
    int m;
};
 
struct B {
    B() {}
};

struct DvsLayerConfig {
    uint8_t destination = 0b1101;
    bool onlyAsyncIn = false;
    bool dropInEvent = false;
    std::array<uint8_t, 2> pooling{0, 0};
    bool merge = false;
    bool onChannel = true;
    bool offChannel = true;
    std::array<uint8_t, 2> origin{0, 0};
    std::array<uint8_t, 2> cut{0, 0};
    std::array<bool, 2> mirror{false, false};
    bool mirrorDiagonal = false;
    bool passSensorEvents = true;
};

struct Structs1 {
    uint8_t destination = 1;
};
struct Structs2 {
    uint8_t destination;
};

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2() = default;
    Vec2(T _x, T _y) :
        x(_x), y(_y) {}
    bool operator==(const Vec2<T>& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Vec2<T>& rhs) const { return !(*this == rhs); }
};
 
int test_trivial() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_trivial<A>::value << '\n';
    std::cout << std::is_trivial<B>::value << '\n';
    std::cout << std::is_trivial<std::array<std::uint16_t, 5>>::value << std::endl;
    std::cout << std::is_trivial<DvsLayerConfig>::value << std::endl;
    std::cout << std::is_trivially_copyable<DvsLayerConfig>::value << std::endl;
    std::cout << std::is_trivially_copyable<Vec2<std::uint16_t>>::value << std::endl;

    std::cout << "---------------" << std::endl;
    std::cout << std::is_trivial<Structs1>::value << std::endl;
    std::cout << std::is_trivial<Structs2>::value << std::endl;

    return 0;
}

#endif