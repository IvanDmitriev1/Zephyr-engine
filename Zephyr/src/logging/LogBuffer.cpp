module zephyr.logging.LogBuffer;

namespace Zephyr
{
	LogBuffer::LogBuffer(size_t capacity)
		: m_Capacity(capacity)
	{
		m_Logs.reserve(capacity);
	}

	void LogBuffer::AddLog(LogEntry&& message)
	{
		std::unique_lock lock(m_Mutex);

		m_Logs.push_back(std::move(message));

		if (m_Logs.size() > m_Capacity)
		{
			m_Logs.erase(m_Logs.begin(), m_Logs.begin() + (m_Logs.size() - m_Capacity));
		}
	}

	void LogBuffer::Clear()
	{
		std::unique_lock lock(m_Mutex);
		m_Logs.clear();
	}

	size_t LogBuffer::GetSize() const
	{
		std::shared_lock lock(m_Mutex);
		return m_Logs.size();
	}
}