module Zephyr.Renderer.Shaders.ShaderLoader;

namespace Zephyr
{
    Ref<RHI::IShader> ShaderLoader::Load(std::string_view name, std::span<const ShaderStageLoadInfo> stages)
    {
        std::vector<std::vector<std::byte>> stageData;
        std::vector<RHI::ShaderStageDesc> stageDescs;

        stageData.reserve(stages.size());
        stageDescs.reserve(stages.size());

        for (const auto& stage : stages)
        {
            std::string source = ReadFile(stage.Path);

            stageData.emplace_back(
                reinterpret_cast<const std::byte*>(source.data()),
                reinterpret_cast<const std::byte*>(source.data() + source.size())
            );

            stageDescs.push_back({
                .Stage = stage.Stage,
                .Code = { stageData.back().data(),stageData.back().size()}
            });
        }

        RHI::ShaderCreateInfo createInfo
        {
            .Name = name,
            .Stages = {stageDescs.data(), stageDescs.size()}
        };

        return RHI::Device::CreateShader(createInfo);
    }

    Ref<RHI::IShader> ShaderLoader::LoadFromFile(
        std::string_view name,
        const std::filesystem::path& path)
    {
        std::string source = ReadFile(path);
        auto stageMap = PreprocessShader(source);

        std::vector<std::vector<std::byte>> stageData;
        std::vector<RHI::ShaderStageDesc> stageDescs;

        for (const auto& [stage, code] : stageMap)
        {
            stageData.emplace_back(
                reinterpret_cast<const std::byte*>(code.data()),
                reinterpret_cast<const std::byte*>(code.data() + code.size())
            );

            stageDescs.push_back({
                .Stage = stage,
                .Code = { stageData.back().data(),stageData.back().size()}
            });
        }

        RHI::ShaderCreateInfo createInfo
        {
            .Name = name,
            .Stages = {stageDescs.data(), stageDescs.size()}
        };

        return RHI::Device::CreateShader(createInfo);
    }

    Ref<RHI::IShader> ShaderLoader::LoadFromPath(
        std::string_view name,
        const std::filesystem::path& basePath)
    {
        std::vector<ShaderStageLoadInfo> stages;

        const std::array extensions = {
            std::pair{".vert", RHI::ShaderStage::Vertex},
            std::pair{".frag", RHI::ShaderStage::Fragment},
            std::pair{".geom", RHI::ShaderStage::Geometry},
            std::pair{".tesc", RHI::ShaderStage::TessControl},
            std::pair{".tese", RHI::ShaderStage::TessEvaluation},
            std::pair{".comp", RHI::ShaderStage::Compute}
        };

        for (const auto& [ext, stage] : extensions)
        {
            auto path = basePath;
            path.replace_extension(ext);

            if (std::filesystem::exists(path))
            {
                stages.push_back({
                    .Path = path,
                    .Stage = stage
                                 });
            }
        }

        if (stages.empty())
        {
            throw std::runtime_error(std::format(
                "No shader stages found for base path: {}", basePath.string()
            ));
        }

        return Load(name, { stages.data(), stages.size() });
    }

    std::string ShaderLoader::ReadFile(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error(std::format(
                "Failed to open shader file: {}", path.string()
            ));
        }

        std::ostringstream contents;
        contents << file.rdbuf();
        return contents.str();
    }

    std::vector<std::pair<RHI::ShaderStage, std::string>> ShaderLoader::PreprocessShader(
        std::string_view source)
    {
        constexpr std::string_view typeToken = "#type";
        std::vector<std::pair<RHI::ShaderStage, std::string>> result;

        size_t pos = source.find(typeToken);
        while (pos != std::string_view::npos)
        {
            // Find end of line
            size_t eol = source.find_first_of("\r\n", pos);
            if (eol == std::string_view::npos)
                break;

            // Extract stage name
            size_t begin = pos + typeToken.length() + 1;
            std::string_view stageName = source.substr(begin, eol - begin);

            // Trim whitespace
            stageName.remove_prefix(
                std::min(stageName.find_first_not_of(" \t"), stageName.size())
            );
            stageName.remove_suffix(
                stageName.size() - stageName.find_last_not_of(" \t") - 1
            );

            // Determine stage type
            RHI::ShaderStage stage;
            if (stageName == "vertex")
                stage = RHI::ShaderStage::Vertex;
            else if (stageName == "fragment" || stageName == "pixel") 
                stage = RHI::ShaderStage::Fragment;
            else if (stageName == "geometry")
                stage = RHI::ShaderStage::Geometry;
            else if (stageName == "tesscontrol")
                stage = RHI::ShaderStage::TessControl;
            else if (stageName == "tessevaluation")
                stage = RHI::ShaderStage::TessEvaluation;
            else if (stageName == "compute")
                stage = RHI::ShaderStage::Compute;
            else
            {
                throw std::runtime_error(std::format("Unknown shader stage: {}", stageName));
            }

            // Find next #type or end of file
            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);

            // Extract stage code
            std::string_view code = (pos == std::string_view::npos)
                ? source.substr(nextLinePos)
                : source.substr(nextLinePos, pos - nextLinePos);

            result.push_back({ stage, std::string(code) });
        }

        if (result.empty())
        {
            throw std::runtime_error("No shader stages found in source (missing #type directives)");
        }

        return result;
    }
}