export module Zephyr.Core.CoreTypes;

export import zephyr.logging.LogHelpers;

export namespace Zephyr
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


	template <class T>
	concept BoolTestable = requires(T && t)
	{
		{
			static_cast<bool>(std::forward<T>(t))
		} -> std::same_as<bool>;
	};

	template <BoolTestable Condition>
	inline void Assert(
		Condition&& condition,
		std::string_view message,
		std::source_location location = std::source_location::current())
	{
		if (static_cast<bool>(condition))
		{
			return;
		}

		Zephyr::log::Critical(
			"Assertion failed: {} at {}:{}",
			message,
			location.file_name(),
			location.line());

		DebugBreak();
		throw std::runtime_error(std::string(message));
	}

	template <std::unsigned_integral T = std::uint32_t>
	[[nodiscard]] constexpr T bit(uint32_t pos) noexcept
	{
		return T{ 1 } << pos;
	}

	template <typename C, typename M>
	[[nodiscard]] constexpr auto bind_event_fn(C* self, M method)
	{
		return std::bind_front(method, self);
	}
}