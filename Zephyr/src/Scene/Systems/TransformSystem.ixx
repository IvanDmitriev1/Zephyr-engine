export module Zephyr.Scene.Systems.TransformSystem;

export import Zephyr.Scene.Systems.ISystem;

export namespace Zephyr
{
	class TransformSystem : public ISystem
	{
	public:
		void OnUpdate(World& world, float deltaTime) override;

	private:
		void UpdateTransform(World& world, Entity entity);
	};
}