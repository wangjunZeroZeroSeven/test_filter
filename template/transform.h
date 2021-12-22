#ifndef TEMPLATE_TRANSFORM_H_
#define TEMPLATE_TRANSFORM_H_

#include <tuple>
#include <type_traits>

// a template that take metafunction as input
template<template<class...> class MetaFunction>
struct lambda
{
    struct type
    {
        template<typename... Args> struct apply
        {
            using type = typename MetaFunction<Args...>::type;
        };
    };
};

// transform
template<typename List, typename F> struct transform;

template<template<class...> class List, typename... Elems, typename F>
struct transform<List<Elems...>, F>
{
    template<typename T>
    using call = typename F::template apply<T>::type;

    using type = List< call<Elems>... >;
};

using no_pointers = transform< std::tuple<int*, float**, double>, lambda<std::remove_pointer>::type >::type;

template<typename T>
class TD;

void test_transform()
{
    // TD<no_pointers> aa;
}


#endif