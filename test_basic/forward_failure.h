#ifndef FORWARD_FAILURE_H_
#define FORWARD_FAILURE_H_

#include <vector>
#include <iostream>

template<typename... Ts>
class TD;

void f(const std::vector<int>& v) {
    std::cout << "get length: " << v.size() << std::endl;
}

template<typename... Ts>
void fwd(Ts&&... params) {
    // TD<Ts...> td; 
    f(std::forward<Ts>(params)...);
} 

void test_forward() {
    auto lst = {1,2,3};
    //fwd({1,2,3});     // 注意： 模板不能识别std::initializer_list， auto可以识别！
    fwd(lst);
}

#endif