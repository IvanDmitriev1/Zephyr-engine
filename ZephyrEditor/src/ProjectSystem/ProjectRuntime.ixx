export module ZephyrEditor.ProjectRuntime;

export import std;

export namespace ZephyrEditor
{
	struct ProjectRuntime
	{
		enum class BuildConfig { Debug, Release, Distribution };

		std::string Name{};
		std::filesystem::path RootPath{};
		std::filesystem::path ZprojPath{};
		std::filesystem::path VsProjPath{};
		std::filesystem::path DllPath{};
		BuildConfig ActiveConfig = BuildConfig::Debug;

		std::optional< std::filesystem::path> LoadedRuntimeDllPath{};
		std::optional<std::filesystem::file_time_type> LastDllWrite{};
	};

	namespace Utils
	{
		inline constexpr std::wstring_view BuildConfigToString(ProjectRuntime::BuildConfig config) noexcept
		{
			switch (config)
			{
			case ProjectRuntime::BuildConfig::Debug:
				return L"Debug";
			case ProjectRuntime::BuildConfig::Release:
				return L"Release";
			case ProjectRuntime::BuildConfig::Distribution:
				return L"Dist";
			default:
				return L"Debug";
			}
		}
	}
}