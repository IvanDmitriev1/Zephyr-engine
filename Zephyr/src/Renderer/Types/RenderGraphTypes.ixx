export module Zephyr.Renderer.Types.RenderGraphTypes;

export import Zephyr.Renderer.RHI.IBuffer;
export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Renderer.RenderQueue;
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
		Ref<RHI::IFrameBuffer> Target;
	};
}