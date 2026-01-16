export module Zephyr.Scene.Systems.RenderingSystem;

export import Zephyr.Scene.Systems.ISystem;

export namespace Zephyr
{
	class RenderingSystem final : public ISystem
	{
	public:
		RenderingSystem() = default;
		~RenderingSystem() override = default;

		void OnUpdate(World& world, float deltaTime) override;

	private:
		void SubmitEntity(World& world, Entity entity, const glm::vec3& cameraPos);
	};
}