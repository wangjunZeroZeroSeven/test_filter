#ifndef __SPDLOG_CONTROLLER__
#define __SPDLOG_CONTROLLER__

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <string_view>

// the actual default format of spdlog is "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v", but we have the same logger name, so we remove [%n]
constexpr auto DEFAULT_FORMAT = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";

// a class which wraps std::shared_ptr<spdlog::logger>
class SpdLogger {
public:
    SpdLogger(std::shared_ptr<spdlog::logger> i_logger)
    {
        logger = i_logger;
    }

    template<typename FormatString, typename... Args>
    void trace(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void debug(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void info(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void warn(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void error(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void critical(const FormatString& fmt, Args&&... args)
    {
        logger->log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }

private:
    std::shared_ptr<spdlog::logger> logger;
};

// represent a file or some other output
class Sinker {
public:
    Sinker(std::string_view filename);

    void setLevel(spdlog::level::level_enum log_level) {
        curr_sink->set_level(log_level);
    }

    void setPattern(const std::string &pattern) {
        curr_sink->set_pattern(pattern);
    }

    spdlog::level::level_enum getLevel() const
    {
        return curr_sink->level();
    }

private:
    spdlog::sink_ptr curr_sink;
};


/*
    create a logger from sinks. 
    the {filename}.log file exists in build/log directory.
    the logger object you get support multithreaded context. 
    if you need to use the same logger at different places, just call this function at difference places and it will generate different loggers which use the same sink in their implementation. as they use the same sink, better to call this function with the same file log param because the later will overwrite the former. 
    
    issue: https://gitlab.com/synsense-sys-int/samna/-/issues/628.
    for more info, you could see: https://github.com/gabime/spdlog
*/
SpdLogger GetSpdLogger(const std::string& filename,
                       bool console = false, 
                       spdlog::level::level_enum file_log_level = spdlog::level::trace,
                       const std::string& file_format = DEFAULT_FORMAT,
                       spdlog::level::level_enum console_log_level = spdlog::level::trace,
                       const std::string& console_format = DEFAULT_FORMAT);

#endif