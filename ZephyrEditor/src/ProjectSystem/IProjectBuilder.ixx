export module ZephyrEditor.IProjectBuilder;

export import ZephyrEditor.ProjectRuntime;

export namespace ZephyrEditor
{
	class IProjectBuilder
	{
	public:
		virtual ~IProjectBuilder() = default;

		// Builds the project DLL
		[[nodiscard]] virtual std::expected<void, std::string>
			BuildProject(const ProjectRuntime& project) = 0;

		// Rebuilds the project (clean + build)
		[[nodiscard]] virtual std::expected<void, std::string>
			RebuildProject(const ProjectRuntime& project) = 0;
	};
}