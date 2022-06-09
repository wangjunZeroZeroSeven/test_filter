#ifndef CALC_PRIME_IN_COMPILATION_H_
#define CALC_PRIME_IN_COMPILATION_H_

#include <iostream>
#include <utility>

template<size_t... N>
struct Primes {
    void print() const {
        (std::cout << ... << (std::to_string(N) + " ")) << '\n';
    }
};

constexpr bool isPrime(size_t n) {
    if (n < 2) {
        return false;
    }

    // std::sqrt 不支持constexpr
    for (int d = 2; d < n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

// concat
template <size_t, typename> struct Cons;

template <size_t T, size_t ...Args>
struct Cons<T, Primes<Args...>>
{
    using type = Primes<T, Args...>;
};

// filter
template <size_t...> struct filter;

template <> struct filter<> { using type = Primes<>; };

template <size_t Head, size_t ...Tail>
struct filter<Head, Tail...>
{
    using type = typename std::conditional_t<isPrime(Head),
                               typename Cons<Head, typename filter<Tail...>::type>::type,
                               typename filter<Tail...>::type>;
};

template<size_t... I>
constexpr auto calc_prime(std::index_sequence<I...>) {
    using TargetType = typename filter<I...>::type;
    return TargetType();
};

template<size_t N>
constexpr auto calc_prime() {
    return calc_prime(std::make_index_sequence<N>{});
}

void test_calc_prime() {
    constexpr auto primes = calc_prime<100>();
    primes.print();
}


#endif