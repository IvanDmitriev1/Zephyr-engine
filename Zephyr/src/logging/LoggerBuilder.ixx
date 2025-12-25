module;

#include <spdlog/spdlog.h>

export module zephyr.logging.LoggerBuilder;

export import zephyr.logging.Log;

export namespace Zephyr
{
	class LoggerBuilder
	{
	public:
		LoggerBuilder();
		~LoggerBuilder() = default;

		LoggerBuilder(const LoggerBuilder&) = delete;
		LoggerBuilder& operator=(const LoggerBuilder&) = delete;

		LoggerBuilder(LoggerBuilder&&) = default;
		LoggerBuilder& operator=(LoggerBuilder&&) = default;

	public:
		LoggerBuilder& SetName(std::string_view loggerName);
		LoggerBuilder& SetLevel(LogLevel level);
		LoggerBuilder& SetPattern(std::string_view pattern);

		LoggerBuilder& AddSink(const std::shared_ptr<spdlog::sinks::sink>& sink);
		LoggerBuilder& ClearSinks();

		Log::LoggerType Build();

	private:
		std::string m_LoggerName = "Default logger name";
		LogLevel m_Level = LogLevel::Info;
		std::string m_Pattern = "%^[%T] [%n] %v%$";
		std::vector<std::shared_ptr<spdlog::sinks::sink>> m_Sinks;
	};
}

