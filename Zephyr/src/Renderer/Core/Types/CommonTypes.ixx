export module Zephyr.Renderer.Types.CommonTypes;

import std.compat;
import Zephyr.Core.Assert;

export namespace Zephyr
{
	struct Extent2D
	{
		uint32_t Width{};
		uint32_t Height{};

		constexpr bool operator==(const Extent2D&) const noexcept = default;
	};

	struct Offset2D
	{
		int32_t X{};
		int32_t Y{};

		constexpr bool operator==(const Offset2D&) const noexcept = default;
	};

	struct Rect2D
	{
		Offset2D Offset{};
		Extent2D Extent{};

		constexpr bool operator==(const Rect2D&) const noexcept = default;
	};

	enum class ViewportRenderMode : uint8_t
	{
		Shaded,
		Wireframe,
		Unlit,
		Normals,
		UVs
	};

	namespace Utils
	{
		constexpr std::string_view ToString(ViewportRenderMode mode) noexcept
		{
			switch (mode)
			{
			case ViewportRenderMode::Shaded:           return "Shaded";
			case ViewportRenderMode::Wireframe:        return "Wireframe";
			case ViewportRenderMode::Unlit:            return "Unlit";
			case ViewportRenderMode::Normals:          return "Normals";
			case ViewportRenderMode::UVs:              return "UVs";
			default:  Unreachable();
			}
		}
	}
}