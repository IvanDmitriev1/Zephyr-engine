module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlCommandList;

import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlVertexArray;
import Zephyr.Renderer.OpenGL.GlBuffer;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.Resources.GlPipelineTypes;

namespace Zephyr::RHI::OpenGL
{
	void GlCommandList::Begin()
	{
		m_IsInRenderPass = false;
		m_BoundedPipeline.reset();
		m_BoundedVao.reset();
	}

	void GlCommandList::End()
	{
		Assert(!m_IsInRenderPass, "GlCommandList: End called while still in render pass");
	}

	void GlCommandList::BeginRenderPass(const RenderPassDesc& rp)
	{
        Assert(!m_IsInRenderPass, "GlCommandList: BeginRenderPass called while already in a render pass");
        m_IsInRenderPass = true;

        auto& glFb = StaticCastRef<GlFrameBuffer>(rp.Target);
        glFb.Bind();
        glFb.ClearForRenderPass(rp);
	}
    void GlCommandList::EndRenderPass()
    {
        Assert(m_IsInRenderPass, "GlCommandList: EndRenderPass called without BeginRenderPass");
        m_IsInRenderPass = false;

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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

	void GlCommandList::BindUniformBuffer(uint32_t binding, const Ref<IBuffer>& buffer)
	{
		Assert(buffer, "GlCommandList: BindUniformBuffer received null buffer");

		auto& glBuffer = StaticCastRef<GlBuffer>(buffer);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, glBuffer.RendererID());
	}

	void GlCommandList::SetUniformMat4(uint32_t location, const glm::mat4 & value)
	{
		Assert(m_BoundedPipeline, "GlCommandList: SetUniformMat4 called without bound pipeline");

		uint32_t program = GetCurrentShaderProgram();
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

	}

	void GlCommandList::SetUniformFloat3(uint32_t location, const glm::vec3 & value)
	{
		Assert(m_BoundedPipeline, "GlCommandList: SetUniformFloat3 called without bound pipeline");

		uint32_t program = GetCurrentShaderProgram();
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

    void GlCommandList::Draw(uint32_t vertexCount, uint32_t firstVertex)
    {
		Assert(m_IsInRenderPass, "GlCommandList: Draw called outside render pass");
		Assert(m_BoundedPipeline, "GlCommandList: Draw called without bound pipeline");
		Assert(m_BoundedVao, "GlCommandList: Draw called without bound VAO");

        const auto mode = ToGlTopology(m_BoundedPipeline->GetDesc().Topology);
		glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(vertexCount));
    }

    void GlCommandList::DrawIndexed(uint32_t indexCount, uint32_t firstIndex)
    {
		Assert(m_IsInRenderPass, "GlCommandList: DrawIndexed called outside render pass");
		Assert(m_BoundedPipeline, "GlCommandList: DrawIndexed called without bound pipeline");
		Assert(m_BoundedVao && m_BoundedVao->GetIndexBinding().has_value(),
			   "GlCommandList: DrawIndexed called without bound index buffer");

        const auto mode = ToGlTopology(m_BoundedPipeline->GetDesc().Topology);
        const auto& indexBinding = m_BoundedVao->GetIndexBinding();
        const auto idxType = indexBinding->Type;

        const GLenum glIndexType = (idxType == IndexType::UInt16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        const uintptr_t indexSize = GetIndexSize(idxType);
        const void* offset = reinterpret_cast<const void*>(static_cast<uintptr_t>(firstIndex) * indexSize);

		glDrawElements(mode, static_cast<GLsizei>(indexCount), glIndexType, offset);
	}

	uint32_t GlCommandList::GetCurrentShaderProgram() const
	{
		Assert(m_BoundedPipeline, "No pipeline bound");

		auto& glPipeline = StaticCastRef<GlPipeline>(m_BoundedPipeline);
		auto& shader = glPipeline.GetDesc().Shader;
		Assert(shader, "GlCommandList: No active shader program");

		auto& glShader = StaticCastRef<GlShader>(shader);
		return glShader.GetRendererID();
	}
}