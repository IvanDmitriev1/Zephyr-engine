export module Zephyr.Core.CoreTypes;

export import zephyr.logging.LogHelpers;

export import Zephyr.Core.BuildConfig;
export import std;

export namespace Zephyr
{
	inline void DebugBreak()
	{
#ifdef _DEBUG
	#ifdef Zephyr_PLATFORM_WINDOWS
		__debugbreak();
	#endif
#endif
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
		requires std::constructible_from<T, Args...>
	[[nodiscard]] constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
		requires std::constructible_from<T, Args...>
	[[nodiscard]] constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<class To, class From>
	concept Related = std::is_base_of_v<From, To> || std::is_base_of_v<To, From>;

	template<class From>
	concept Polymorphic = std::is_polymorphic_v<From>;

	template <class To, class From>
		requires Related<To, From> && Polymorphic<From>
	[[nodiscard]] constexpr inline To& StaticCastRef(const Ref<From>& from)
	{
		if constexpr (Zephyr::Build::SafeCast)
		{
			if (auto* p = dynamic_cast<To*>(from.get()))
			{
				return *p;
			}

			DebugBreak();
			throw std::bad_cast{};
		}
		else
		{
			return static_cast<To&>(*from);
		}
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
		if constexpr (!Zephyr::Build::EnableAsserts)
		{
			return;
		}

		if (static_cast<bool>(condition))
			return;

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