export module Zephyr.Renderer.RHI.IShader;

export import Zephyr.Renderer.RHI.ShaderTypes;
export import glm;

export namespace Zephyr::RHI
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

    public:
        virtual std::string_view GetName() const noexcept = 0;
    };

}