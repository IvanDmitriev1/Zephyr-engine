export module ZephyrEditor.ProjectTypes;

import std.compat;

export namespace ZephyrEditor
{
	struct ProjectFile
	{
		enum class BuildConfig { Debug, Release, Distribution };

		uint32_t Version = 1;
		std::string Name{};
		std::filesystem::path RootPath{};

		// Build
		std::filesystem::path SolutionPath{};
		BuildConfig ActiveBuildConfig = BuildConfig::Debug;

		// Artifact
		std::filesystem::path OutputDllPath{};
	};

	namespace Utils
	{
		inline constexpr std::string_view BuildConfigToString(ProjectFile::BuildConfig config) noexcept
		{
			switch (config)
			{
			case ProjectFile::BuildConfig::Debug:
				return "Debug";
			case ProjectFile::BuildConfig::Release:
				return "Release";
			case ProjectFile::BuildConfig::Distribution:
				return "Dist";
			default:
				return "Unknown";
			}
		}
	}
}