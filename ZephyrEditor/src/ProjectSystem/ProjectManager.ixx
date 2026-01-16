export module ZephyrEditor.ProjectManager;

export import ZephyrEditor.ProjectTypes;

import Zephyr.Core.CoreTypes;
import ZephyrEditor.IProjectBuilder;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager() = default;

	public:
		[[nodiscard]] bool HasProject() const noexcept { return m_Project.has_value(); }
		[[nodiscard]] const ProjectRuntime& GetProject() const;

		[[nodiscard]] std::expected<void, std::string> OpenProject(const std::filesystem::path& zprojPath);

		// Build steps
		[[nodiscard]] std::expected<void, std::string> GenerateProjectFiles();
		[[nodiscard]] std::expected<void, std::string> Build();
		[[nodiscard]] std::expected<void, std::string> Rebuild();

	private:
		void CloseProject();

	private:
		Scope<IProjectBuilder> m_ProjectBuilder;

		std::optional<ProjectRuntime> m_Project;
	};
}