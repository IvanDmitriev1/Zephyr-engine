module Zephyr.Renderer.Renderer;

import Zephyr.Renderer.RenderQueue;
import Zephyr.Renderer.RenderGraph;
import Zephyr.Renderer.Core.Device;

import Zephyr.Renderer.Passes.GeometryPass;

namespace Zephyr::Renderer
{
	struct RendererData
	{
		RenderQueue Queue;
		RenderGraph Graph;
		RenderResources Resources;
	};

	static RendererData* s_Data = nullptr;

	void Init()
	{
		s_Data = new RendererData();

		RHI::BufferDesc cameraDesc
		{
			.SizeBytes = sizeof(CameraUniformData),
			.Usage = RHI::BufferUsage::Uniform,
			.Access = RHI::BufferAccess::Streaming,
			.DebugName = "Global_CameraUBO"
		};

		RHI::BufferDesc objectDesc
		{
			.SizeBytes = sizeof(ObjectUniformData),
			.Usage = RHI::BufferUsage::Uniform,
			.Access = RHI::BufferAccess::Streaming,
			.DebugName = "Global_ObjectUBO"
		};

		s_Data->Resources.CameraBuffer = RHI::Device::CreateBuffer(cameraDesc);
		s_Data->Resources.ObjectBuffer = RHI::Device::CreateBuffer(objectDesc);

		s_Data->Graph.AddPass(CreateScope<GeometryPass>());
	}

	void Shutdown()
	{
		if (s_Data)
		{
			delete s_Data;
		}
	}

	void BeginFrame()
	{
		s_Data->Queue.BeginFrame();
	}

	void Submit(const DrawItem& item)
	{
		s_Data->Queue.Submit(item);
	}

	void Submit(std::span<const DrawItem> items)
	{
		s_Data->Queue.Submit(items);
	}

	void RenderToTarget(Ref<RHI::IFrameBuffer> target, const CameraUniformData& cameraData)
	{
		s_Data->Queue.SortQueues();

		s_Data->Resources.CameraBuffer->SetData(
			std::as_bytes(std::span{ &cameraData, 1 })
		);

		PassExecutionContext context
		{
			.Queue = s_Data->Queue,
			.Resources = s_Data->Resources,
			.Target = std::move(target),
		};

		s_Data->Graph.Execute(context);
	}
}