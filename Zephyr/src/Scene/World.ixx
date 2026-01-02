export module Zephyr.Scene.World;

export import Zephyr.Scene.Entity;
export import Zephyr.Scene.Components;
export import Zephyr.Scene.ComponentPool;

export namespace Zephyr
{
	class World
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template<typename T>
		void AddComponent(Entity entity, T&& component);

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename... Components>
		std::vector<Entity> GetEntitiesWith();

		bool IsAlive(EntityId id) const noexcept { return id < m_AliveEntities.size() && m_AliveEntities[id] != 0; }


	private:
		void EnsureAlive(EntityId id)
		{
			if (id >= m_AliveEntities.size())
				m_AliveEntities.resize(static_cast<size_t>(id) + 1, 0);
		}

		bool Owns(Entity e) const noexcept
		{
			return e.m_World == this && e.m_Id != NullEntity && IsAlive(e.m_Id);
		}

		template<typename T>
		ComponentPool<T>& GetOrCreatePool();

		template<typename T>
		ComponentPool<T>* FindPool();

		template<typename T>
		const ComponentPool<T>* FindPool() const;

	private:
		EntityId m_NextEntityId = 1;

		std::vector<bool> m_AliveEntities;
		std::unordered_map<std::type_index, Scope<IComponentPool>> m_Pools;
	};

	Entity World::CreateEntity()
	{
		const EntityId id = m_NextEntityId++;

		EnsureAlive(id);
		m_AliveEntities[id] = true;
		return Entity{ id, this };
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

	template<typename T>
	void World::AddComponent(Entity entity, T&& component)
	{
		using U = std::remove_cvref_t<T>;
		Assert(Owns(entity), "AddComponent: invalid entity or wrong world");

		GetOrCreatePool<U>().Emplace(entity.GetId(), std::forward<T>(component));
	}

	template<typename T>
	bool World::HasComponent(Entity entity) const
	{
		if (auto* pool = FindPool<T>())
		{
			return pool->Contains(entity.GetId());
		}

		return false;
	}

	template<typename T>
	T& World::GetComponent(Entity entity)
	{
		Assert(Owns(entity), "GetComponent: invalid entity or wrong world");

		auto* pool = FindPool<T>();
		Assert(pool != nullptr && pool->Contains(entity.GetId()), "GetComponent: component missing");

		return pool->Get(entity.GetId());
	}

	template<typename ...Components>
	std::vector<Entity> World::GetEntitiesWith()
	{
		using First = std::tuple_element_t<0, std::tuple<Components...>>;

		auto* basePool = FindPool<First>();
		if (!basePool)
			return {};

		const auto ids = basePool->Entities();
		std::vector<Entity> out;
		out.reserve(ids.size());

		for (EntityId id : basePool->Entities())
		{
			if (!IsAlive(id))
				continue;

			if ((HasComponent<Components>(Entity{ id, this }) && ...))
				out.emplace_back(id, this);
		}

		return out;
	}

	template<typename T>
	ComponentPool<T>& World::GetOrCreatePool()
	{
		const std::type_index key{ typeid(T) };
		auto [it, inserted] = m_Pools.try_emplace(key, nullptr);

		if (inserted)
			it->second = CreateScope<ComponentPool<T>>();

		return *static_cast<ComponentPool<T>*>(it->second.get());
	}
	template<typename T>
	ComponentPool<T>* World::FindPool()
	{
		const std::type_index key{ typeid(T) };
		auto it = m_Pools.find(key);
		if (it == m_Pools.end())
			return nullptr;

		return static_cast<ComponentPool<T>*>(it->second.get());
	}

	template<typename T>
	const ComponentPool<T>* World::FindPool() const
	{
		const std::type_index key{ typeid(T) };
		auto it = m_Pools.find(key);
		if (it == m_Pools.end())
			return nullptr;

		return static_cast<const ComponentPool<T>*>(it->second.get());
	}
}