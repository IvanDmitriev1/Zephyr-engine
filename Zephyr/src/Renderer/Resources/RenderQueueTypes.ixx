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

	[[nodiscard]] constexpr std::string_view RenderQueueToString(RenderQueue queue) noexcept
	{
		switch (queue)
		{
		case RenderQueue::Background: return "Background";
		case RenderQueue::Geometry: return "Geometry";
		case RenderQueue::AlphaTest: return "AlphaTest";
		case RenderQueue::Transparent: return "Transparent";
		case RenderQueue::Overlay: return "Overlay";
		default: return "Unknown";
		}
	}
}