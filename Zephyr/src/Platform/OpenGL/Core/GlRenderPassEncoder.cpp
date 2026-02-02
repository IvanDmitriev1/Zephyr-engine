module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlRenderPassEncoder;

import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlVertexArray;
import Zephyr.Renderer.OpenGL.GlBuffer;
import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.Types.GlPipelineTypes;

import zephyr.logging.LogHelpers;

namespace Zephyr::RHI::OpenGL
{
	GlRenderPassEncoder::GlRenderPassEncoder(const RenderPassDesc& desc)
		:m_Framebuffer(desc.Target)
	{
		auto& glFb = StaticCast<GlFrameBuffer>(m_Framebuffer);
		glFb.Bind();
		glFb.ClearForRenderPass(desc);
	}

	GlRenderPassEncoder::~GlRenderPassEncoder()
	{
		auto& glFb = StaticCast<GlFrameBuffer>(m_Framebuffer);
		glFb.Unbind();
	}

	void GlRenderPassEncoder::BindPipeline(const Ref<IPipeline>& pipeline)
	{
		auto& glp = StaticCast<GlPipeline>(pipeline);
		glp.Bind();

		m_CurrentPipeline = pipeline;
	}

	void GlRenderPassEncoder::BindVertexArray(const Ref<IVertexArray>& vao)
    {
        auto& glvao = StaticCast<GlVertexArray>(vao);
        glvao.Bind();

        m_BoundedVao = vao;
    }

	void GlRenderPassEncoder::BindResources(std::span<const ResourceBinding> bindings)
	{
		for (const ResourceBinding& binding : bindings)
		{
			std::visit([slot = binding.BindingSlot](auto&& resource)
			{
				using ResourceT = std::decay_t<decltype(resource)>;

				if constexpr (std::is_same_v<ResourceT, Ref<IBuffer>>)
				{
					auto& glBuf = StaticCast<GlBuffer>(resource);
					Assert(HasFlag(glBuf.GetDesc().Usage, BufferUsage::Uniform),
						   "GlRenderPassEncoder::BindResources: Buffer is not uniform.");

					const uint32_t id = glBuf.RendererID();
					glBindBufferBase(GL_UNIFORM_BUFFER, slot, id);
				}
				else if constexpr (std::is_same_v<ResourceT, Ref<ITexture>>)
				{
					auto& glTex = StaticCast<GlTexture>(resource);
					const GLuint texId = glTex.GetId();
					glBindTextureUnit(slot, texId);
				}
				else if constexpr (std::is_same_v<ResourceT, Ref<ISampler>>)
				{
					// TODO: bind sampler to unit 'slot'
					// auto& glSampler = StaticCast<GlSampler>(resource);
					// glBindSampler(slot, glSampler.GetId());
				}
				else
					static_assert(false, "non-exhaustive visitor!");
			}, binding.Resource);
		}
	}

    void GlRenderPassEncoder::Draw(uint32_t vertexCount, uint32_t firstVertex)
    {
		Assert(m_CurrentPipeline, "GlCommandList: Draw called without bound pipeline");
		Assert(m_BoundedVao, "GlCommandList: Draw called without bound VAO");

        const auto mode = ToGlTopology(m_CurrentPipeline->GetDesc().Topology);
		glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(vertexCount));
    }

    void GlRenderPassEncoder::DrawIndexed(uint32_t indexCount, uint32_t firstIndex)
    {
		Assert(m_CurrentPipeline, "GlCommandList: DrawIndexed called without bound pipeline");
		Assert(m_BoundedVao && m_BoundedVao->GetIndexBinding().has_value(),
			   "GlCommandList: DrawIndexed called without bound index buffer");

        const auto mode = ToGlTopology(m_CurrentPipeline->GetDesc().Topology);
        const auto& indexBinding = m_BoundedVao->GetIndexBinding();
        const auto idxType = indexBinding->Type;

        const GLenum glIndexType = (idxType == IndexType::UInt16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        const uintptr_t indexSize = GetIndexSize(idxType);
        const void* offset = reinterpret_cast<const void*>(static_cast<uintptr_t>(firstIndex) * indexSize);

		glDrawElements(mode, static_cast<GLsizei>(indexCount), glIndexType, offset);
	}
}