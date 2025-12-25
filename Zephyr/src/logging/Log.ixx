module;

#include <spdlog/spdlog.h>

export module zephyr.logging.Log;

export import std;

export namespace Zephyr
{
	enum class LogLevel
	{
		Trace = 1,
		Debug,
		Info,
		Warning,
		Error,
		Critical,
		Off
	};

	struct LogEntry
	{
		LogEntry() = default;
		~LogEntry() = default;

		LogEntry(const LogEntry&) = delete;
		LogEntry& operator=(const LogEntry&) = delete;

		LogEntry(LogEntry&&) = default;
		LogEntry& operator=(LogEntry&&) = default;

		LogLevel Level;
		std::string Message;
	};

	class Log
	{
	public:
		using LoggerType = std::shared_ptr<spdlog::logger>;

		static void Initialize(
			LoggerType engineLogger,
			LoggerType appLogger)
		{
			s_EngineLogger = engineLogger;
			s_AppLogger = appLogger;
		}

		static void Shutdown()
		{
			if (s_EngineLogger)
			{
				spdlog::drop(s_EngineLogger->name());
				s_EngineLogger.reset();
			}

			if (s_AppLogger)
			{
				spdlog::drop(s_AppLogger->name());
				s_AppLogger.reset();
			}
		}


		static LoggerType& GetEngineLogger()
		{
			return s_EngineLogger;
		}

		static LoggerType& GetAppLogger()
		{
			return s_AppLogger;
		}

	private:
		inline static LoggerType s_EngineLogger;
		inline static LoggerType s_AppLogger;
	};
}