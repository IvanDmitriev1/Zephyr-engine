module ZephyrEditor.ProjectTemplateLoader;

namespace fs = std::filesystem;

namespace ZephyrEditor
{
	ProjectTemplateLoader::ProjectTemplateLoader(fs::path templatesRoot)
		:m_TemplatesRoot(std::move(templatesRoot))

	{
		if (!fs::exists(m_TemplatesRoot))
		{
			throw std::runtime_error(std::format("Templates root path does not exist: {}", m_TemplatesRoot.string()));
		}
	}

	std::vector<std::string> ProjectTemplateLoader::ListTemplateNames() const
	{
		std::vector<std::string> out{};

		for (auto& entry : fs::directory_iterator(m_TemplatesRoot))
		{
			if (entry.is_directory())
			{
				out.push_back(entry.path().filename().string());
			}
		}

		return out;
	}

	std::expected<ProjectTemplate, std::string> ProjectTemplateLoader::LoadTemplate(std::string_view templateName) const
	{
		const fs::path templateDir = m_TemplatesRoot / templateName;
		if (!fs::exists(templateDir) || !fs::is_directory(templateDir))
			return std::unexpected("Failed to find template");

		std::vector<ProjectTemplateFile> files{};

		for (const auto& file : fs::recursive_directory_iterator(templateDir))
		{
			if (!file.is_regular_file())
				continue;

			const auto relativePath = fs::relative(file.path(), templateDir);
			files.push_back(ProjectTemplateFile{ .RelativeFilePath = std::move(relativePath) });
		}

		return ProjectTemplate{ .Name = std::string(templateName), .TemplateRoot = std::move(templateDir), .Files = std::move(files) };
	}

}