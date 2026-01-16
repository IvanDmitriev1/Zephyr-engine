export module Zephyr.Scene.Systems.CameraSystem;

export import Zephyr.Scene.Systems.ISystem;

export namespace Zephyr
{
	class CameraSystem final : public ISystem
	{
	public:
		CameraSystem() = default;
		~CameraSystem() override = default;

		void OnUpdate(World& world, float deltaTime) override;

	private:
		void UpdateCameraRuntime(World& world, Entity entity);
	};
}