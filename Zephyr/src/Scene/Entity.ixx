export module Zephyr.Scene.Entity;

export import std.compat;

export namespace Zephyr
{
	using EntityId = uint32_t;
	constexpr EntityId NullEntity = 0;

	class Entity
	{
		friend class World;

	public:
		EntityId GetId() const noexcept { return m_Id; }
		bool IsValid() const noexcept { return m_Id != NullEntity && m_World != nullptr; }

		template<typename T>
		T& GetComponent();

		template<typename T>
		bool HasComponent() const;

	private:
		Entity(EntityId id, World* world) : m_Id(id), m_World(world) {}

	private:
		EntityId m_Id = NullEntity;
		World* m_World = nullptr;
	};

	template<typename T>
	T& Entity::GetComponent()
	{

	}


	template<typename T>
	bool Entity::HasComponent() const
	{

	}


}