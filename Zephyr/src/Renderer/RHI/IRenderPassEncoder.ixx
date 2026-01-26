export module Zephyr.Renderer.RHI.IRenderPassEncoder;

export import Zephyr.Renderer.RHI.RenderPassTypes;
export import Zephyr.Renderer.RHI.IPipeline;
export import Zephyr.Renderer.RHI.IVertexArray;
export import Zephyr.Renderer.RHI.RenderPassEncoderTypes;

export namespace Zephyr::RHI
{
    class IRenderPassEncoder
    {
    public:
        virtual ~IRenderPassEncoder() = default;

		virtual void BindPipeline(const Ref<IPipeline>& pipeline) = 0;
        virtual void BindVertexArray(const Ref<IVertexArray>& vao) = 0;
		virtual void BindResources(std::span<const ResourceBinding> bindings) = 0;

        // Draw commands
        virtual void Draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
        virtual void DrawIndexed(uint32_t indexCount, uint32_t firstIndex = 0) = 0;
    };
}