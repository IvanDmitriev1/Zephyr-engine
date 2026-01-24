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
		inline decltype(auto) GetWorld(this auto& self) noexcept { return (self.m_World); }

	public:
		template<SystemType TSystem, typename... Args>
		TSystem& AddSystem(Args&&... args);

		template<SystemType TSystem>
		void RemoveSystem();

		template<SystemType TSystem>
		auto* TryGetSystem(this auto& self) noexcept;

		template<SystemType TSystem>
		decltype(auto) GetSystem(this auto& self);

	public:
		void OnUpdate(float deltaTime);

	private:
		void DetachAll() noexcept;

	private:
		World m_World;
		std::vector<Scope<ISystem>> m_Systems;
	};

	
	template<SystemType TSystem, typename ...Args>
	TSystem& Scene::AddSystem(Args && ...args)
	{
		auto sys = CreateScope<TSystem>(std::forward<Args>(args)...);
		TSystem& ref = *sys;

		m_Systems.emplace_back(std::move(sys));
		ref.OnAttach(m_World);

		return ref;
	}

	template<SystemType TSystem>
	void Scene::RemoveSystem()
	{
		for (auto it = m_Systems.begin(); it != m_Systems.end(); ++it)
		{
			if (*it && typeid(*(*it)) == typeid(TSystem))
			{
				m_Systems.erase(it);
				return;
			}
		}
	}

	template<SystemType TSystem>
	auto* Scene::TryGetSystem(this auto& self) noexcept
	{
		using Self = std::remove_reference_t<decltype(self)>;
		using Ret = std::conditional_t<std::is_const_v<Self>, const TSystem, TSystem>;

		for (auto& sys : self.m_Systems)
		{
			if (!sys)
				continue;

			if (typeid(*sys) == typeid(TSystem))
				return static_cast<Ret*>(sys.get());
		}

		return static_cast<Ret*>(nullptr);
	}

	template<SystemType TSystem>
	decltype(auto) Scene::GetSystem(this auto& self)
	{
		auto* p = self.TryGetSystem<TSystem>();
		Assert(p != nullptr, "GetSystem: requested system not present");
		return *p;
	}

}