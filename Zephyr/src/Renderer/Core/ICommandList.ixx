export module Zephyr.Renderer.Core.ICommandList;

export import Zephyr.Renderer.Resources.RenderPassTypes;
export import Zephyr.Renderer.Core.IPipeline;
export import Zephyr.Renderer.Core.IVertexArray;
export import Zephyr.Renderer.Resources.CommandListTypes;

export namespace Zephyr::RHI
{
    class ICommandList
    {
    public:
        virtual ~ICommandList() = default;

        // Render pass
        virtual void BeginRenderPass(const RenderPassDesc& rp) = 0;
        virtual void EndRenderPass() = 0;

        // Pipeline binding
        virtual void BindPipeline(const Ref<IPipeline>& pipeline) = 0;

        // Resource binding
        virtual void BindVertexArray(const Ref<IVertexArray>& vao) = 0;

		virtual void BindResources(std::span<ResourceBinding> bindings) = 0;

        // Draw commands
        virtual void Draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
        virtual void DrawIndexed(uint32_t indexCount, uint32_t firstIndex = 0) = 0;
    };
}