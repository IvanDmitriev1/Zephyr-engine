module;

#include <imgui_internal.h>

module ZephyrEditor.UiPanelHost;

namespace ZephyrEditor
{
	UiPanelHost::~UiPanelHost()
	{
		for (auto it = m_Panels.rbegin(); it != m_Panels.rend(); ++it)
		{
			(*it)->OnDetach();
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
		RenderDockspaceRoot();

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

	UiPanel& UiPanelHost::Get(std::string_view id)
	{
		if (auto* p = Find(id))
			return *p;

		throw std::out_of_range(std::format("Panel not found: {}", id));
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
		auto it = FindIt(panel->GetTitle());

		//Assert(it != m_Panels.end(), "UiPanelHost::OnAdd added panel with same name");

		panel->OnAttach();
		m_Panels.emplace_back(std::move(panel));
	}

	UiPanelHost::Iterator UiPanelHost::FindIt(std::string_view id) noexcept
	{
		return std::ranges::find_if(m_Panels, [&](const auto& p) { return p->GetTitle() == id; });
	}

	void UiPanelHost::RenderDockspaceRoot()
	{
		static bool dockspaceOpen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags =
			ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);


		ImGui::Begin("Zephyr editor", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		ImGuiID dockspace_id = ImGui::GetID("Editor dockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		static bool first_time = true;
		if (first_time)
		{
			first_time = false;
			BuildDefaultDockLayout(dockspace_id);
		}

		m_MenuBar.Render();

		ImGui::End(); //Zephyr editor
	}

	void UiPanelHost::BuildDefaultDockLayout(ImGuiID dock_main_id)
	{
		// Clear out existing layout
		ImGui::DockBuilderRemoveNode(dock_main_id);
		ImGui::DockBuilderAddNode(dock_main_id, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dock_main_id, ImGui::GetMainViewport()->Size);

		ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
		ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.3f, nullptr, &dock_main_id);

		ImGui::DockBuilderDockWindow("Scene Hierarchy", dock_id_left);
		ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
		ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
		ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Debug log", dock_id_bottom);

		ImGui::DockBuilderFinish(dock_main_id);
	}
}