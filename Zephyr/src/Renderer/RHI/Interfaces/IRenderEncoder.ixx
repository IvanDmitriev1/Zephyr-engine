export module Zephyr.Renderer.RHI.Interfaces.IRenderEncoder;

import Zephyr.Renderer.RHI.Types.RenderEncoderTypes;
import Zephyr.Renderer.RHI.Interfaces.IVertexArray;
import Zephyr.Renderer.RHI.Interfaces.IPipeline;

export namespace Zephyr::RHI
{
    class IRenderEncoder
    {
    public:
        virtual ~IRenderEncoder() = default;

		virtual void BindPipeline(const Ref<IPipeline>& pipeline) = 0;
        virtual void BindVertexArray(const Ref<IVertexArray>& vao) = 0;
		virtual void BindResources(std::span<const ResourceBinding> bindings) = 0;

        // Draw commands
        virtual void Draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
        virtual void DrawIndexed(uint32_t indexCount, uint32_t firstIndex = 0) = 0;
    };
}
