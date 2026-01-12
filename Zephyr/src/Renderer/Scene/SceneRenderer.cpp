module Zephyr.Renderer.SceneRenderer;

import Zephyr.Renderer.Core.Device;
import Zephyr.Renderer.Resources.ShaderTypes;

namespace Zephyr
{
	using namespace Zephyr::RHI;

	SceneRenderer::SceneRenderer()
	{
		BufferDesc cameraBufferDesc
		{
			.SizeBytes = sizeof(CameraUniformData),
			.Usage = BufferUsage::Uniform,
			.Access = BufferAccess::Streaming,
			.DebugName = "CameraUniformBuffer"
		};
		m_CameraUniformBuffer = Device::CreateBuffer(cameraBufferDesc);

		BufferDesc objectBufferDesc
		{
			.SizeBytes = sizeof(CameraUniformData),
			.Usage = BufferUsage::Uniform,
			.Access = BufferAccess::Streaming,
			.DebugName = "CameraUniformBuffer"
		};
		m_ObjectUniformBuffer = Device::CreateBuffer(objectBufferDesc);
	}

	void SceneRenderer::Submit(const DrawItem& item)
	{
		m_Queues[static_cast<size_t>(item.Queue)].push_back(item);
	}

	void SceneRenderer::Submit(std::span<const DrawItem> items)
	{
		for (const auto& item : items)
		{
			m_Queues[static_cast<size_t>(item.Queue)].push_back(item);
		}
	}

	void SceneRenderer::BeginFrame(const CameraUniformData& cameraData)
	{
		for (auto& queue : m_Queues)
		{
			queue.clear();
		}

		m_CameraUniformBuffer->SetData(
			std::as_bytes(std::span{ &cameraData, 1 })
		);
	}


	void SceneRenderer::ExecutePass(const RHI::RenderPassDesc& passDesc)
	{
		SortQueues();

		auto cameraBinding = std::to_array<ResourceBinding>(
		{
			{ UniformBindings::Camera, m_CameraUniformBuffer },
		});

		auto encoder = Device::CreateRenderPassEncoder(passDesc);
		encoder->BindResources(cameraBinding);

		for (RenderQueue queue : passDesc.QueuesFilter)
		{
			ConfigureRenderQueue(encoder.get(), queue);
		}
	}

	void SceneRenderer::SortQueues()
	{
		// Geometry: front-to-back (early-Z optimization)
		auto& geometry = m_Queues[static_cast<size_t>(RenderQueue::Geometry)];
		std::ranges::sort(geometry, std::less<>{}, &DrawItem::DistanceFromCamera);

		// AlphaTest: also front-to-back
		auto& alphaTest = m_Queues[static_cast<size_t>(RenderQueue::AlphaTest)];
		std::ranges::sort(alphaTest, std::less<>{}, &DrawItem::DistanceFromCamera);

		// Transparent: back-to-front (correctness)
		auto& transparent = m_Queues[static_cast<size_t>(RenderQueue::Transparent)];
		std::ranges::sort(transparent, std::greater<>{}, &DrawItem::DistanceFromCamera);
	}

	void SceneRenderer::ConfigureRenderQueue(RHI::IRenderPassEncoder* encoder, RenderQueue queueType)
	{
		const auto& queue = m_Queues[static_cast<size_t>(queueType)];
		if (queue.empty())
			return;

		const Material* currentMaterial = nullptr;
		Ref<IPipeline> currentPipeline = nullptr;

		for (const auto& item : queue)
		{
			if (item.Material.get() != currentMaterial)
			{
				currentMaterial = item.Material.get();

				GraphicsPipelineDesc pipelineDesc{};
				pipelineDesc.Shader = currentMaterial->GetShader();
				ConfigurePipelineForQueue(pipelineDesc, queueType, currentMaterial->GetType());

				currentPipeline = Device::CreatePipeline(pipelineDesc);
				encoder->BindPipeline(currentPipeline);
				encoder->BindResources(currentMaterial->GetBindings());
			}

			ObjectUniformData objectData
			{
				.Model = item.Transform
			};
			m_ObjectUniformBuffer->SetData(std::as_bytes(std::span{ &objectData, 1 }));

			auto objectBindings = std::to_array<ResourceBinding>(
			{
				{ UniformBindings::PerObject, m_ObjectUniformBuffer },
			});

			encoder->BindResources(objectBindings);
			encoder->BindVertexArray(item.Mesh->GetVertexArray());

			if (item.Mesh->GetIndexCount() > 0)
				encoder->DrawIndexed(item.Mesh->GetIndexCount());
			else
				encoder->Draw(item.Mesh->GetVertexCount());
		}

	}

	void SceneRenderer::ConfigurePipelineForQueue(RHI::GraphicsPipelineDesc& desc, RenderQueue queue, AlphaMode alphaMode)
	{
		// Defaults for opaque geometry
		desc.Depth.DepthTestEnable = true;
		desc.Depth.DepthWriteEnable = true;
		desc.Blend.Enable = false;

		switch (queue)
		{
		case RenderQueue::Transparent:
			desc.Blend.Enable = true;
			desc.Depth.DepthWriteEnable = false; // Don't write depth for transparents
			break;

		case RenderQueue::Overlay:
			desc.Depth.DepthTestEnable = false; // Always on top
			desc.Depth.DepthWriteEnable = false;
			break;

		default:
			break;
		}
	}

}