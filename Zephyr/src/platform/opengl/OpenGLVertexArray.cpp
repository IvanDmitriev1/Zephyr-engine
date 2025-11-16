module;

#include <glad/glad.h>

module zephyr.opengl.OpenGLVertexArray;

namespace zephyr
{
	Ref<IVertexArray> zephyr::IVertexArray::Create(const VertexArrayCreateInfo& info)
	{
		return CreateRef<OpenGLVertexArray>(info);
	}

	OpenGLVertexArray::OpenGLVertexArray(const VertexArrayCreateInfo& info)
		: m_VertexBuffer(info.VertexBuffer)
		, m_IndexBuffer(info.IndexBuffer)
		, m_Layout(std::move(const_cast<VertexLayout&>(info.Layout)))
		, m_IndexType(info.IndexType)
	{
		glGenVertexArrays(1, &m_RendererID);
		Bind();

		SetVertexBuffer();
		SetIndexBuffer();

		Unbind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		if (m_RendererID)
			glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArray::SetVertexBuffer()
	{
		auto glBuffer = std::static_pointer_cast<OpenGLBuffer>(m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, glBuffer->GetRendererID());
		ConfigureVertexAttributes(*glBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer()
	{
		auto glBuffer = std::static_pointer_cast<OpenGLBuffer>(m_IndexBuffer);
		const uint32_t elementSize = IndexTypeSize(m_IndexType);
		m_IndexCount = elementSize ? static_cast<uint32_t>(m_IndexBuffer->GetSize() / elementSize) : 0;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glBuffer->GetRendererID());
	}

	void OpenGLVertexArray::ConfigureVertexAttributes(const OpenGLBuffer& glVertexBuffer)
	{
		const auto& attributes = m_Layout.GetAttributes();
		const uint32_t stride = m_Layout.GetStride();

		GLuint index = 0;
		for (const auto& attr : attributes)
		{
			GLenum type = GL_FLOAT;
			GLint  componentCount = 0;
			GLboolean normalized = attr.Normalized ? GL_TRUE : GL_FALSE;

			switch (attr.Type)
			{
			case ShaderDataType::Float:  componentCount = 1; type = GL_FLOAT; break;
			case ShaderDataType::Float2: componentCount = 2; type = GL_FLOAT; break;
			case ShaderDataType::Float3: componentCount = 3; type = GL_FLOAT; break;
			case ShaderDataType::Float4: componentCount = 4; type = GL_FLOAT; break;
			case ShaderDataType::Int:    componentCount = 1; type = GL_INT;   break;
			case ShaderDataType::Int2:   componentCount = 2; type = GL_INT;   break;
			case ShaderDataType::Int3:   componentCount = 3; type = GL_INT;   break;
			case ShaderDataType::Int4:   componentCount = 4; type = GL_INT;   break;
			default:
				continue;
			}

			glEnableVertexAttribArray(index);

			if (type == GL_INT)
			{
				glVertexAttribIPointer(index,
					componentCount,
					type,
					static_cast<GLsizei>(stride),
					reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.Offset)));
			}
			else
			{
				glVertexAttribPointer(index,
					componentCount,
					type,
					normalized,
					static_cast<GLsizei>(stride),
					reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.Offset)));
			}

			++index;
		}
	}
}