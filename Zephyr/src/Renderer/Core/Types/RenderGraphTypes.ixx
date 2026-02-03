export module Zephyr.Renderer.Types.RenderGraphTypes;

import Zephyr.Renderer.RHI.Interfaces.IBuffer;
import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
import Zephyr.Renderer.Frame.RenderQueue;
import Zephyr.Renderer.Graph.GBuffer;

import Zephyr.Core.CoreTypes;

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
