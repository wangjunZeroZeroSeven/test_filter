#ifndef TEMPLATE_LIST_H_
#define TEMPLATE_LIST_H_

#include <tuple>
#include <string>
#include <iostream>

template<class List> struct size;

template<template<class...> class List, class... Elements>
struct size<List<Elements...>> 
    : std::integral_constant<std::size_t, sizeof...(Elements)>
{};



template<class List, class New> struct push_front;

template<template<class...> class List, class... Elements, class New>
struct push_front<List<Elements...>, New>
{
    using type = List<New, Elements...>;
};



template<class List> struct remove_front;

template<template<class...> class List, class Head, class... Elements>
struct remove_front<List<Head, Elements...>>
{
    using type = List<Elements...>;
};

template<template<class...> class List>
struct remove_front<List<>>
{
    using type = List<>;
};


void test_template() {
    using Lst = push_front<std::tuple<int, float, void>, std::string>::type;
    using Lst1 = remove_front<Lst>::type;
    using Lst2 = remove_front<Lst1>::type;
    constexpr auto s = size<Lst2>::value;
    std::cout << "basic function test  -- " << s << std::endl;
}


#endif