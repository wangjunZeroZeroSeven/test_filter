#ifndef __SPDLOG_CONTROLLER__
#define __SPDLOG_CONTROLLER__

#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <map>
#include <string_view>

// the default format of spdlog, note that the logger's name %n is replaced by module name.
constexpr auto DEFAULT_FORMAT = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v";

// all modules, every time we add new module we must add value to LOG_MODULE and MODULE_NAME_ARR.
enum class LOG_MODULE : uint16_t {
    DEFAULT_MODULE,

    MODULE_COUNT
};

// module names to write before every message, it msut keep the same order of LOG_MODULE enumerator.
constexpr std::array MODULE_NAME_ARR{
    "default"};

// C++ interface :

// a logger class for each module.
class ModuleLogger {
public:
    ModuleLogger(LOG_MODULE i_module) :
        curr_module(i_module)
    {
        if (curr_module == LOG_MODULE::MODULE_COUNT) {
            throw std::invalid_argument("construct ModuleLogger ERROR: invalid i_module!");
        }
    }

    LOG_MODULE getModule()
    {
        return curr_module;
    }

    std::string getModuleName()
    {
        return MODULE_NAME_ARR.at(static_cast<std::underlying_type_t<LOG_MODULE>>(curr_module));
    }

    template<typename FormatString, typename... Args>
    void log(spdlog::level::level_enum lvl, const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(lvl, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void trace(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void debug(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void info(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void warn(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void error(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void critical(const FormatString& fmt, Args&&... args)
    {
        getLogger()->log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }

    void flush()
    {
        getLogger()->flush();
    }

private:
    const LOG_MODULE curr_module;

    std::shared_ptr<spdlog::logger> getLogger();
};

void initModuleLogger();    // init spdlogger globally, call this when program start.

// python interface :

// represent a file or some other output
class Sink {
    friend class SinksController;

public:
    enum class SinkType {
        FileSink,
        ConsoleSink,
        ConsoleErrSink
    };

    SinkType getSinkType()
    {
        return sink_type;
    }

    std::string getOriginFileName()
    {
        return originFileName;
    }

    std::string getAbsoluteFilePath()
    {
        return absoluteFilePath;
    }

    void setLevel(spdlog::level::level_enum log_level)
    {
        base_sink->set_level(log_level);
    }

    void setPattern(const std::string& pattern)
    {
        base_sink->set_pattern(pattern);
    }

    spdlog::level::level_enum getLevel() const
    {
        return base_sink->level();
    }

private:
    spdlog::sink_ptr base_sink;
    SinkType sink_type = SinkType::FileSink;
    std::string originFileName;
    std::string absoluteFilePath;
};

// a class that controll sinks.
class SinksController {
    friend class ModuleLogger;

public:
    static SinksController& getInstance()
    {
        static SinksController instance;
        return instance;
    }

    /*
        the {filename}.log file will be created in the current directory, the filename param also support relative path and absolute path. 
        e.g. "./log/aaa.log" will create a log directory and aaa.log in that directory for you automatically.
    */
    Sink createFileSink(std::string_view filename);
    Sink createConsoleSink();
    Sink createConsoleErrSink();

    // configure a logger to user some sinks.
    void configureSinks(const std::vector<Sink>& sinks);

    std::vector<Sink> getCurrSinks();

private:
    SinksController() = default;
    SinksController(SinksController&&);

    std::shared_ptr<spdlog::logger> getLogger(LOG_MODULE i_module);

    std::mutex mutex; // lock all variables.
    std::vector<Sink> curr_sinks;
    // every module has a logger, they use common sinks.
    std::array<std::shared_ptr<spdlog::logger>, static_cast<std::underlying_type_t<LOG_MODULE>>(LOG_MODULE::MODULE_COUNT)> module_loggers;
};

#endif