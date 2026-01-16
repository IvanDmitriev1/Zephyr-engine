module Zephyr.Scene.Systems.CameraSystem;

import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Scene.Components.TransformComponent;

namespace Zephyr
{
	void CameraSystem::OnUpdate(World& world, float deltaTime)
	{
		auto cameras = world.GetEntitiesWith<CameraComponent, TransformComponent>();
		for (Entity entity : cameras)
		{
			UpdateCameraRuntime(world, entity);
		}
	}

	void CameraSystem::UpdateCameraRuntime(World& world, Entity entity)
	{
		auto& camera = world.GetComponent<CameraComponent>(entity);
		auto& transform = world.GetComponent<TransformComponent>(entity);

		if (!world.HasComponent<CameraRuntimeComponent>(entity))
			world.AddComponent(entity, CameraRuntimeComponent{});

		auto& runtime = world.GetComponent<CameraRuntimeComponent>(entity);

		runtime.Position = transform.Position;
		runtime.Forward = glm::normalize(transform.Rotation * glm::vec3(0, 0, -1));
		runtime.Up = glm::normalize(transform.Rotation * glm::vec3(0, 1, 0));
		runtime.Right = glm::cross(runtime.Forward, runtime.Up);
		runtime.Projection = glm::perspective(glm::radians(camera.Fov), camera.AspectRatio, camera.Near, camera.Far);

		runtime.View = glm::lookAt(
			runtime.Position,
			runtime.Position + runtime.Forward,
			runtime.Up
		);

		runtime.ViewProjection = runtime.Projection * runtime.View;
	}
}