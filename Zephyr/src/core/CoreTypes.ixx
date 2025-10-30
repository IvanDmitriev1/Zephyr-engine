export module zephyr.core.coreTypes;

export import zephyr.logging.LogHelpers;

export namespace zephyr
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	[[nodiscard]] constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	[[nodiscard]] constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


	inline void DebugBreak()
	{
#ifdef _DEBUG
	#ifdef Zephyr_PLATFORM_WINDOWS
		__debugbreak();
	#endif
#endif
	}

	inline void Assert(bool condition, std::string_view message,
		std::source_location location = std::source_location::current())
	{
		if (condition)
		{
			return;
		}

		zephyr::log::Critical(
			"Assertion failed: {} at {}:{}",
			message,
			location.file_name(),
			location.line());

		DebugBreak();
		throw std::runtime_error(std::string(message));
	}
}