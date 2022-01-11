#ifndef __INDEX_SEQ_H__
#define __INDEX_SEQ_H__

#include <iostream>
#include <utility>

template<size_t... N, size_t... M>
void tryToPrint(std::index_sequence<N...>, std::index_sequence<M...>)
{
    ((std::cout << N << " " << M << std::endl), ...);
}

int test_index_seq()
{
    tryToPrint(std::make_index_sequence<8>{}, std::make_index_sequence<8>{});
    return 0;
}

#endif