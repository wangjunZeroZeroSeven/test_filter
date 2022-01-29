#ifndef COUNTER_MACRO_H_
#define COUNTER_MACRO_H_

#include <iostream>

#define SVEJS_CONCAT_INNER(x) std::cout << x << "  " << x << std::endl; 

// int getCounter() {
//     return __COUNTER__;
// }

// int getCounter2() {
//     return __COUNTER__;
// }

// auto getCounter3() {

// }

void test_counter() {
    SVEJS_CONCAT_INNER(__COUNTER__);

    SVEJS_CONCAT_INNER(__COUNTER__);

    SVEJS_CONCAT_INNER(__COUNTER__);
}

#endif