module Zephyr.Scene.World;

namespace Zephyr
{
	Entity World::CreateEntity()
	{
		const EntityId id = m_NextEntityId++;

		EnsureAlive(id);
		m_AliveEntities[id] = true;
		return Entity{ id, const_cast<World*>(this) };
	}

	void World::DestroyEntity(Entity entity)
	{
		if (!Owns(entity))
			return;

		const EntityId id = entity.GetId();
		m_AliveEntities[id] = false;

		for (auto& [_, pool] : m_Pools)
		{
			pool->Remove(id);
		}
	}

	void World::EnsureAlive(EntityId id)
	{
		if (id >= m_AliveEntities.size())
			m_AliveEntities.resize(static_cast<size_t>(id) + 1, 0);
	}

	bool World::Owns(Entity e) const noexcept
	{
		return e.m_World == this && e.m_Id != NullEntity && IsAlive(e.m_Id);
	}
}