export module Zephyr.Renderer.Types.DrawCategory;

import std.compat;

export namespace Zephyr
{
	enum class DrawCategory : uint8_t
	{
		// Opaque geometry - rendered to GBuffer
		Opaque = 0,

		// e.g., foliage, fences with alpha cutout
		AlphaMasked,

		// e.g., glass, water, particles
		Transparent,

		Overlay
	};

	constexpr std::size_t DrawCategoryCount = std::to_underlying(DrawCategory::Overlay) + 1;

	template <class T>
	using DrawCategoryArray = std::array<T, DrawCategoryCount>;
}