export module Zephyr.Scene.Systems.ISystem;

export import Zephyr.Scene.World;

export namespace Zephyr
{
	class ISystem
	{
	public:
		virtual ~ISystem() = default;

		inline virtual void OnAttach(World& world) {}
		inline virtual void OnDetach(World& world) noexcept {}

		virtual void OnUpdate(World& world, float deltaTime) = 0;
	};

	template<typename T>
	concept SystemType =
		std::derived_from<T, ISystem> &&
		(!std::is_abstract_v<T>);
}