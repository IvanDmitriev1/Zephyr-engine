export module zephyr.renderer.IRenderPass;

export import zephyr.renderer.IRendererAPI;

export namespace zephyr
{
    class IRenderPass
    {
    public:
        IRenderPass() = default;
        virtual ~IRenderPass() = default;

        IRenderPass(const IRenderPass&) = delete;
        IRenderPass& operator=(const IRenderPass&) = delete;

    public:
        virtual void Begin(IRendererAPI& api) = 0;
        virtual void End(IRendererAPI& api) = 0;
    };
}