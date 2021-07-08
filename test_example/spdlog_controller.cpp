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

// init spdlogger globally.
void initSpdLogger() {
    std::vector<Sink> sinks;
    auto& sinksController = SinksController::getInstance();

    spdlog::init_thread_pool(QUEUE_SIZE, 1); // init global thread pool, one thread can keep sequence.

    Sink fileSink = sinksController.createFileSink("samna");
    fileSink.setLevel(spdlog::level::info);
    sinks.emplace_back(std::move(fileSink));

    Sink consoleErrSink = sinksController.createConsoleErrSink();
    consoleErrSink.setLevel(spdlog::level::err);
    sinks.emplace_back(std::move(consoleErrSink));

    sinksController.configureSinks(sinks);
}

// a controller singleton that create and cache different file sinks. it can recognize duplicate sinks.
class FileSinkController {
public:
    static FileSinkController& getInstance() {
        static FileSinkController instance;
        return instance;
    }

    // return sink and absolute path
    std::pair<spdlog::sink_ptr, std::string> getFileSink(const std::string& filename)
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
                spdlog::sink_ptr sink = iter->second.lock();
                if (sink) {
                    return std::make_pair(sink, file_path);
                }
            }

            spdlog::sink_ptr sink = CreateFileSink(file_path);
            cache[file_path] = sink;
            return std::make_pair(sink, file_path);
        }
        else {
            // log file doesn't exist currently.
            spdlog::sink_ptr sink = CreateFileSink(file_path);
            file_path = std::filesystem::canonical(file_path).string();
            cache[file_path] = sink;
            return std::pair(sink, file_path);
        }
    }

    void clearExpired() {
        std::lock_guard<std::mutex> lock(mutex);

        for (auto iter = cache.cbegin(); iter != cache.cend();) {
            if (iter->second.expired()) {
                iter = cache.erase(iter);
            }
            else {
                iter++;
            }
        }
    }

private:
    FileSinkController() = default;

    // create a new file sink.
    spdlog::sink_ptr CreateFileSink(const std::string& file_path)
    {
        try {
            return std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_path, ROTATING_MAX_FILE_SIZE, ROTATING_MAX_FILES_NUM);
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
        return filename;
    }

    // use weak_ptr to observe actual reference count.
    std::mutex mutex;
    std::unordered_map<std::string, std::weak_ptr<spdlog::sinks::sink>> cache;
};

}

Sink SinksController::createFileSink(std::string_view filename) {
    // because python users may edit sink's log level or output format, so we use multi threaded sink(_mt).
    Sink fileSink;
    fileSink.sink_type = Sink::SinkType::FileSink;
    fileSink.originFileName = filename;
    std::tie(fileSink.base_sink, fileSink.absoluteFilePath) = FileSinkController::getInstance().getFileSink(filename.data());
    fileSink.base_sink->set_pattern(DEFAULT_FORMAT);
    return fileSink;
}

Sink SinksController::createConsoleSink() {
    Sink consoleSink;
    consoleSink.sink_type = Sink::SinkType::ConsoleSink;
    consoleSink.base_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink.base_sink->set_pattern(DEFAULT_FORMAT);
    return consoleSink;
}

Sink SinksController::createConsoleErrSink() {
    Sink consoleErrSink;
    consoleErrSink.sink_type = Sink::SinkType::ConsoleErrSink;
    consoleErrSink.base_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    consoleErrSink.base_sink->set_pattern(DEFAULT_FORMAT);
    return consoleErrSink;
}

void SinksController::configureSinks(const std::vector<Sink>& sinks) {
    // because we cannot edit a logger's sinks during this logger is logging. so we drop the old logger and generate a new one instead.

    std::vector<spdlog::sink_ptr> base_sinks;

    if (sinks.empty()) {
        throw std::invalid_argument("configure sinks ERROR: no sinks at all!");
    }

    for (auto&sink: sinks) {
        base_sinks.emplace_back(sink.base_sink);
    }

    {
        auto* newLoggerRawPtr = new spdlog::async_logger(COMMON_LOGGER_NAME, base_sinks.begin(), base_sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        newLoggerRawPtr->flush_on(spdlog::level::err);  // when there appears an error msg, flush immediately.

        std::lock_guard<std::mutex> lock(mutex);
        // call the same std::shared_ptr object with reset method is not thread safe, we should put it in lock range.
        if (curr_logger) {
            curr_logger->flush();
        }
        curr_logger.reset(newLoggerRawPtr);
        curr_sinks = sinks;
    }

    // replace the old logger by reset
    FileSinkController::getInstance().clearExpired();
}

std::vector<Sink> SinksController::getCurrSinks() {
    std::lock_guard<std::mutex> lock(mutex);
    return curr_sinks;
}

std::shared_ptr<spdlog::logger> SinksController::getLogger() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (curr_logger) {
            return curr_logger;
        }
    }

    // not init spdlog yet
    initSpdLogger();

    {
        std::lock_guard<std::mutex> lock(mutex);
        return curr_logger;
    }
}