export module ZephyrEditor.Ui.CreateProjectDialog;

export import ZephyrEditor.ProjectTypes;

import ZephyrEditor.ProjectTemplateLoader;
import ZephyrEditor.ProjectGenerator;

export namespace ZephyrEditor
{
	class CreateProjectDialog
	{
	public:
		using OnCreateCallback = std::function<void(const ProjectFile&)>;

		struct CreateInfo
		{
			std::filesystem::path EngineSdkRoot{};
			std::filesystem::path TemplatesRoot{};

			std::filesystem::path PremakeExe{};
			std::filesystem::path MsBuildExe{};
		};

		CreateProjectDialog(CreateInfo info, OnCreateCallback onCreate);
		~CreateProjectDialog() = default;

	public:
		void Open();
		void Draw();
		bool IsOpen() const noexcept { return m_IsOpen; }

	private:
		void RefreshTemplates();
		void DrawCard();

		bool ValidateInput();
		void CreateProject();

	private:
		static constexpr const char* kPopupName = "Create New Project";

		CreateInfo m_Info{};
		OnCreateCallback m_OnCreate;
		ProjectTemplateLoader m_TemplateLoader;
		ProjectGenerator m_ProjectGenerator;

		bool m_IsOpen = false;
		bool m_RequestOpenPopup = false;
		std::string m_LastError{};

		std::vector<std::string> m_TemplateNames;
		int m_SelectedTemplate = -1;

		std::array<char, 128> m_ProjectName{};
		std::array<char, 512> m_ProjectLocation{};
		std::filesystem::path m_ProjectPath{};
	};
}