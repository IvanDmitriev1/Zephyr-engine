export module Zephyr.Renderer.Platform.IUiRenderContext;

export namespace Zephyr
{
    class IUiRenderContext
    {
    public:
        virtual ~IUiRenderContext() = default;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;
    };
}