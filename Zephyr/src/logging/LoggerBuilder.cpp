module;

#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef ZEPHYR_PLATFORM_WINDOWS
	#include "spdlog/sinks/msvc_sink.h"
#endif //ZEPHYR_PLATFORM_WINDOWS

module zephyr.logging.LoggerBuilder;

import zephyr.logging.LogHelpers;

import <spdlog/spdlog.h>;

namespace Zephyr
{
	LoggerBuilder::LoggerBuilder()
	{
		AddSink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

		#ifdef ZEPHYR_PLATFORM_WINDOWS
		AddSink(std::make_shared<spdlog::sinks::msvc_sink_mt>());
		#endif //ZEPHYR_PLATFORM_WINDOWS
	}

	LoggerBuilder& LoggerBuilder::SetName(std::string_view loggerName)
	{
		m_LoggerName = std::string(loggerName);
		return *this;
	}

	LoggerBuilder& LoggerBuilder::SetLevel(LogLevel level)
	{
		m_Level = level;
		return *this;
	}

	LoggerBuilder& LoggerBuilder::SetPattern(std::string_view pattern)
	{
		m_Pattern = std::string(pattern);
		return *this;
	}

	LoggerBuilder& LoggerBuilder::AddSink(const std::shared_ptr<spdlog::sinks::sink>& sink)
	{
		m_Sinks.push_back(sink);
		return *this;
	}

	LoggerBuilder& LoggerBuilder::ClearSinks()
	{
		m_Sinks.clear();
		return *this;
	}

	Log::LoggerType LoggerBuilder::Build()
	{
		for (auto& sink : m_Sinks)
		{
			sink->set_pattern(m_Pattern);
		}

		auto logger = std::make_shared<spdlog::logger>(
			m_LoggerName,
			m_Sinks.begin(),
			m_Sinks.end());

		logger->set_level(log::ConvertLogLevel(m_Level));
		logger->flush_on(log::ConvertLogLevel(LogLevel::Trace));

		spdlog::register_logger(logger);

		return logger;
	}
}
