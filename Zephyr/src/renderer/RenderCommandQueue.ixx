export module zephyr.renderer.RenderCommandQueue;

export import zephyr.renderer.IRendererAPI;

export namespace zephyr
{
    class RenderCommandQueue
    {
    public:
        RenderCommandQueue() = default;
		~RenderCommandQueue() = default;

        RenderCommandQueue(const RenderCommandQueue&) = delete;
        RenderCommandQueue& operator=(const RenderCommandQueue&) = delete;

    public:
        void Submit(const DrawCommand& cmd);
        void Clear();
        void Flush(IRendererAPI& api, const glm::mat4& viewProjection);

    private:
        std::vector<DrawCommand> m_Commands;
    };
}