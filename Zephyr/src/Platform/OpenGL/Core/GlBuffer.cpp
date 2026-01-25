module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlBuffer;

import Zephyr.Renderer.OpenGL.Resources.GlBufferTypes;
import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::RHI::OpenGL
{
	GlBuffer::GlBuffer(BufferDesc desc)
		:m_Desc(desc)
	{
		if (m_Desc.SizeBytes == 0)
			throw std::runtime_error("GlBuffer: SizeBytes must be > 0");

		glCreateBuffers(1, &m_RendererID);
		Assert(m_RendererID, "GlBuffer: glCreateBuffers failed");

		glNamedBufferData(m_RendererID, (GLsizeiptr)m_Desc.SizeBytes, nullptr, ToGlUsage(m_Desc.Access));
		Debug::SetGlDebugLabel(GL_BUFFER, m_RendererID, m_Desc.DebugName);
	}

	GlBuffer::~GlBuffer()
	{
		if (m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void GlBuffer::SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes)
	{
		Assert(dstOffsetBytes + data.size() <= m_Desc.SizeBytes, "GlBuffer::SetData: write out of bounds");

		glNamedBufferSubData(m_RendererID,
							 static_cast<GLintptr>(dstOffsetBytes),
							 static_cast<GLsizeiptr>(data.size_bytes()),
							 data.data());
	}
}