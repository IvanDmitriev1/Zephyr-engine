export module Zephyr.Scene;

export import Zephyr.Scene.Systems.ISystem;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	class Scene final
	{
	public:
		Scene();
		~Scene();

	public:
		template<SystemType TSystem, typename... Args>
		TSystem& AddSystem(Args&&... args);

		template<SystemType TSystem>
		TSystem* GetSystem();

	public:
		void OnUpdate(float deltaTime);

		World& GetWorld() noexcept { return m_World; }
		const World& GetWorld() const noexcept { return m_World; }

	private:
		void DetachAll() noexcept;

	private:
		World m_World;
		std::vector<Scope<ISystem>> m_Systems;
	};

	
	template<SystemType TSystem, typename ...Args>
	TSystem& Scene::AddSystem(Args && ...args)
	{
		m_Systems.emplace_back(args...);
		m_Systems.back()->OnAttach(m_World);
	}

	template<SystemType TSystem>
	TSystem* Scene::GetSystem()
	{
		for (auto& sys : m_Systems)
		{
			if (auto* casted = static_cast<TSystem*>(sys.get()))
				return casted;
		}

		return nullptr;
	}

}