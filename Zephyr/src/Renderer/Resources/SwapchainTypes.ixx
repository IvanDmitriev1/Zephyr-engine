export module Zephyr.Renderer.Resources.SwapchainTypes;

export import Zephyr.Renderer.Resources.TextureTypes;

export namespace Zephyr::RHI
{
	struct SwapchainDesc
	{
		Extent2D Size{};
		TextureFormat ColorFormat = TextureFormat::RGBA8;
		TextureFormat DepthFormat = TextureFormat::DEPTH24STENCIL8;

		std::string_view DebugName{};
	};

}