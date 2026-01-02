module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlRenderPassEncoder;

import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlVertexArray;
import Zephyr.Renderer.OpenGL.GlBuffer;
import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.Resources.GlPipelineTypes;

namespace Zephyr::RHI::OpenGL
{
	GlRenderPassEncoder::GlRenderPassEncoder(const RenderPassDesc& rp)
	{
		auto& glFb = StaticCastRef<GlFrameBuffer>(rp.Target);
		glFb.Bind();
		glFb.ClearForRenderPass(rp);
	}

	GlRenderPassEncoder::~GlRenderPassEncoder()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void GlRenderPassEncoder::BindPipeline(const Ref<IPipeline>& pipeline)
    {
        auto& glp = StaticCastRef<GlPipeline>(pipeline);
        glp.ApplyState();

        m_BoundedPipeline = pipeline;
    }

    void GlRenderPassEncoder::BindVertexArray(const Ref<IVertexArray>& vao)
    {
        auto& glvao = StaticCastRef<GlVertexArray>(vao);
        glvao.Bind();

        m_BoundedVao = vao;
    }

	void GlRenderPassEncoder::BindResources(std::span<ResourceBinding> bindings)
	{
		for (const ResourceBinding& binding : bindings)
		{
			if (binding.UniformBuffer)
			{
				auto& glBuf = StaticCastRef<GlBuffer>(binding.UniformBuffer);
				const uint32_t id = glBuf.RendererID();
				glBindBufferBase(GL_UNIFORM_BUFFER, binding.Slot, id);
			}

			if (binding.Texture)
			{
				auto& glTex = StaticCastRef<GlTexture>(binding.Texture);
				const GLuint texId = glTex.GetId();
				glBindTextureUnit(binding.Slot, texId);
			}

			if (binding.Sampler)
			{
				//TODO
			}
		}
	}

    void GlRenderPassEncoder::Draw(uint32_t vertexCount, uint32_t firstVertex)
    {
		Assert(m_IsInRenderPass, "GlCommandList: Draw called outside render pass");
		Assert(m_BoundedPipeline, "GlCommandList: Draw called without bound pipeline");
		Assert(m_BoundedVao, "GlCommandList: Draw called without bound VAO");

        const auto mode = ToGlTopology(m_BoundedPipeline->GetDesc().Topology);
		glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(vertexCount));
    }

    void GlRenderPassEncoder::DrawIndexed(uint32_t indexCount, uint32_t firstIndex)
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

	uint32_t GlRenderPassEncoder::GetCurrentShaderProgram() const
	{
		Assert(m_BoundedPipeline, "No pipeline bound");

		auto& glPipeline = StaticCastRef<GlPipeline>(m_BoundedPipeline);
		auto& shader = glPipeline.GetDesc().Shader;
		Assert(shader, "GlCommandList: No active shader program");

		auto& glShader = StaticCastRef<GlShader>(shader);
		return glShader.GetRendererID();
	}
}