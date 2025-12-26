module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlVertexArray;

import Zephyr.Renderer.OpenGL.Resources.GlVertexArrayTypes;
import Zephyr.Renderer.OpenGL.Debug;
import Zephyr.Renderer.OpenGL.GlBuffers;

namespace Zephyr::RHI::OpenGL
{
	GlVertexArray::GlVertexArray(VertexArrayCreateInfo createInfo)
		:m_IndexBuffer(std::move(createInfo.IndexBuffer)),
		m_VertexBuffer(std::move(createInfo.VertexBuffer)),
		m_Layout{ std::move(createInfo.Layout) }
	{
		Assert(m_VertexBuffer, "GlVertexArray: VertexBuffer is null");

		glCreateVertexArrays(1, &m_RendererID);
		Assert(m_RendererID, "glCreateVertexArrays");
		Debug::SetGlDebugLabel(GL_VERTEX_ARRAY, m_RendererID, createInfo.DebugName);

		BindVertexBuffer();
		ConfigureVertexAttributes();
		BindIndexBuffer();
	}

	GlVertexArray::~GlVertexArray()
	{
		if (m_RendererID)
			glDeleteVertexArrays(1, &m_RendererID);
	}

	void GlVertexArray::BindVertexBuffer()
	{
		const auto vbId = (std::static_pointer_cast<GlVertexBuffer>(m_VertexBuffer))->GetUnderlyingBuffer().RendererID();
		const GLuint binding = 0;

		glVertexArrayVertexBuffer(
			m_RendererID,
			binding,
			vbId,
			0,
			static_cast<GLsizei>(m_Layout.GetStride())
		);
	}

	void GlVertexArray::ConfigureVertexAttributes()
	{
		const GLuint binding = 0;

		for (const auto& attr : m_Layout.GetAttributes())
		{
			Assert(attr.Type != VertexAttributeType::None, "GlVertexArray::ConfigureVertexAttributes: invalid vertexAttributeType");

			const GLuint baseLoc = attr.Location;
			const GLenum glType = ToGlBaseType(attr.Type);
			const uint32_t componentCount = VertexAttributeTypeComponentCount(attr.Type);
			Assert(componentCount, "GlVertexArray: unsupported attribute type");

			glEnableVertexArrayAttrib(m_RendererID, baseLoc);

			if (VertexAttributeTypeIsInteger(attr.Type))
			{
				glVertexArrayAttribIFormat(m_RendererID, baseLoc, (GLint)componentCount, glType, attr.Offset);
			}
			else
			{
				glVertexArrayAttribFormat(m_RendererID, baseLoc, (GLint)componentCount, glType,
										  attr.Normalized ? GL_TRUE : GL_FALSE,
										  attr.Offset);
			}

			glVertexArrayAttribBinding(m_RendererID, baseLoc, binding);
		}
	}

	void GlVertexArray::BindIndexBuffer()
	{
		if (!m_IndexBuffer)
		{
			return;
		}

		const auto ibId = (std::static_pointer_cast<GlIndexBuffer>(m_IndexBuffer))->GetUnderlyingBuffer().RendererID();
		glVertexArrayElementBuffer(m_RendererID, ibId);
	}
}