#ifndef UNCAUGHT_EXCEPTION_H
#define UNCAUGHT_EXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

struct Foo {
    int count = std::uncaught_exceptions();
    std::string name;

    Foo(std::string name) : name(name) {}
    ~Foo() {
        std::cout << (count == std::uncaught_exceptions()
            ? std::string("~Foo(") + name + ") called normally\n"
            : std::string("~Foo(") + name + ") called during stack unwinding\n");
    }
};

void test_uncaught_exception()
{
    Foo f("out");
    try {
        Foo g("in");
        std::cout << "Exception thrown\n";
        throw std::runtime_error("test exception");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}

#endif