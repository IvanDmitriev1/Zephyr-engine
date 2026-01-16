module;

#include <rfl/toml.hpp>

module ZephyrEditor.ProjectManager;

#ifdef ZEPHYR_PLATFORM_WINDOWS
import ZephyrEditor.MSBuildProjectBuilder;
#endif // ZEPHYR_PLATFORM_WINDOWS

import ZephyrEditor.ProjectTypes;

namespace fs = std::filesystem;

namespace ZephyrEditor
{
	ProjectManager::ProjectManager()
	{
#ifdef ZEPHYR_PLATFORM_WINDOWS
		m_ProjectBuilder = CreateScope<MSBuildProjectBuilder>();
#endif // ZEPHYR_PLATFORM_WINDOWS
	}

	const ProjectRuntime& ProjectManager::GetProject() const
	{
		Assert(HasProject(), "Cannot get project if its not loaded");
		return *m_Project;
	}

	std::expected<void, std::string> ProjectManager::OpenProject(const std::filesystem::path& zprojPath)
	{
		if (!fs::exists(zprojPath))
			return std::unexpected("Project file not found: " + zprojPath.string());

		std::ifstream inFile{ zprojPath, std::ios::binary };
		if (!inFile)
			return std::unexpected("Failed to open project file: " + zprojPath.string());

		auto result = rfl::toml::read<ProjectFile>(inFile);
		if (!result)
			return std::unexpected("Failed to parse project file: " + zprojPath.string() + "\nError: " + result.error().what());

		CloseProject();
		ProjectFile projectFile = std::move(*result);
		ProjectRuntime projectRuntime
		{
			.Name = projectFile.Name,
			.RootPath = zprojPath.parent_path(),
			.ZprojPath = zprojPath,
			.VsProjPath = zprojPath.parent_path() / (projectFile.Name + ".vcxproj"),
			.DllPath = zprojPath.parent_path() / projectFile.BinDirectory / (projectFile.Name + ".dll"),
		};

		m_Project = std::move(projectRuntime);
		return {};
	}

	std::expected<void, std::string> ProjectManager::GenerateProjectFiles()
	{
		return {};
	}

	std::expected<void, std::string> ProjectManager::Build()
	{
		if (!m_Project)
			return std::unexpected("No project open.");

		auto built = m_ProjectBuilder->BuildProject(*m_Project);
		if (!built)
			return std::unexpected(built.error());

		m_Project->LastDllWrite = fs::last_write_time(m_Project->DllPath);
		return {};
	}

	std::expected<void, std::string> ProjectManager::Rebuild()
	{
		return std::expected<void, std::string>();
	}

	void ProjectManager::CloseProject()
	{
		m_Project.reset();
	}
}