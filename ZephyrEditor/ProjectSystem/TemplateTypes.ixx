export module ZephyrEditor.TemplateTypes;

import std;

export namespace ZephyrEditor
{
	struct ProjectTemplateFile
	{
		std::filesystem::path RelativePath{};
	};

	struct ProjectTemplate
	{
		std::string Name{};
		std::vector<ProjectTemplateFile> Files{};
	};
}