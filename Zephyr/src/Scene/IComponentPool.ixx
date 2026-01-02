export module Zephyr.Scene.IComponentPool;

export import Zephyr.Scene.Entity;

export namespace Zephyr
{
	class IComponentPool
	{
	public:
		virtual ~IComponentPool() = default;
		virtual void Remove(EntityId id) = 0;
		virtual bool Contains(EntityId id) const = 0;
	};
}