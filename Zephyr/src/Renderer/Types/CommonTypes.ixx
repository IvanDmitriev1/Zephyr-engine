export module Zephyr.Renderer.Types.CommonTypes;

import std.compat;

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
}