module ZephyrEditor.Ui.CreateProjectDialog;

import <imgui.h>;

namespace ZephyrEditor
{
	CreateProjectDialog::CreateProjectDialog(CreateInfo info, OnCreateCallback onCreate)
		:m_Info(std::move(info)),
		m_ProjectGenerator({ m_Info.EngineSdkRoot }),
		m_TemplateLoader(m_Info.TemplatesRoot),
		m_OnCreate(std::move(onCreate))
	{
		
	}

	void CreateProjectDialog::Open()
	{
		m_IsOpen = true;
		m_RequestOpenPopup = true;
		m_LastError.clear();
		RefreshTemplates();
	}

	void CreateProjectDialog::Draw()
	{
		if (!m_IsOpen)
			return;

		if (m_RequestOpenPopup)
		{
			ImGui::OpenPopup(kPopupName);
			m_RequestOpenPopup = false;
		}


		const ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_AlwaysAutoResize;

		bool open = true;
		if (ImGui::BeginPopupModal(kPopupName, &open, flags))
		{
			DrawCard();
			ImGui::EndPopup();
		}

		if (!open)
		{
			m_IsOpen = false;
			ImGui::CloseCurrentPopup();
		}
	}

	void CreateProjectDialog::RefreshTemplates()
	{
		m_TemplateNames = m_TemplateLoader.ListTemplateNames();
		m_SelectedTemplate = -1;
	}


	void CreateProjectDialog::DrawCard()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18.0f, 16.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 10.0f));

		ImGui::TextUnformatted("Create a new game project");
		ImGui::Separator();

		ImGui::TextDisabled("Engine SDK: %s", m_Info.EngineSdkRoot.string().c_str());
		ImGui::TextDisabled("Templates:  %s", m_Info.TemplatesRoot.string().c_str());

		ImGui::Spacing();

		// Template selection
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted("Template");
		ImGui::SameLine();

		const char* preview = (m_SelectedTemplate >= 0 && m_SelectedTemplate < (int)m_TemplateNames.size())
			? m_TemplateNames[(size_t)m_SelectedTemplate].c_str()
			: "<none>";

		ImGui::SetNextItemWidth(-1.0f);
		if (ImGui::BeginCombo("##TemplateCombo", preview))
		{
			for (int i = 0; i < (int)m_TemplateNames.size(); ++i)
			{
				const bool selected = (i == m_SelectedTemplate);
				if (ImGui::Selectable(m_TemplateNames[(size_t)i].c_str(), selected))
					m_SelectedTemplate = i;
				if (selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		// Project name
		ImGui::TextUnformatted("Project Name");
		ImGui::SetNextItemWidth(-1.0f);
		ImGui::InputText("##ProjectName", m_ProjectName.data(), m_ProjectName.size(), ImGuiInputTextFlags_AutoSelectAll);

		// Project location
		ImGui::TextUnformatted("Project location");
		ImGui::SetNextItemWidth(-1.0f);
		ImGui::InputText("##ProjectRoot", m_ProjectLocation.data(), m_ProjectLocation.size(), ImGuiInputTextFlags_AutoSelectAll);


		//Project path
		if (!m_ProjectPath.empty())
		{
			ImGui::Spacing();
			ImGui::TextDisabled("Project will be created:  %s", m_ProjectPath.generic_string().c_str());
		}

		// Error
		if (!m_LastError.empty())
		{
			ImGui::Spacing();
			ImGui::TextColored(ImVec4(1, 0.25f, 0.25f, 1), "%s", m_LastError.c_str());
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		// Buttons row
		const float buttonW = 120.0f;

		// Left: refresh templates
		if (ImGui::Button("Refresh", ImVec2(buttonW, 0)))
		{
			RefreshTemplates();
		}

		ImGui::SameLine();
		ImGui::Dummy(ImVec2(0, 0));
		ImGui::SameLine(ImGui::GetContentRegionAvail().x - (buttonW * 2.0f + ImGui::GetStyle().ItemSpacing.x));

		// Right: cancel button
		if (ImGui::Button("Cancel", ImVec2(buttonW, 0)))
		{
			m_IsOpen = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		const bool canCreate = ValidateInput();
		if (!canCreate)
			ImGui::BeginDisabled();

		//Right: create button
		if (ImGui::Button("Create", ImVec2(buttonW, 0)))
		{
			CreateProject();
		}

		if (!canCreate)
			ImGui::EndDisabled();

		ImGui::PopStyleVar(2);
	}

	bool CreateProjectDialog::ValidateInput()
	{
		m_LastError.clear();

		const auto nameLen = std::strlen(m_ProjectName.data());
		const auto rootLen = std::strlen(m_ProjectLocation.data());

		if (m_SelectedTemplate < 0 || m_SelectedTemplate >= static_cast<int>(m_TemplateNames.size()))
		{
			m_LastError = "Select a template.";
			return false;
		}
		if (nameLen == 0)
		{
			m_LastError = "Project name is required.";
			return false;
		}
		if (rootLen == 0)
		{
			m_LastError = "Project location directory is required.";
			return false;
		}
		if (m_Info.EngineSdkRoot.empty())
		{
			m_LastError = "EngineSdkRoot is not set (dialog CreateInfo).";
			return false;
		}
		if (m_Info.TemplatesRoot.empty())
		{
			m_LastError = "TemplatesRoot is not set (dialog CreateInfo).";
			return false;
		}

		m_ProjectPath = std::filesystem::path(m_ProjectLocation.data()) / std::filesystem::path(m_ProjectName.data());
		if (std::filesystem::exists(m_ProjectPath))
		{
			m_LastError = "Directory already exists.";
			return false;
		}

		return true;
	}

	void CreateProjectDialog::CreateProject()
	{
		const std::string tplName = m_TemplateNames[(size_t)m_SelectedTemplate];
		auto tempLateOpt = m_TemplateLoader.LoadTemplate(tplName);
		if (!tempLateOpt.has_value())
		{
			m_LastError = std::format("Failed to load template: {}", tplName);
			return;
		}

		const std::string projectName = m_ProjectName.data();

		TemplateContext ctx;
		ctx.Set("PROJECT_NAME", m_ProjectName.data());
		ctx.Set("ENGINE_SDK_ROOT", m_Info.EngineSdkRoot.string());
		ctx.Set("ENGINE_INCLUDE", (m_Info.EngineSdkRoot / "include").string());
		ctx.Set("ENGINE_LINK", "Zephyr.Engine");

		ProjectGeneratorDesc desc
		{
			.ProjectRoot = std::move(m_ProjectPath),
			.ProjectName = std::move(projectName),
			.Template = std::move(*tempLateOpt),
			.Context = std::move(ctx)
		};

		auto projectFileResult = m_ProjectGenerator.Generate(desc);
	}

}