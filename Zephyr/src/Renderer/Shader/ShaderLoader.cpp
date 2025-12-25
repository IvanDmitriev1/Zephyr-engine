module Zephyr.Renderer.Shader.ShaderLoader;

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

        return Ref<RHI::IShader>();
    }

    Ref<RHI::IShader> ShaderLoader::LoadFromFile(std::string_view name, const std::filesystem::path& path)
    {
        return Ref<RHI::IShader>();
    }

    Ref<RHI::IShader> ShaderLoader::LoadFromPath(std::string_view name, const std::filesystem::path& basePath)
    {
        return Ref<RHI::IShader>();
    }
}