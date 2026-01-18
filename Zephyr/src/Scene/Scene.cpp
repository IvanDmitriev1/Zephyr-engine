module Zephyr.Scene;

namespace Zephyr
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		DetachAll();
	}

	void Scene::OnUpdate(float deltaTime)
	{
		for (auto& sys : m_Systems)
		{
			sys->OnUpdate(m_World, deltaTime);
		}
	}

	void Scene::DetachAll() noexcept
	{
		for (auto& sys : m_Systems)
		{
			sys->OnDetach(m_World);
		}

		m_Systems.clear();
	}
}