export module Zephyr.Renderer.Core.ISwapchain;

export import Zephyr.Renderer.Resources.SwapchainTypes;
export import Zephyr.Renderer.Core.ITexture;
export import Zephyr.Renderer.Core.IFrameBuffer;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
    class ISwapchain
    {
    public:
        virtual ~ISwapchain() = default;

    public:
        virtual const Ref<IFrameBuffer> GetBackBuffer() const = 0;

        virtual void BeginFrame() = 0;
        virtual void Present() = 0;
        virtual void Resize(glm::vec2 newSize) = 0;
    };
}