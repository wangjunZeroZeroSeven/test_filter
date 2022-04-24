#ifndef __ASYNC_H__
#define __ASYNC_H__

#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void waitLong() {
    std::cout << "wait begin" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "wait end." << std::endl;
}

void test_async() {
    {
        std::cout << "test destructor of no taker of std::async :" << std::endl;
        const auto begin = std::chrono::steady_clock::now();
        std::async(std::launch::async, waitLong);
        const auto millsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
        std::cout << "last milliseconds: " << millsec << std::endl;
    }

    {
        std::cout << "test default destructor of the std::future of std::async's return :" << std::endl;
        const auto begin = std::chrono::steady_clock::now();
        auto fut = std::async(std::launch::async, waitLong);
        const auto millsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
        std::cout << "last milliseconds: " << millsec << std::endl;
    }
    std::cout << "run over" << std::endl;
}


#endif