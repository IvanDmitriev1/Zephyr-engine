export module Zephyr.Renderer.Types.RenderGraphTypes;

export import Zephyr.Renderer.RHI.Interfaces.IBuffer;
export import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
export import Zephyr.Renderer.Frame.RenderQueue;
export import Zephyr.Renderer.Graph.GBuffer;

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