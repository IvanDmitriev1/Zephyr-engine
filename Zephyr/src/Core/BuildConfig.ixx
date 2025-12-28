export module Zephyr.Core.BuildConfig;

export namespace Zephyr::Build
{
#if _DEBUG
	inline constexpr bool EnableAsserts = true;
	inline constexpr bool SafeCast = true;
#else
	inline constexpr bool EnableAsserts = false;
	inline constexpr bool SafeCast = false;
#endif // NDEBUG
}