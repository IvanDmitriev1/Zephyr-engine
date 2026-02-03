export module Zephyr.Core.Assert;

export import zephyr.logging.LogHelpers;
export import Zephyr.Core.BuildConfig;

namespace Zephyr
{
	[[noreturn]] inline void FailAssert(
		std::string_view message,
		std::source_location location)
	{
		Zephyr::log::Critical(
			"Assertion failed: {} at {}:{}",
			message,
			location.file_name(),
			location.line());

		Build::DebugBreak();
		throw std::runtime_error(std::string(message));
	}

	template<class T>
	concept BoolThunk =
		std::invocable<T&> && std::convertible_to<std::invoke_result_t<T&>, bool>;

	template<class T>
	concept BoolTestable =
		requires(T && t)
	{
		{ static_cast<bool>(std::forward<T>(t)) } -> std::same_as<bool>;
	};

	export inline void Assert(
		bool condition,
		std::string_view message,
		std::source_location location = std::source_location::current())
	{
		if constexpr (!Zephyr::Build::EnableAsserts)
			return;

		if (condition)
			return;

		FailAssert(message, location);
	}

	export template<BoolTestable T>
		requires (!std::invocable<std::remove_reference_t<T>&>)
	inline void Assert(
		T&& condition,
		std::string_view message,
		std::source_location location = std::source_location::current())
	{
		if constexpr (!Zephyr::Build::EnableAsserts)
			return;

		if (static_cast<bool>(std::forward<T>(condition)))
			return;

		FailAssert(message, location);
	}

	export template <BoolThunk ConditionFn>
	inline void Assert(
		ConditionFn&& conditionFn,
		std::string_view message,
		std::source_location location = std::source_location::current())
	{
		if constexpr (!Zephyr::Build::EnableAsserts)
			return;

		if (static_cast<bool>(std::invoke(conditionFn)))
			return;

		FailAssert(message, location);
	}

	export [[noreturn]] inline void Unreachable()
	{
		Build::DebugBreak();
		std::unreachable();
	}
}