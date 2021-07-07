#include <iostream>
//#include "example.h"
// #include "test_stl/variant.h"
// #include "test_example/throw.h"
// #include "test_stl/test_struct.h"
// #include "test_tools/string_formater"
// #include "test_stl/assert.h"
// #include "test_stl/visit_variant.h"
// #include "test_stl/bind.h"
// #include "test_example/method_pointer.h"
// #include "test_example/one_method_override_same_two.h"
// #include "test_example/test_spdlog.h"
#include "test_example/spdlog_controller.h"
#include "test_example/defer_task.h"
#include <filesystem>
#include <strstream>

int main(int, char**) {
    test_defer_task();

    auto logger = GetSpdLogger("bbb", true);
    logger.info("format string {}, {}, {}", 1, 3.5, "abc");

    // std::filesystem::path p1 = "./log/aaa.log";
    // std::filesystem::path p2 = "log/aaa.log";
    // std::filesystem::path p3 = "/home/synsense/projects/test_filter/build/log/aaa.log";
    // try {
    //     std::cout << "p1 == p3: " << std::filesystem::equivalent(p1, p3) << std::endl;
    // }
    // catch (const std::filesystem::__cxx11::filesystem_error& ex) {
    //     std::cout << "throw exception111: " << ex.what() << std::endl;
    // }

    auto logger2 = GetSpdLogger("bbb", true);
    logger2.info("it's the beginning.");
    logger2.warn("format string {}, {}, {}", 1, 3.5, "abc");

    // logger.warn("111");
    // logger2.warn("333");

    //std::this_thread::sleep_for(std::chrono::minutes(1));
    return 0;
}
