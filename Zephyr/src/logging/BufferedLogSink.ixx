module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

export module zephyr.logging.BufferedLogSink;

export import zephyr.logging.LogHelpers;

export namespace zephyr
{
	template<typename Mutex = std::mutex>
	class BufferedLogSink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
		BufferedLogSink(size_t max_entries = 10000)
			:m_MaxEntries(max_entries)
		{
			m_Logs.reserve(max_entries);
		}

		~BufferedLogSink() override = default;

		BufferedLogSink(const BufferedLogSink&) = delete;
		BufferedLogSink& operator=(const BufferedLogSink&) = delete;

	public:
		const std::vector<LogEntry>& GetLogs() const
		{
			return m_Logs;
		}

		void ClearLogs()
		{
			std::scoped_lock lock{ spdlog::sinks::base_sink<Mutex>::mutex_ };
			m_Logs.clear();
		}

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			this->formatter_->format(msg, formatted);

			LogEntry entry;
			entry.Level = log::ConvertLogLevel(msg.level);
			entry.TimeStamp = msg.time;
			entry.LoggerName = std::string(msg.logger_name.begin(), msg.logger_name.end());
			entry.Message = std::string(formatted.data(), formatted.size());

			m_Logs.push_back(std::move(entry));

			if (m_Logs.size() > m_MaxEntries)
			{
				m_Logs.erase(m_Logs.begin(), m_Logs.begin() + (m_Logs.size() - m_MaxEntries));
			}
		}

		void flush_() override
		{
		}

	private:
		std::vector<LogEntry> m_Logs;
		size_t m_MaxEntries;
	};
}