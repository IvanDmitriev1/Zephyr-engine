export module Zephyr.Renderer.Types.DrawItemRendererTypes;

export import Zephyr.Renderer.RHI.RenderPassTypes;
export import Zephyr.Renderer.Types.DrawCategory;

export namespace Zephyr
{
	enum class ViewportRenderMode : uint8_t
	{
		Shaded,
		Wireframe,
		Unlit,
		Normals,
		UVs
	};

	struct DrawItemExecutionConfig
	{
		RHI::DepthAttachment Depth{};
		DrawCategory Category = DrawCategory::Opaque;
		ViewportRenderMode RenderMode = ViewportRenderMode::Shaded;
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