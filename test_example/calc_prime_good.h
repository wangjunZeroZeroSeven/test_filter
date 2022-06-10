#ifndef CALC_PRIME_GOOD_H_
#define CALC_PRIME_GOOD_H_

#include <array>
#include <type_traits>
#include <iostream>
using namespace std;


template<size_t... N>
struct primers {
    constexpr static std::array<size_t, sizeof...(N)> makeArray()
    {
        return {N...};
    }
};

using FirstPrimer = primers<2>;

template<size_t M, size_t... N>
struct last {
    constexpr static auto value = last<N...>::value;
};
template<size_t M>
struct last<M> {
    constexpr static size_t value = M;
};

constexpr size_t nextTry(size_t v)
{
    return (v & 1) ? v + 2 : v + 1;
}

template<class>
struct primersMeta;

template<size_t... N>
struct primersMeta<primers<N...>> {
    constexpr static size_t lastValue = last<N...>::value;
    constexpr static size_t nextTryValue = nextTry(lastValue);
};

template<size_t M, size_t N>
struct isMultiple {
    constexpr static auto value = M % N == 0;
};

template<size_t, class>
struct primerCheck;

template<size_t M, size_t... N>
struct primerCheck<M, primers<N...>> {
    constexpr static auto value = std::conjunction_v<std::negation<isMultiple<M, N>>...>;
};

template<size_t, class>
struct appendPrimer;

template<size_t M, size_t... N>
struct appendPrimer<M, primers<N...>> {
    using type = primers<N..., M>;
};

template<class Primers, size_t N = primersMeta<Primers>::nextTryValue, bool = primerCheck<N, Primers>::value>
struct nextPrimers {
    using type = typename appendPrimer<N, Primers>::type;
};

template<class Primers, size_t N>
struct nextPrimers<Primers, N, false> {
    using type = typename nextPrimers<Primers, nextTry(N)>::type;
};

template<size_t M, class Primers, bool = (primersMeta<typename nextPrimers<Primers>::type>::lastValue < M)>
struct genPrimers {
    using type = typename genPrimers<M, typename nextPrimers<Primers>::type>::type;
};

template<size_t M, class Primers>
struct genPrimers<M, Primers, false> {
    using type = Primers;
};

template<size_t M>
struct makePrimers {
    using type = typename genPrimers<M, FirstPrimer>::type;
};

int test_prime_good()
{
    using ps = makePrimers<100>::type;
    constexpr auto result = ps::makeArray();
    using p2 = FirstPrimer;
    using p3 = nextPrimers<p2>::type;
    using p4 = nextPrimers<p3>::type;
    using p5 = nextPrimers<p4>::type;

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

#endif