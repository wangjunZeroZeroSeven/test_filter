#ifndef CALC_PRIME_IN_COMPILATION_H_
#define CALC_PRIME_IN_COMPILATION_H_

template<size_t... N>
struct primers{};

primers<2>;

template<size_t ...N>
auto next(primers<N...>)
{
    return primers<N..., M>{};
}

using primers = decltype(next(...));


#endif