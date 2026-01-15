export module ZephyrEditor.MSBuildProjectBuilder;

export import ZephyrEditor.IProjectBuilder;

namespace fs = std::filesystem;

export namespace ZephyrEditor
{
	class MSBuildProjectBuilder final : public IProjectBuilder
	{
	public:
		MSBuildProjectBuilder();
		~MSBuildProjectBuilder() override = default;

		[[nodiscard]] std::expected<void, std::string>
			BuildProject(const ProjectRuntime& project) override;

		[[nodiscard]] std::expected<void, std::string>
			RebuildProject(const ProjectRuntime& project) override;

	private:
		static fs::path DiscoverDevenv();

	private:
		fs::path m_DevenvPath;
	};
}