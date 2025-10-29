module;

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

export module zephyr.logging.LogHelpers;

export import zephyr.logging.Log;

export namespace zephyr::log
{
    constexpr LogLevel ConvertLogLevel(spdlog::level::level_enum level)
    {
        switch (level)
        {
		case spdlog::level::trace:    return LogLevel::Trace;
		case spdlog::level::debug:    return LogLevel::Debug;
		case spdlog::level::info:     return LogLevel::Info;
		case spdlog::level::warn:     return LogLevel::Warning;
		case spdlog::level::err:      return LogLevel::Error;
		case spdlog::level::critical: return LogLevel::Critical;
        default:                      return LogLevel::Info;
        }
    }

    constexpr spdlog::level::level_enum ConvertLogLevel(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Trace:    return spdlog::level::trace;
        case LogLevel::Debug:    return spdlog::level::debug;
        case LogLevel::Info:     return spdlog::level::info;
        case LogLevel::Warning:  return spdlog::level::warn;
        case LogLevel::Error:    return spdlog::level::err;
        case LogLevel::Critical: return spdlog::level::critical;
        case LogLevel::Off:      return spdlog::level::off;
        default:                 return spdlog::level::info;
        }
    }

    template<typename... Args>
    inline void Trace(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetEngineLogger()->trace(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Info(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetEngineLogger()->info(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Warn(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetEngineLogger()->warn(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Error(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetEngineLogger()->error(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Critical(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetEngineLogger()->critical(fmt::format(fmt, std::forward<Args>(args)...));
    }
}

export namespace zephyr::applog
{
    template<typename... Args>
    inline void Trace(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetAppLogger()->trace(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Info(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetAppLogger()->info(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Warn(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetAppLogger()->warn(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Error(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetAppLogger()->error(fmt::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void Critical(fmt::format_string<Args...> fmt, Args&&... args)
    {
        Log::GetAppLogger()->critical(fmt::format(fmt, std::forward<Args>(args)...));
    }
}