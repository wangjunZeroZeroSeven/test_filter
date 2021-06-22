#ifndef __STD_COPY_H__
#define __STD_COPY_H__

#include "util.h"

void test_std_copy()
{
    std::vector<int> vec1(3, 4);
    std::vector<int> vec2(4, 5);

    //如果push到的是普通的iterator, 则是纯拷贝，需要保证后面的容器大小不小于前面的。
    std::copy(vec1.begin(), vec1.end(), vec2.begin());

    //如果使用back_inserter, 就直接向后增加元素。
    //std::copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));

    auto backInserter = std::back_inserter(vec2);

    //等于号可以直接向容器后面插入元素。
    backInserter = 6;
    backInserter = 7;
    backInserter = 8;

    print_vector(vec2);
}

#endif