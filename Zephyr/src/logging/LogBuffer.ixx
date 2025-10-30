export module zephyr.logging.LogBuffer;

export import zephyr.logging.Log;

export namespace zephyr
{
	class LogBuffer
	{
	public:
		class LockedView
		{
		public:
			LockedView(const LogBuffer& buffer)
				: m_Lock(buffer.m_Mutex)
				, m_Logs(buffer.m_Logs)
			{
			}

			auto begin() const
			{
				return m_Logs.begin();
			}

			auto end() const
			{
				return m_Logs.end();
			}

			
			size_t size() const
			{
				return m_Logs.size();
			}

			bool empty() const
			{
				return m_Logs.empty();
			}

			const LogEntry& operator[](size_t index) const
			{
				return m_Logs[index];
			}

		private:
			std::shared_lock<std::shared_mutex> m_Lock;
			const std::vector<LogEntry>& m_Logs;
		};

	public:
		LogBuffer(size_t capacity = 8000);
		~LogBuffer() = default;

		LogBuffer(const LogBuffer&) = delete;
		LogBuffer& operator=(const LogBuffer&) = delete;

	public:
		void AddLog(LogEntry&& message);
		void Clear();
		size_t GetSize() const;

		LockedView GetView() const
		{
			return LockedView(*this);
		}

	private:
		mutable std::shared_mutex m_Mutex;
		std::vector<LogEntry> m_Logs;
		const size_t m_Capacity;
	};
}