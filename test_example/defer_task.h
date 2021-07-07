#ifndef __DEFER_TASK_H__
#define __DEFER_TASK_H__

#include <functional>
#include <iostream>

class DeferTask {
    using Task = std::function<void()>;
public:
    DeferTask(const Task& i_task) {
        task = i_task;
    }

    ~DeferTask() {
        if (task) {
            task();
        }
    }

private:
    Task task;
};

void test_defer_task() {
    DeferTask task1([](){
        std::cout << "task1" << std::endl;
    });

    DeferTask task2([](){
        std::cout << "task2" << std::endl;
    });

    DeferTask task3([](){
        std::cout << "task3" << std::endl;
    });
}

#endif