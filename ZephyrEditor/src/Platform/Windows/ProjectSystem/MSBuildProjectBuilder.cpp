module ZephyrEditor.MSBuildProjectBuilder;

import ZephyrEditor.Process;

namespace fs = std::filesystem;

namespace ZephyrEditor
{
	MSBuildProjectBuilder::MSBuildProjectBuilder()
		:m_DevenvPath(DiscoverDevenv())
	{

	}

	std::expected<void, std::string> MSBuildProjectBuilder::BuildProject(const ProjectRuntime& project)
	{
		auto args = std::to_array<std::wstring>(
		{
			project.VsProjPath.generic_wstring(),
			L"/Build \"Debug|Opengl\"",
		});

		Process::ProcessDesc desc
		{
			.Executable = m_DevenvPath,
			.Args = args,
			.WorkingDir = fs::current_path(),
		};

		auto commandResult = Process::RunProcess(desc);
		if (!commandResult)
			return std::unexpected(commandResult.error());

		return {};
	}

	std::expected<void, std::string> MSBuildProjectBuilder::RebuildProject(const ProjectRuntime& project)
	{
		auto args = std::to_array<std::wstring>(
			{
				project.VsProjPath.generic_wstring(),
				L"/ReBuild \"Debug|Opengl\"",
			});

		Process::ProcessDesc desc
		{
			.Executable = m_DevenvPath,
			.Args = args,
			.WorkingDir = fs::current_path(),
		};

		auto commandResult = Process::RunProcess(desc);
		if (!commandResult)
			return std::unexpected(commandResult.error());

		return {};
	}

	fs::path MSBuildProjectBuilder::DiscoverDevenv()
	{
		const fs::path vsWhere = L"C:/Program Files (x86)/Microsoft Visual Studio/Installer/vswhere.exe";
		if (!fs::exists(vsWhere))
			throw std::runtime_error("vswhere.exe not found at expected location.");

		static auto args = std::to_array<std::wstring>(
		{
			L"-latest",
			L"-prerelease",
			L"-products", L"*",
			L"-requires", L"Microsoft.VisualStudio.Component.CoreEditor",
			L"-find", L"Common7\\IDE\\devenv.com",
		});

		Process::ProcessDesc desc
		{
			.Executable = std::move(vsWhere),
			.Args = args,
			.WorkingDir = fs::current_path(),
		};

		auto commandResult = Process::RunProcess(desc);
		if (!commandResult.has_value())
		{
			throw std::runtime_error("Failed to execute vswhere.exe: " + commandResult.error());
		}

		return fs::path(commandResult.value());
	}

}