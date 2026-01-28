module Zephyr.Renderer.SceneRenderer;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.Passes.GeometryPass;
import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Scene.Components.TransformComponent;
import Zephyr.Scene.Components.MeshComponent;

namespace Zephyr
{
	SceneRenderer::SceneRenderer(World& world)
		:m_World(world)
	{
		RHI::BufferDesc cameraDesc{
			.SizeBytes = sizeof(CameraUniformData),
			.Usage = RHI::BufferUsage::Uniform,
			.Access = RHI::BufferAccess::Streaming,
			.DebugName = "SceneRenderer_CameraUBO"
		};

		RHI::BufferDesc objectDesc{
			.SizeBytes = sizeof(ObjectUniformData),
			.Usage = RHI::BufferUsage::Uniform,
			.Access = RHI::BufferAccess::Streaming,
			.DebugName = "SceneRenderer_ObjectUBO"
		};

		m_Resources.CameraBuffer = RHI::Device::CreateBuffer(cameraDesc);
		m_Resources.ObjectBuffer = RHI::Device::CreateBuffer(objectDesc);

		m_Graph.AddPass(CreateScope<GeometryPass>());
		m_Graph.Initialize();
	}

	void SceneRenderer::BeginFrame()
	{
		m_Queue.BeginFrame();
	}

	void SceneRenderer::Execute(Ref<RHI::IFrameBuffer> target)
	{
		m_Queue.SortQueues();

		PassExecutionContext context{
			.Queue = m_Queue,
			.Resources = m_Resources,
			.Target = std::move(target),
		};

		m_Graph.Execute(context);
	}

	void SceneRenderer::RenderWorld(Entity cameraEntity)
	{
		CameraUniformData cameraData = ExtractCameraData(cameraEntity);
		m_Resources.CameraBuffer->SetData(
			std::as_bytes(std::span{ &cameraData, 1 })
		);

		auto renderables = m_World.GetEntitiesWith<TransformComponent, MeshComponent>();

		for (Entity entity : renderables)
		{
			auto& transform = m_World.GetComponent<TransformRuntimeComponent>(entity);
			auto& mesh = m_World.GetComponent<MeshComponent>(entity);

			// TODO: Calculate distance from camera for sorting
			const glm::vec3 cameraPos = glm::vec3(cameraData.Position);
			const glm::vec3 objectPos = glm::vec3(transform.LocalToWorld[3]);
			const float distance = glm::length(objectPos - cameraPos);

			DrawItem item{
				.Mesh = mesh.MeshData,
				.Material = mesh.MaterialInstance,
				.Transform = transform.LocalToWorld,
				.Category = GetDefaultDrawCategory(mesh.MaterialInstance->GetType()),
				.DistanceFromCamera = distance
			};

			Submit(item);
		}
	}

	void SceneRenderer::Submit(const DrawItem & item)
	{
		m_Queue.Submit(item);
	}

	void SceneRenderer::Submit(std::span<const DrawItem> items)
	{
		m_Queue.Submit(items);
	}

	CameraUniformData SceneRenderer::ExtractCameraData(Entity cameraEntity)
	{
		Assert(cameraEntity.IsValid(), "SceneRenderer::ExtractCameraData failed to get camera entity");
		Assert(m_World.HasComponent<CameraRuntimeComponent>(cameraEntity), "SceneRenderer::ExtractCameraData camera entity doesent have ");

		auto& camera = m_World.GetComponent<CameraRuntimeComponent>(cameraEntity);
		return CameraUniformData{
			.ViewProjection = camera.ViewProjection,
			.Position = glm::vec4(camera.Position, 1.0f)
		};
	}
}