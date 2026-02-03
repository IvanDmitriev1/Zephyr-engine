export module Zephyr.Renderer.Shaders.ShaderLoader;

import Zephyr.Renderer.RHI.Interfaces.Device;

export namespace Zephyr
{
	struct ShaderStageLoadInfo
	{
		std::filesystem::path Path;
		RHI::ShaderStage Stage;
	};

	class ShaderLoader final
	{
	public:
        // Load from multiple files (e.g., shader.vert + shader.frag)
        static Ref<RHI::IShader> Load(
            std::string_view name,
            std::span<const ShaderStageLoadInfo> stages
        );

        // Load from single file with #type directives
        static Ref<RHI::IShader> LoadFromFile(
            std::string_view name,
            const std::filesystem::path& path
        );

        // Convenience: auto-detect .vert/.frag/.geom extensions
        static Ref<RHI::IShader> LoadFromPath(
            std::string_view name,
            const std::filesystem::path& basePath
        );

    private:
        static std::string ReadFile(const std::filesystem::path& path);

        static std::vector<std::pair<RHI::ShaderStage, std::string>> PreprocessShader(std::string_view source);

        static RHI::ShaderStage ExtensionToStage(std::string_view extension);
	};
}
