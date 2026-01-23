export module ZephyrEditor.DemoSystem;

import Zephyr.Scene.Systems.ISystem;
import Zephyr.Scene.Components.TransformComponent;

using namespace Zephyr;

export namespace ZephyrEditor
{
	struct DemoComponent
	{

	};

	class DemoSystem : public ISystem
	{

	public:
		void OnUpdate(World& world, float deltaTime) override
		{
			constexpr float kDegreesPerSecond = 90.0f;

			const float deltaDegrees = kDegreesPerSecond * deltaTime;
			const float radians = glm::radians(deltaDegrees);

			const glm::quat delta = glm::angleAxis(radians, glm::vec3{ 0.0f, 1.0f, 0.0f });

			auto entities = world.GetEntitiesWith<DemoComponent, TransformComponent>();
			for (Entity entity : entities)
			{
				auto& tc = world.GetComponent<TransformComponent>(entity);
				tc.Rotation = glm::normalize(tc.Rotation * delta);
				tc.IsDirty = true;
			}
		}

	private:
		float m_Degrees = 0.0f;
	};
}