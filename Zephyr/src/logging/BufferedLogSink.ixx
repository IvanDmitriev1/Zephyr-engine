module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

export module zephyr.logging.BufferedLogSink;

export import zephyr.logging.LogHelpers;
export import zephyr.logging.LogBuffer;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	class BufferedLogSink : public spdlog::sinks::base_sink<std::mutex>
	{
	public:
		BufferedLogSink(Ref<LogBuffer> logBuffer)
			:m_logBuffer(std::move(logBuffer))
		{
			
		}

		~BufferedLogSink() override = default;

		BufferedLogSink(const BufferedLogSink&) = delete;
		BufferedLogSink& operator=(const BufferedLogSink&) = delete;

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			this->formatter_->format(msg, formatted);

			LogEntry entry;
			entry.Level = log::ConvertLogLevel(msg.level);
			entry.Message = std::string(formatted.data(), formatted.size());

			m_logBuffer->AddLog(std::move(entry));
		}

		void flush_() override
		{
		}

	private:
		const Ref<LogBuffer> m_logBuffer;
	};
}