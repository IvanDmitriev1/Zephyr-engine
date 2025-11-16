module;

#include <glad/glad.h>

module zephyr.opengl.OpenGLBuffer;

namespace zephyr
{
	Ref<IBuffer> IBuffer::Create(const BufferCreateInfo& info)
	{
		return CreateRef<OpenGLBuffer>(info);
	}


	OpenGLBuffer::OpenGLBuffer(const BufferCreateInfo& info)
		: m_Type(info.Type),
		m_Usage(info.Usage),
		m_Size(info.Size)
	{
		glGenBuffers(1, &m_RendererID);
		Assert(m_RendererID != 0, "Failed to create OpenGL buffer");

		Bind();
		glBufferData(
			GetGLTarget(),
			static_cast<GLsizeiptr>(m_Size),
			info.Data,
			GetGLUsage());
		Unbind();
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		if (m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLBuffer::SetData(
		const void* data,
		size_t size,
		size_t offset)
	{
		Assert(offset + size > m_Size, "OpenGLBuffer::SetData: out of range");

		Bind();
		glBufferSubData(GetGLTarget(),
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			data);
		Unbind();
	}

	void OpenGLBuffer::Bind() const
	{
		glBindBuffer(GetGLTarget(), m_RendererID);
	}

	void OpenGLBuffer::Unbind() const
	{
		glBindBuffer(GetGLTarget(), 0);
	}

	uint32_t OpenGLBuffer::GetGLTarget() const
	{
		switch (m_Type)
		{
		case BufferType::Vertex:  return GL_ARRAY_BUFFER;
		case BufferType::Index:   return GL_ELEMENT_ARRAY_BUFFER;
		case BufferType::Uniform: return GL_UNIFORM_BUFFER;
		case BufferType::Storage: return GL_SHADER_STORAGE_BUFFER;
		}
		return GL_ARRAY_BUFFER;
	}

	uint32_t OpenGLBuffer::GetGLUsage() const
	{
		switch (m_Usage)
		{
		case BufferUsage::StaticDraw:  return GL_STATIC_DRAW;
		case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
		case BufferUsage::StreamDraw:  return GL_STREAM_DRAW;
		}
		return GL_STATIC_DRAW;
	}
}