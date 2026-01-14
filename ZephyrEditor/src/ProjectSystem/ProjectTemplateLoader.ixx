export module ZephyrEditor.ProjectTemplateLoader;

export import ZephyrEditor.TemplateTypes;

export namespace ZephyrEditor
{
	class ProjectTemplateLoader
	{
	public:
		explicit ProjectTemplateLoader(std::filesystem::path templatesRoot);
		~ProjectTemplateLoader() = default;

		std::vector<std::string> ListTemplateNames() const;
		std::expected<ProjectTemplate, std::string> LoadTemplate(std::string_view templateName) const;

	private:
		std::filesystem::path m_TemplatesRoot;
	};
}