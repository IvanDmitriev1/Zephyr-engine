export module Zephyr.Renderer.Resources.RenderQueueTypes;

import std.compat;

export namespace Zephyr
{
	enum class RenderQueue : uint8_t
	{
		Background = 0,    // Skybox, background elements (rendered first)
		Geometry,      // Opaque geometry (front-to-back sorted)
		AlphaTest,     // Alpha cutout materials (rendered after opaque)
		Transparent,   // Transparent objects (back-to-front sorted)
		Overlay        // UI, debug lines, gizmos (no sorting, rendered last)
	};

	constexpr std::size_t RenderQueueCount = std::to_underlying(RenderQueue::Overlay) + 1;

	template <class T>
	using RenderQueueArray = std::array<T, RenderQueueCount>;
}