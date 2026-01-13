export module Zephyr.Core.HashUtils;

import std.compat;

export namespace Zephyr::Unitls
{
	constexpr std::size_t kHashMagic = 0x9e3779b97f4a7c15ull;

	constexpr std::size_t Mix(std::size_t seed, std::size_t h) noexcept
	{
		return seed ^ (h + kHashMagic + (seed << 6) + (seed >> 2));
	}

	template <class T>
	inline std::size_t HashValue(const T& value) noexcept
	{
		return std::hash<std::remove_cvref_t<T>>{}(value);
	}

	export template <class... Ts>
	inline std::size_t HashCombine(const Ts&... xs) noexcept
	{
		std::size_t seed = 0;
		((seed = Mix(seed, HashValue(xs))), ...);
		return seed;
	}
}