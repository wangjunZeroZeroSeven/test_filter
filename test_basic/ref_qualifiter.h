#ifndef REF_QUALIFIER_H_
#define REF_QUALIFIER_H_

#include <iostream>

class Widget {
public:
    void doWork() & {
        std::cout << "calling with lvalue." << std::endl;
    }

    void doWork() && {
        std::cout << "calling with rvalue." << std::endl;
    }
};

Widget makeWidget() {
    return {};
}

void test_ref_qualifier() {
    Widget w;

    w.doWork();
    makeWidget().doWork();
}

#endif