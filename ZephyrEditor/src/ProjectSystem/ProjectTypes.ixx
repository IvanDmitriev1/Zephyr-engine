module;

#include <rfl.hpp>

export module ZephyrEditor.ProjectTypes;

export import std.compat;

export namespace ZephyrEditor
{
	struct ProjectFile
	{
		enum class BuildConfig { Debug, Release, Distribution };

		uint32_t Version = 1;
		std::string Name{};

		rfl::Skip<std::filesystem::path>RootPath{};
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
				return "Debug";
			}
		}
	}
}