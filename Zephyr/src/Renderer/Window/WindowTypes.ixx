export module Zephyr.Renderer.WindowTypes;

import std.compat;

export namespace Zephyr
{
	struct WindowSpecification
	{
		std::string_view Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizeable = true;
		bool VSync = true;
	};
}