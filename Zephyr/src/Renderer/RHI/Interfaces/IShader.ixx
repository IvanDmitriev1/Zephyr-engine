export module Zephyr.Renderer.RHI.Interfaces.IShader;

import Zephyr.Renderer.RHI.Types.ShaderTypes;

export namespace Zephyr::RHI
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

    public:
        virtual std::string_view GetName() const noexcept = 0;
		virtual size_t GetHash() const noexcept = 0;
    };

}
