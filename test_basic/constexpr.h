#ifndef CONSTEXPR_H_
#define CONSTEXPR_H_

#include <iomanip>
#include <cmath>
#include <utility>
#include <array>
#include <iostream>
#include <typeinfo>

template <std::size_t N>
constexpr int naiveSumArray() {
    std::array<int, N> arr { 0 };
    for (std::size_t i = 0; i < arr.size(); ++i)
        arr[i] = i+1;
    int sum = 0;
    for (const auto& elem : arr)
        sum += elem;
    return sum;
}

constexpr int smartSum(unsigned int n) {
    return (n*(1+n))/2;
}


class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal)
    {}
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    constexpr void setX(double newX) noexcept { x = newX; }
    constexpr void setY(double newY) noexcept { y = newY; }

private:
    double x, y;
};

// return reflection of p with respect to the origin (C++14)
constexpr Point reflection(const Point& p) noexcept
{
    Point result; // create non-const Point
    result.setX(-p.xValue()); // set its x and y values
    result.setY(-p.yValue());
    return result; // return copy of it
}

constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return { (p1.xValue() + p2.xValue()) / 2, // call constexpr
        (p1.yValue() + p2.yValue()) / 2 }; // member funcs
}




/*--------------------------------------------------------------------*/
// C++20后可在编译器动态分配内存。

class PrimeGenerator 
{
public:
    constexpr PrimeGenerator(int upBound) : upBound{upBound} {}

    constexpr int calcPrimes() const { // 这个const不能少

        size_t curr_index = 0;
        for (int num = 2; num <= upBound; num++) {
            // std::sqrt 不支持constexpr
            bool is_prime = true;
            for (int d = 2; d < num; d++) {
                if (num % d == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                // std::cout << "get prime: " << num << std::endl;
                // std::cout 不支持constexpr
                curr_index++;
                num;
            }
        }

        return 1;
    }

    constexpr void calcPrimesWithUpbound(int ub) {

        size_t curr_index = 0;
        for (int num = 2; num <= upBound; num++) {
            // std::sqrt 不支持constexpr
            bool is_prime = true;
            for (int d = 2; d < num; d++) {
                if (num % d == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                // std::cout << "get prime: " << num << std::endl;
                // std::cout 不支持constexpr
                curr_index++;
            }
        }
    }
    
private:
    int upBound;
};

constexpr int calc_with_generator(int ub) {
    PrimeGenerator gen(ub);
    gen.calcPrimesWithUpbound(ub);
    return 1;
}

void test_constexpr() {
    static_assert(naiveSumArray<10>() == smartSum(10));
    static_assert(naiveSumArray<11>() == smartSum(11));
    static_assert(naiveSumArray<23>() == smartSum(23));
    std::cout << "static assert passed!" << std::endl;

    constexpr Point p1(9.4, 27.7); // as above
    constexpr Point p2(28.8, 5.3);
    constexpr auto mid = midpoint(p1, p2);
    constexpr auto reflectedMid = // reflectedMid's value is
    reflection(mid); // (-19.1 -16.5) and known
    // during compilation

    std::cout << "point calculate over!" << mid.xValue() << " " << mid.yValue() << std::endl;
    std::cout << "point calculate over!" << reflectedMid.xValue() << " " << reflectedMid.yValue() << std::endl;

    constexpr int upBound = 100;
    constexpr PrimeGenerator gen(upBound);

    constexpr auto ret = gen.calcPrimes();
    std::cout << "get result: " << ret << std::endl;

    constexpr auto ret2 = calc_with_generator(upBound);
    std::cout << "get result: " << ret2 << std::endl;

    // constexpr函数在C++17中不好返回列表。关于编译器计算素数请参考 calc_prime_in_compilation.h 文件。
}

#endif