#ifndef __TEST_SPDLOG_H__
#define __TEST_SPDLOG_H__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <filesystem>

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

void test_spdlog()
{
    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Hello, {}123!", "World");

    // one logger write to more than one sinks.
    std::vector<spdlog::sink_ptr> sinks;
    spdlog::sink_ptr sink1 = std::make_shared<spdlog::sinks::stdout_sink_st>();
    sinks.push_back(sink1);
    spdlog::sink_ptr sink2 = std::make_shared<spdlog::sinks::daily_file_sink_st>("logfile", 23, 59);
    sinks.push_back(sink2);
    auto combined_logger = std::make_shared<spdlog::logger>("name", begin(sinks), end(sinks));
    //register it if you need to access it globally
    spdlog::register_logger(combined_logger);
    combined_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    combined_logger->info("test 123456789");


    std::filesystem::path cwd = std::filesystem::current_path() / "log" / "abc.txt";
    std::string sss = cwd.string();
    int a = 0;

    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async_log.txt");

}

#endif