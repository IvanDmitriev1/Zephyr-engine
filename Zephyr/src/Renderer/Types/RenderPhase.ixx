export module Zephyr.Renderer.Types.RenderPhase;

import std.compat;

export namespace Zephyr
{
	enum class RenderPhase : uint8_t
	{
		Background = 0,    // Skybox, background elements (rendered first)
		Geometry,      // Opaque geometry (front-to-back sorted)
		AlphaTest,     // Alpha cutout materials (rendered after opaque)
		Transparent,   // Transparent objects (back-to-front sorted)
		Overlay        // UI, debug lines, gizmos (no sorting, rendered last)
	};

	constexpr std::size_t RenderPhaseCount = std::to_underlying(RenderPhase::Overlay) + 1;

	template <class T>
	using RenderPhaseArray = std::array<T, RenderPhaseCount>;
}