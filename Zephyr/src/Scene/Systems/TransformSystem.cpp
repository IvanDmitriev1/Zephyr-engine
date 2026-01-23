module Zephyr.Scene.Systems.TransformSystem;

import Zephyr.Scene.Components.TransformComponent;

namespace Zephyr
{
	void TransformSystem::OnUpdate(World& world, float deltaTime)
	{
		auto entities = world.GetEntitiesWith<TransformComponent>();
		for (Entity entity : entities)
		{
			UpdateTransform(world, entity);
		}
	}

	void TransformSystem::UpdateTransform(World& world, Entity entity)
	{
		auto& transform = world.GetComponent<TransformComponent>(entity);

		if (!transform.IsDirty)
			return;

		if (!world.HasComponent<TransformRuntimeComponent>(entity))
			world.AddComponent(entity, TransformRuntimeComponent{});

		auto& runtime = world.GetComponent<TransformRuntimeComponent>(entity);

		// Compute local-to-world matrix
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.Position);
		glm::mat4 rotation = glm::mat4_cast(glm::normalize(transform.Rotation));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);

		runtime.LocalToWorld = translation * rotation * scale;
		runtime.WorldToLocal = glm::inverse(runtime.LocalToWorld);
		runtime.WorldPosition = glm::vec3(runtime.LocalToWorld[3]);


		transform.IsDirty = false;
	}
}