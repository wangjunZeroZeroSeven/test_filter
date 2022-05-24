#ifndef VIRTUAL_METHOD_H_
#define VIRTUAL_METHOD_H_

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

class Base {
public:
    Base() {
        startRun();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "==== constructed base" << std::endl;
    }

    void run() {
        while (alive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            f();
        }
    }

    void startRun()
    {
        // Make sure the previous thread is started before creating a new one
        stopRun();

        alive = true;
        rwThread = std::thread([this](){ 
            while (alive) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                f();
            }
        });
    }

    void stopRun()
    {
        alive = false;
        if (rwThread.joinable()) {
            rwThread.join();
        }
    }

    virtual ~Base() {
        std::cout << "==== begin to destruct base" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        stopRun();
    }

private:
    std::atomic_bool alive = false;
    std::thread rwThread;

    virtual void f() {
        std::cout << "base function is called." << std::endl;
    }
};

class Derived: public Base {
private:
    virtual void f() override {
        // bool ret = alive;    // can't visit private member!
        std::cout << "derived function is called." << std::endl;
    }
};

void test_virtual_method() {
    Derived d;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

#endif