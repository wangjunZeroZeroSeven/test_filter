#ifndef TEST_DESTRUCTOR_H_
#define TEST_DESTRUCTOR_H_

#include <iostream>
#include <exception>

class A {
public:
    A() {
        std::cout << "== construct" << std::endl;
    }

    ~A() {
        std::cout << "== destruct" << std::endl;
    }
};

namespace detail {
enum class ScopeGuardMode {
    OnSuccess,
    OnFailure,
    OnExit
};
}

template<detail::ScopeGuardMode mode, typename Callable>
class ScopeGuard {
private:
    int count = std::uncaught_exceptions();
    Callable f;

public:
    ScopeGuard(Callable f) :
        f(f)
    {
    }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&&) = delete;

    virtual ~ScopeGuard()
    {
        if ((mode == detail::ScopeGuardMode::OnExit) ||
            (mode == detail::ScopeGuardMode::OnFailure && std::uncaught_exceptions() != count) ||
            (mode == detail::ScopeGuardMode::OnSuccess && std::uncaught_exceptions() == count)) {
            f();
        }
    }
};

template<typename Callable>
struct OnScopeFailure : public ScopeGuard<detail::ScopeGuardMode::OnFailure, Callable> {
    explicit OnScopeFailure(Callable&& f) :
        ScopeGuard<detail::ScopeGuardMode::OnFailure, Callable>(f) {}
};

template<typename Callable>
struct OnScopeSuccess : public ScopeGuard<detail::ScopeGuardMode::OnSuccess, Callable> {
    explicit OnScopeSuccess(Callable&& f) :
        ScopeGuard<detail::ScopeGuardMode::OnSuccess, Callable>(f) {}
};

template<typename Callable>
struct OnScopeExit : public ScopeGuard<detail::ScopeGuardMode::OnExit, Callable> {
    explicit OnScopeExit(Callable&& f) :
        ScopeGuard<detail::ScopeGuardMode::OnExit, Callable>(f) {}
};

void test_destructor() {
    {A b;}
    A a;
    OnScopeExit cleanup([](){
        std::cout << "Very Good!" << std::endl;
    });
    throw std::runtime_error("bad!!!");
}

void test_destructor2() {
    try {
        A a;
    }
    catch (const std::exception& e) {
        
    }
}

#endif