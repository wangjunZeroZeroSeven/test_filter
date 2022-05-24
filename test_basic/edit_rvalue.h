#ifndef EDIT_RVALUE_H_
#define EDIT_RVALUE_H_

#include <vector>
#include <iostream>

void printVec(std::vector<int>&& vec) {
    std::cout << " ";
    for (auto& i: vec) {
        std::cout << i << " ,";
    }
    std::cout << std::endl;
}

void editVec(std::vector<int>&& vec) {
    vec.push_back(55);
    printVec(std::move(vec));
}

class A : public std::vector<int> {
public:
    A() {
        std::cout << "A 's default constructor called !" << std::endl;
    }

    A(A&& c) {
        std::cout << "A 's move constructor called !" << std::endl;
    }

    A(const A& c) {
        std::cout << "A 's copy constructor called !" << std::endl;
    }

    A& operator= (const A&) {
        std::cout << "A 's copy assignment called !" << std::endl;
        return *this;
    }

    A& operator= (A&&) {
        std::cout << "A 's move assignment called !" << std::endl;
        return *this;
    }

    void print() const {
        std::cout << "A 's print method" << std::endl;
    }

    void edit() {
        r = 5;
        std::cout << "A 's edit method" << std::endl;
    }

private:
    int r;
};

void testA1(A a) {
    a.print();
    a.edit();
}

void testA2(const A& a) {
    a.print();
}

void testA3(A&& a) {
    a.print();
    a.edit();
}

void test_edit_rvalue() {
    std::vector<int> vec = {1,2,3,4};
    editVec(std::move(vec));

    A a1;
    testA1(std::move(a1));

    A a2;
    testA2(std::move(a2));

    A a3;
    testA3(std::move(a3));
}

#endif