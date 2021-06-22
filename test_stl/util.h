#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <iostream>

void print_vector(const std::vector<int>& vec) {
    std::cout << "vec: ";
    for (auto& elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

#endif