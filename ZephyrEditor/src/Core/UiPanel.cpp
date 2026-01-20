module ZephyrEditor.UiPanel;

namespace ZephyrEditor
{
	void UiPanel::Render()
	{
		if (!m_IsOpen)
		{
			m_IsFocused = false;
			m_IsHovered = false;
			return;
		}

		std::string windowName;
		windowName.reserve(GetTitle().size() + 2 + GetId().size());
		windowName.append(GetTitle());
		windowName.append("##");
		windowName.append(GetId());

		bool open = m_IsOpen;
		const ImGuiWindowFlags flags = GetWindowFlags();

		const bool began = ImGui::Begin(windowName.c_str(), &open, flags);
		m_IsOpen = open;

		if (began)
		{
			m_IsFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
			m_IsHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);

			OnImGuiRender();
		}
		else
		{
			m_IsFocused = false;
			m_IsHovered = false;
		}

		ImGui::End();
	}
}