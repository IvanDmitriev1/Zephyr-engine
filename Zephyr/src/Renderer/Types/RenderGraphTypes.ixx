export module Zephyr.Renderer.Types.RenderGraphTypes;

export import Zephyr.Renderer.RHI.IBuffer;
export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Renderer.RenderQueue;
export import Zephyr.Renderer.GBuffer;

export import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	struct RenderResources
	{
		Ref<RHI::IBuffer> CameraBuffer{};
		Ref<RHI::IBuffer> ObjectBuffer{};
	};

	struct PassExecutionContext
	{
		const RenderQueue& Queue;
		const RenderResources& Resources;
		GBuffer GBuffer{};

		Ref<RHI::IFrameBuffer> Target;
		ViewportRenderMode RenderMode = ViewportRenderMode::Shaded;
	};
}