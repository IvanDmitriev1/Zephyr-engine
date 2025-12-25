export module Zephyr.Renderer.Core.IShader;

export import Zephyr.Renderer.Resources.ShaderTypes;
export import glm;

export namespace Zephyr::RHI
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

        virtual std::string_view GetName() const noexcept = 0;

        // Uniform setters (OpenGL-style for now)
        virtual void SetInt(std::string_view name, int value) = 0;
        virtual void SetFloat(std::string_view name, float value) = 0;
        virtual void SetFloat2(std::string_view name, const glm::vec2& value) = 0;
        virtual void SetFloat3(std::string_view name, const glm::vec3& value) = 0;
        virtual void SetFloat4(std::string_view name, const glm::vec4& value) = 0;
        virtual void SetMat4(std::string_view name, const glm::mat4& value) = 0;
    };

}