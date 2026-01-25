module Zephyr.Scene.Systems.RenderingSystem;

import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Scene.Components.TransformComponent;
import Zephyr.Scene.Components.MeshComponent;
import Zephyr.Renderer.Renderer;

namespace Zephyr
{
	void RenderingSystem::OnUpdate(World& world, float deltaTime)
	{
		auto renderables = world.GetEntitiesWith<TransformComponent, MeshComponent, MeshComponent>();
		for (Entity entity : renderables)
		{
			SubmitEntity(world, entity, {});
		}
	}

	void RenderingSystem::SubmitEntity(World& world, Entity entity, const glm::vec3& cameraPos)
	{
		auto& transform = world.GetComponent<TransformRuntimeComponent>(entity);
		auto& mesh = world.GetComponent<MeshComponent>(entity);

		auto distanceFromCamera = glm::distance(cameraPos, transform.WorldPosition);
		bool isVisible = true; //TODO

		if (!isVisible)
			return;

		DrawItem item
		{
			.Mesh = mesh.MeshData,
			.Material = mesh.MaterialInstance,
			.Transform = transform.LocalToWorld,
			.Phase = GetDefaultPhase(mesh.MaterialInstance->GetType()),
			.DistanceFromCamera = distanceFromCamera,
		};

		Renderer::Submit(item);
	}
}