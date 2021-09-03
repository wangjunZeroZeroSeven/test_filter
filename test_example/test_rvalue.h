#ifndef __TEST_RIGHT_VALUE_H__
#define __TEST_RIGHT_VALUE_H__

#include <iostream>

class Matrix {
public:
    Matrix(int value) : value(value) {
        std::cout << "init by int" << std::endl;
    }

    Matrix(Matrix&& m) {
        std::cout << "move constructor" << std::endl;
    }

    Matrix(const Matrix& m) {
        std::cout << "copy constructor" << std::endl;
    }

    void operator+=(const Matrix& m) {
        this->value += m.value;
    }

public:
    int value = 0;
};

Matrix
operator+(Matrix&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return std::move(lhs);
}

Matrix
operator*(Matrix&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return lhs;
}



template<typename T>
Matrix
operator-(T&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return std::forward<T>(lhs);
}

template<typename T>
Matrix
operator/(T&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return lhs;
}

void test_rvalue_param_return() {
    Matrix rhs(1);

    auto m_move = Matrix(1) + rhs;
    auto m_copy = Matrix(1) * rhs;
}

void test_universal_param_return() {
    Matrix lhs(1);
    Matrix rhs(1);

    auto m_move = Matrix(1) - rhs;
    auto m_copy = Matrix(1) / rhs;

    auto m_copy1 = lhs - rhs;
    auto m_copy2 = lhs / rhs;
}

/////////////////////////////////test return value optimization (RVO)/////////////////////////////////

Matrix make_matrix_local_variable() {
    Matrix lhs(1);
    lhs += Matrix(2);
    return lhs;
}

Matrix make_matrix_input_value(Matrix lhs) {
    lhs += Matrix(2);
    return lhs;
}

Matrix make_matrix_return_constructor() {
    Matrix lhs(1);
    lhs += Matrix(2);
    return lhs.value;
}

void test_RVO() {
    std::cout << "1111" << std::endl;
    auto m_move1 = make_matrix_local_variable();
    std::cout << "2222" << std::endl;
    auto m_move2 = make_matrix_input_value(1);
    std::cout << "3333" << std::endl;
    auto m_move3 = make_matrix_return_constructor();
}

#endif