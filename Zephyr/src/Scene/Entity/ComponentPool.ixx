export module Zephyr.Scene.ComponentPool;

export import Zephyr.Core.CoreTypes;
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

	template<typename T>
	class ComponentPool final : public IComponentPool
	{
		static constexpr uint32_t InvalidData = std::numeric_limits<uint32_t>::max();

	public:
		bool Contains(EntityId id) const override
		{
			return id < m_Sparse.size() && m_Sparse[id] != InvalidData;
		}

		void Remove(EntityId e) override;

		template<typename... Args>
		T& Emplace(EntityId e, Args&&... args);

		T& Get(EntityId id);
		const T& Get(EntityId id) const;

		std::span<const EntityId> Entities() const { return { m_Entities.data(), m_Entities.size() }; }

	private:
		void EnsureSparse(EntityId id)
		{
			if (id >= m_Sparse.size())
				m_Sparse.resize(static_cast<size_t>(id) + 1, InvalidData);
		}

	private:
		std::vector<EntityId>  m_Entities;
		std::vector<T> m_Data;
		std::vector<uint32_t> m_Sparse;
	};

	template<typename T>
	template<typename ...Args>
	T& ComponentPool<T>::Emplace(EntityId e, Args && ...args)
	{
		EnsureSparse(e);

		if (Contains(e))
		{
			return m_Data[m_Sparse[e]];
		}

		const uint32_t dataIndex = static_cast<uint32_t>(m_Data.size());
		m_Data.emplace_back(std::forward<Args>(args)...);
		m_Entities.emplace_back(e);
		m_Sparse[e] = dataIndex;
		return m_Data.back();
	}

	template<typename T>
	void ComponentPool<T>::Remove(EntityId e)
	{
		if (!Contains(e))
			return;

		const uint32_t dataIndex = m_Sparse[e];
		const uint32_t lastIndex = static_cast<uint32_t>(m_Data.size() - 1);
		const EntityId lastEntity = m_Entities[lastIndex];

		m_Data[dataIndex] = std::move(m_Data[lastIndex]);
		m_Entities[dataIndex] = lastEntity;
		m_Sparse[lastEntity] = dataIndex;

		m_Data.pop_back();
		m_Entities.pop_back();
		m_Sparse[e] = InvalidData;
	}

	template<typename T>
	T& ComponentPool<T>::Get(EntityId id)
	{
		Assert(Contains(id), "ComponentPool::Get: entity does not have component");
		return m_Data[m_Sparse[id]];
	}

	template<typename T>
	const T& ComponentPool<T>::Get(EntityId id) const
	{
		Assert(Contains(id), "ComponentPool::Get: entity does not have component");
		return m_Data[m_Sparse[id]];
	}
}