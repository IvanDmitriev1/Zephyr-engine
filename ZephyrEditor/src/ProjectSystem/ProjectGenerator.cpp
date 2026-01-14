module;

#include <rfl/toml.hpp>

module ZephyrEditor.ProjectGenerator;

namespace fs = std::filesystem;

namespace ZephyrEditor
{
	ProjectGenerator::ProjectGenerator(ProjectGeneratorCreateInfo info)
		:m_createInfo(std::move(info))
	{

	}

	std::expected<ZephyrEditor::ProjectFile, std::string> ProjectGenerator::Generate(ProjectGeneratorDesc& desc) const
	{
		desc.Context.Set("ENGINE_ROOT", m_createInfo.EngineRootPath.generic_string());

		try
		{
			fs::create_directories(desc.ProjectRoot);

			ProjectFile pf = CreateProjectFile(desc);

			for (const auto& entry : desc.Template.Files)
			{
				fs::path outputExtensionless = entry.RelativeFilePath;
				outputExtensionless =outputExtensionless.replace_extension();

				std::ifstream inFile{ desc.Template.TemplateRoot / entry.RelativeFilePath, std::ios::binary };
				if (!inFile)
				{
					return std::unexpected(std::format("Failed to open template file: {}", entry.RelativeFilePath.string()));
				}

				const fs::path outputPath = SubstitutePathTokens(desc.ProjectRoot / outputExtensionless, desc.Context);
				EnsureParentDirExists(outputPath);
				std::ofstream outFile{ outputPath, std::ios::binary };
				if (!outFile)
				{
					return std::unexpected(std::format("Failed to create output file: {}", outputPath.string()));
				}

				SubstitutePlaceholders(inFile, outFile, desc.Context);
			}

			return pf;
		}
		catch (const std::runtime_error& error)
		{
			return std::unexpected(std::format("Runtime error: {}", error.what()));
		}
	}

	ProjectFile ProjectGenerator::CreateProjectFile(const ProjectGeneratorDesc& desc) const
	{
		auto projectFilePath = desc.ProjectRoot / ".zproj";

		ProjectFile pf
		{
			.Name = desc.ProjectName,
			.RootPath = desc.ProjectRoot,
		};

		std::ofstream outFile{ projectFilePath, std::ios::binary };
		if (!outFile)
		{
			throw std::runtime_error(std::format("Failed to create project file: {}", projectFilePath.string()));
		}

		rfl::toml::write(pf, outFile);
		return pf;
	}

	void ProjectGenerator::EnsureParentDirExists(const std::filesystem::path& filePath) const
	{
		const fs::path parentDir = filePath.parent_path();
		if (!parentDir.empty() && !fs::exists(parentDir))
		{
			fs::create_directories(parentDir);
		}
	}

	std::filesystem::path ProjectGenerator::SubstitutePathTokens(const std::filesystem::path& path, const TemplateContext& ctx) const
	{
		std::string input = path.generic_string();
		std::string_view pathStr{ input };

		const size_t openPos = pathStr.find('{') + 1;
		const std::size_t closePos = pathStr.find('}', openPos);

		if (openPos == 1 || closePos == std::string::npos)
			return path;

		const std::string_view key = pathStr.substr(openPos, closePos - (openPos));
		const std::string_view value = ctx.Get(key);

		std::string out;
		out.reserve(pathStr.size() - (closePos - openPos) + value.size());
		out.append(pathStr.substr(0, openPos - 1));
		out.append(value);
		out.append(pathStr.substr(closePos + 1));

		return fs::path{ out };
	}

	void ProjectGenerator::SubstitutePlaceholders(std::istream& in, std::ostream& out, const TemplateContext& context) const
	{
		static constexpr size_t kChunkSize = 8 * 1024;
		static constexpr size_t kMaxTokenLen = 1024;

		enum class State : uint8_t
		{
			Normal,
			SawOpenBrace,  // saw '{' in Normal
			InToken,       // after "{{"
			SawCloseBrace  // saw '}' inside token (maybe "}}")
		};

		std::array<char, kChunkSize> buffer{};
		std::array<char, kMaxTokenLen> tokenBuffer{};
		size_t tokenLen = 0;
		State state = State::Normal;

		auto writeLiteral = [&](std::string_view literal)
		{
			out.write(literal.data(), static_cast<std::streamsize>(literal.size()));
		};

		auto pushTokenChar = [&](char c)
		{
			if (tokenLen >= kMaxTokenLen)
				throw std::runtime_error("Template token too long.");

			tokenBuffer[tokenLen++] = c;
		};

		auto emitToken = [&]()
		{
			const std::string_view key{ tokenBuffer.data(), tokenLen };
			std::string_view value = context.Get(key);

			writeLiteral(value);
			tokenLen = 0;
		};

		while (in)
		{
			in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
			const std::streamsize readChars = in.gcount();
			if (readChars <= 0)
				break;

			for (std::streamsize i = 0; i < readChars; ++i)
			{
				const char currentChar = buffer[static_cast<size_t>(i)];

				switch (state)
				{
				case State::Normal:
					if (currentChar == '{') state = State::SawOpenBrace;
					else out.put(currentChar);
					break;

				case State::SawOpenBrace:
					if (currentChar == '{')
					{
						state = State::InToken;
						tokenLen = 0;
					}
					else
					{
						out.put('{');
						if (currentChar == '{')
						{
							state = State::SawOpenBrace;
						}
						else
						{
							out.put(currentChar);
							state = State::Normal;
						}
					}
					break;

				case State::InToken:
					if (currentChar == '}')
					{
						state = State::SawCloseBrace;
					}
					else
					{
						pushTokenChar(currentChar);
					}
					break;

				case State::SawCloseBrace:
					if (currentChar == '}')
					{
						emitToken();
						state = State::Normal;
					}
					else
					{
						// '}' was part of token
						pushTokenChar('}');
						if (currentChar == '}')
						{
							state = State::SawCloseBrace;
						}
						else
						{
							pushTokenChar(currentChar);
							state = State::InToken;
						}
					}
					break;
				}
			}
		}

		// EOF cleanup
		if (state == State::SawOpenBrace)
		{
			out.put('{');
			return;
		}

		if (state == State::InToken || state == State::SawCloseBrace)
			throw std::runtime_error("Unterminated template placeholder '{{...}}'.");
	}

}