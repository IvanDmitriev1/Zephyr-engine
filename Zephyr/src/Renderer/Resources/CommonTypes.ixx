export module Zephyr.Renderer.Resources.CommonTypes;

import std.compat;

export namespace Zephyr
{
	struct Extent2D
	{
		uint32_t Width{};
		uint32_t Height{};

		constexpr bool operator==(const Extent2D& other) const noexcept
		{
			return Width == other.Width && Height == other.Height;
		}

		constexpr bool operator!=(const Extent2D& other) const noexcept
		{
			return !(*this == other);
		}
	};

	struct Offset2D
	{
		int32_t X{};
		int32_t Y{};
	};

	struct Rect2D
	{
		Offset2D Offset{};
		Extent2D Extent{};
	};
}