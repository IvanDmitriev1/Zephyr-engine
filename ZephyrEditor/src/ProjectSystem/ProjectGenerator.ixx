export module ZephyrEditor.ProjectGenerator;

export import ZephyrEditor.ProjectGeneratorTypes;

export namespace ZephyrEditor
{
	class ProjectGenerator
	{
	public:
		explicit ProjectGenerator(ProjectGeneratorCreateInfo info);
		~ProjectGenerator() = default;

		std::expected<ProjectFile, std::string> Generate(ProjectGeneratorDesc& desc) const;

	private:
		ProjectFile CreateProjectFile(const ProjectGeneratorDesc& desc) const;

		std::filesystem::path SubstitutePathTokens(const std::filesystem::path& path,
												   const TemplateContext& ctx) const;
		void SubstitutePlaceholders(
			std::istream& in,
			std::ostream& out,
			const TemplateContext& context) const;

		void EnsureParentDirExists(const std::filesystem::path& filePath) const;

	private:
		const ProjectGeneratorCreateInfo m_createInfo{};
	};
}