module ZephyrEditor.UiPanelHost;

namespace ZephyrEditor
{
	UiPanelHost::~UiPanelHost()
	{
		for (auto& panel : m_Panels)
		{
			panel->OnDetach();
		}
	}

	void UiPanelHost::OnUpdate(float deltaTime)
	{
		for (auto& panel : m_Panels)
		{
			panel->OnUpdate(deltaTime);
		}
	}

	void UiPanelHost::Render()
	{
		for (auto& panel : m_Panels)
		{
			panel->Render();
		}
	}

	UiPanel* UiPanelHost::Find(std::string_view id) noexcept
	{
		auto it = FindIt(id);
		return (it != m_Panels.end()) ? it->get() : nullptr;
	}

	bool UiPanelHost::Remove(std::string_view id)
	{
		auto it = FindIt(id);
		if (it == m_Panels.end())
			return false;

		(*it)->OnDetach();
		m_Panels.erase(it);
		return true;
	}

	void UiPanelHost::OnAdd(Scope<UiPanel> panel) noexcept
	{
		auto it = FindIt(panel->GetId());

		//Assert(it != m_Panels.end(), "UiPanelHost::OnAdd added panel with same name");

		panel->OnAttach();
		m_Panels.emplace_back(std::move(panel));
	}

	UiPanelHost::Iterator UiPanelHost::FindIt(std::string_view id) noexcept
	{
		return std::ranges::find_if(m_Panels, [&](const auto& p) { return p->GetId() == id; });
	}
}