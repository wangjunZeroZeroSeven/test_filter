#include <iostream>
#include <chrono>
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
// #include "test_example/defer_task.h"
// #include <filesystem>
// #include <strstream>

int main(int, char**) {

    initModuleLogger();

    ModuleLogger logger(LOG_MODULE::DEFAULT_MODULE);
    logger.info("format string {}, {}, {}", 1, 3.5, "abc");

    auto sink = SinksController::getInstance().createFileSink("samna2");
    SinksController::getInstance().configureSinks({sink});

    auto logger2 = logger;
    logger2.info("abccccccccccc");

    //std::this_thread::sleep_for(std::chrono::seconds(60));

    // logger.log(spdlog::logger::info, "aaaaaa");

    // logger.log(spdlog::logger::info, "format string {}, {}, {}", 1, 3.5, "abc");

    // auto logger2 = GetSpdLogger("bbb", true);
    // logger2.log(spdlog::logger::info, "it's the beginning.");
    // logger2.log(spdlog::logger::warn, "format string {}, {}, {}", 1, 3.5, "abc");



    return 0;
}
