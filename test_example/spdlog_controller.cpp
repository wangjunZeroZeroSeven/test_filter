#include "spdlog_controller.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <mutex>
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace {

constexpr auto QUEUE_SIZE = 8192;
constexpr auto COMMON_LOGGER_NAME = "common_logger_name";
constexpr auto ROTATING_MAX_FILE_SIZE = 100*1024*1024;
constexpr auto ROTATING_MAX_FILES_NUM = 5;

// a controller that create and cache different file sinks.
class FileSinkController {
public:
    FileSinkController()
    {
        spdlog::init_thread_pool(QUEUE_SIZE, 1); // init global thread pool, one thread can keep sequence.
    }

    FileSinkPtr GetFileSink(const std::string& filename)
    {
        std::lock_guard<std::mutex> lock(mutex);

        std::string file_path = GetFilePath(filename);

        // we use std::filesystem::canonical to standardize a path, but it requires on that path exists a file.
        bool log_file_exists = true;
        try {
            file_path = std::filesystem::canonical(file_path).string();
        }
        catch (std::filesystem::__cxx11::filesystem_error& err) {
            // file does not exist
            log_file_exists = false;
        }

        if (log_file_exists) {
            auto iter = cache.find(file_path);
            if (iter != cache.end()) {
                FileSinkPtr sink = iter->second.lock();
                if (sink) {
                    return sink;
                }
            }

            FileSinkPtr sink = CreateFileSink(file_path);
            cache[file_path] = sink;
            return sink;
        }
        else {
            // log file doesn't exist currently.
            FileSinkPtr sink = CreateFileSink(file_path);
            file_path = std::filesystem::canonical(file_path).string();
            cache[file_path] = sink;
            return sink;
        }
    }

private:
    // use weak_ptr to observe actual reference count.
    std::unordered_map<std::string, std::weak_ptr<FileSink>> cache;
    std::mutex mutex;

    // create a new file sink.
    FileSinkPtr CreateFileSink(const std::string& file_path)
    {
        try {
            return std::make_shared<FileSink>(file_path, ROTATING_MAX_FILE_SIZE, ROTATING_MAX_FILES_NUM);
        }
        catch (const spdlog::spdlog_ex& ex) {
            throw std::invalid_argument("CreateFileSink failed with file path (" + file_path + "), exception (" + ex.what() + ")");
        }
    }

    // get the not standard path
    std::string GetFilePath(std::string filename)
    {
        if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".log") {
            filename += ".log";
        }

        if (filename[0] == '/') {
        }
        else {
            filename = "./log/" + filename;
        }

        return filename;
    }
};
FileSinkController file_sink_controller;    // singleton

}

Sinker::Sinker(std::string_view filename) {
    curr_sink = file_sink_controller.GetFileSink(filename.data());
}

SpdLogger GetSpdLogger(const std::string& filename,
                       bool console,
                       spdlog::level::level_enum file_log_level,
                       const std::string& file_format,
                       spdlog::level::level_enum console_log_level,
                       const std::string& console_format)
{
    std::vector<spdlog::sink_ptr> sinks;

    if (!filename.empty()) {
        spdlog::sink_ptr fileSink = file_sink_controller.GetFileSink(filename);
        fileSink->set_level(file_log_level);
        fileSink->set_pattern(file_format);
        sinks.emplace_back(std::move(fileSink));
    }

    if (console) {
        spdlog::sink_ptr stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        stdout_sink->set_level(console_log_level);
        stdout_sink->set_pattern(console_format);
        sinks.emplace_back(std::move(stdout_sink));
    }

    if (sinks.empty()) {
        throw "GetSpdLogger failed: no sink!";
    }

    // all loggers use asynchronous mode and use one common thread.
    std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::async_logger>(COMMON_LOGGER_NAME, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    return logger;
}