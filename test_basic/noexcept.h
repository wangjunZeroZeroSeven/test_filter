#ifndef NOEXCEPT_H_
#define NOEXCEPT_H_

#include <iostream>
#include <string>

// gdb调试教程： https://stackoverflow.com/questions/5115613/core-dump-file-analysis

void doSomething1() noexcept {
    std::cout << "good" << std::endl;
    try {
        throw "aaaaaaaaaaaaaaa";
    }
    catch(...) {
        std::cout << "got it" << std::endl;
    }
}

void doSomething2() {
    int a = 6;
    std::string s = "abc";
    std::cout << "good" << std::endl;
    throw "aaaaaaaaaaaaaaa";
}

void doSomething3() noexcept {
    int a = 6;
    std::string s = "abc";
    std::cout << "good" << std::endl;
    throw "aaaaaaaaaaaaaaa";
}

void test_noexcept() {
    doSomething1();     // no terminate
    // doSomething2();  // can debug with core and we can see local variables in debug mode but no locals in release mode.
    // doSomething3();  // same with doSomething2

    // exception in normal function can be caught.
    try {
        doSomething2();
    }
    catch(...) {
        std::cout << "catch exception in normal. " << std::endl;
    }

    // exception in noexcept function can't be caught. but we still can see stack.
    try {
        doSomething3();
    }
    catch(...) {
        std::cout << "catch exception in noexcept. " << std::endl;
    }
}

#endif