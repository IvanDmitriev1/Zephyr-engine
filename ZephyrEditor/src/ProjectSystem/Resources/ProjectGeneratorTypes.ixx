export module ZephyrEditor.ProjectGeneratorTypes;

export import ZephyrEditor.ProjectTypes;
export import ZephyrEditor.TemplateTypes;


export namespace ZephyrEditor
{
	struct ProjectGeneratorCreateInfo
	{
		std::filesystem::path EngineRootPath{};
	};

	struct ProjectGeneratorDesc
	{
		std::filesystem::path ProjectRoot{};
		std::string ProjectName{};
		ProjectTemplate Template{};
		TemplateContext Context{};
	};
}