export module Zephyr.Scene.Entity;

export import std.compat;

export namespace Zephyr
{
	class World;

	using EntityId = uint32_t;
	constexpr EntityId NullEntity = 0;

	class Entity
	{
		friend class World;

	public:
		inline Entity(EntityId id, const World* world) noexcept : m_Id(id), m_World(world) {}
		Entity() noexcept = default;
		~Entity() = default;

		EntityId GetId() const noexcept { return m_Id; }
		bool IsValid() const noexcept { return m_Id != NullEntity && m_World != nullptr; }

	private:
		EntityId m_Id = NullEntity;
		const World* m_World = nullptr;
	};
}