module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlCommandList;

import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlVertexArray;

import Zephyr.Renderer.OpenGL.Resources.GlPipelineTypes;

namespace Zephyr::RHI::OpenGL
{
	void GlCommandList::Begin() {}
	void GlCommandList::End() {}

	void GlCommandList::BeginRenderPass(const RenderPassDesc& rp)
	{
        Assert(!m_IsInRenderPass, "GlCommandList: BeginRenderPass called while already in a render pass");
        m_IsInRenderPass = true;

        if (rp.Target)
        {
            auto& glFb = StaticCastRef<GlFrameBuffer>(rp.Target);
            glFb.Bind();
            glFb.ClearForRenderPass(rp);
        }
        else
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            GlFrameBuffer::ClearDefaultFrameBuffer(rp);
        }
	}
    void GlCommandList::EndRenderPass()
    {
        Assert(m_IsInRenderPass, "GlCommandList: EndRenderPass called without BeginRenderPass");
        m_IsInRenderPass = false;
    }

    void GlCommandList::BindPipeline(const Ref<IPipeline>& pipeline)
    {
        auto& glp = StaticCastRef<GlPipeline>(pipeline);
        glp.ApplyState();

        m_BoundedPipeline = pipeline;
    }

    void GlCommandList::BindVertexArray(const Ref<IVertexArray>& vao)
    {
        auto& glvao = StaticCastRef<GlVertexArray>(vao);
        glvao.Bind();

        m_BoundedVao = vao;
    }

    void GlCommandList::SetViewport(float x, float y, float w, float h)
    {
        glViewport((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
    }

    void GlCommandList::SetScissor(int32_t x, int32_t y, uint32_t w, uint32_t h)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, (GLsizei)w, (GLsizei)h);
    }

    void GlCommandList::Draw(uint32_t vertexCount, uint32_t firstVertex)
    {
        Assert(m_BoundedPipeline, "GlCommandList::Draw: no pipeline bound");

        const auto mode = ToGlTopology(m_BoundedPipeline->GetDesc().Topology);
        glDrawArrays(mode, (GLint)firstVertex, (GLsizei)vertexCount);
    }

    void GlCommandList::DrawIndexed(uint32_t indexCount, uint32_t firstIndex)
    {
        Assert(m_BoundedPipeline, "GlCommandList::Draw: no pipeline bound");
        Assert(m_BoundedVao && m_BoundedVao->HasIndexBuffer(), "GlCommandList::DrawIndexed: no VAO/index buffer bound");

        const auto mode = ToGlTopology(m_BoundedPipeline->GetDesc().Topology);
        const auto& indexBuffer = m_BoundedVao->GetIndexBuffer();
        const auto idxType = indexBuffer->GetIndexType();

        const GLenum glIndexType = (idxType == IndexType::UInt16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        const uintptr_t indexSize = (idxType == IndexType::UInt16) ? 2u : 4u;
        const void* offset = reinterpret_cast<const void*>(static_cast<uintptr_t>(firstIndex) * indexSize);

        glDrawElements(mode, (GLsizei)indexCount, glIndexType, offset);
    }
}