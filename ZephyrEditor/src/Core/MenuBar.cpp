module ZephyrEditor.MenuBar;

import Zephyr.Core.CoreTypes;
import <imgui.h>;

namespace ZephyrEditor
{
	void MenuBar::Render()
	{
		if (!ImGui::BeginMenuBar())
			return;

		for (auto& menu : m_Menus)
		{
			if (!ImGui::BeginMenu(menu.Label.c_str()))
				continue;

			for (auto& item : menu.Items)
			{
				if (item.IsSeparator)
				{
					ImGui::Separator();
				}
				else if (ImGui::MenuItem(
					item.Label.c_str(),
					item.Shortcut.empty() ? nullptr : item.Shortcut.c_str(),
					false,
					item.IsEnabled))
				{
					if (item.Callback)
						item.Callback();
				}
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	MenuBar& MenuBar::AddMenu(std::string label)
	{
		m_Menus.push_back({ std::move(label), {} });
		return *this;
	}

	MenuBar& MenuBar::AddItem(std::string label, MenuCallback callback, std::string shortcut)
	{
		Zephyr::Assert(!m_Menus.empty(), "MenuBar::AddItem trying to add an item in empty menu");

		m_Menus.back().Items.push_back({
			.Label = std::move(label),
			.Shortcut = std::move(shortcut),
			.Callback = std::move(callback)
									   });
		return *this;
	}

	MenuBar& MenuBar::AddSeparator()
	{
		Zephyr::Assert(!m_Menus.empty(), "MenuBar::AddSeparator trying to add an item in empty menu");

		m_Menus.back().Items.push_back({ .IsSeparator = true });
		return *this;
	}
}