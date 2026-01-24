export module Zephyr.Core.CoreTypes;

export import zephyr.logging.LogHelpers;

export import Zephyr.Core.BuildConfig;
export import Zephyr.Core.Assert;
export import std;

export namespace Zephyr
{
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


	namespace detail
	{
		template<class Holder>
		constexpr auto* ptr(Holder&& holder) noexcept
		{
			if constexpr (std::is_pointer_v<std::remove_reference_t<Holder>>)
				return holder;                           // raw pointer
			else
				return std::forward<Holder>(holder).get(); // Ref/Scope/etc.
		}

		template<class Holder>
		using pointee_t = std::remove_pointer_t<decltype(ptr(std::declval<Holder&&>()))>;
	}

	template<class To, class From>
	concept Related = std::is_base_of_v<From, To> || std::is_base_of_v<To, From>;

	template<class To, class Holder>
		requires Related<To, detail::pointee_t<Holder>>
	[[nodiscard]] inline decltype(auto) StaticCast(Holder&& holder)
	{
		auto* p = detail::ptr(std::forward<Holder>(holder));
		Assert(p != nullptr, "StaticCast: null");

		using FromPointee = detail::pointee_t<Holder>;
		using Target = std::conditional_t<
			std::is_const_v<std::remove_reference_t<FromPointee>>,
			const To,
			To
		>;

		return *static_cast<Target*>(p); // To& or const To&
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