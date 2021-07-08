#ifndef __TEST_WEAK_PTR_H__
#define __TEST_WEAK_PTR_H__

#include <memory>
#include <iostream>

void observe(std::weak_ptr<int> weak) 
{
    if (auto observe = weak.lock()) {
        std::cout << "\tobserve() able to lock weak_ptr<>, value=" << *observe << ", use cout=" << observe.use_count() << "\n";
    } else {
        std::cout << "\tobserve() unable to lock weak_ptr<>\n";
    }
}
 
void test_weak_ptr()
{
    std::weak_ptr<int> weak;
    std::weak_ptr<int> weak2;
    std::cout << "weak_ptr<> not yet initialized\n";
    observe(weak);
    observe(weak2);
 
    {
        auto shared = std::make_shared<int>(42);
        weak = shared;
        weak2 = weak;
        std::cout << "weak_ptr<> initialized with shared_ptr.\n";
        observe(weak);
        observe(weak2);
    }
 
    std::cout << "shared_ptr<> has been destructed due to scope exit.\n";
    observe(weak);
    observe(weak2);
}


#endif