module;

#include <glad/glad.h>

module zephyr.opengl.GLRendererAPI;

namespace zephyr
{
	GLenum ToGLPrimitive(PrimitiveTopology topology)
	{
		switch (topology)
		{
		case PrimitiveTopology::Triangles: return GL_TRIANGLES;
		case PrimitiveTopology::Lines:     return GL_LINES;
		default:                           return GL_TRIANGLES;
		}
	}

	GLenum ToGLIndexType(IndexType type)
	{
		switch (type)
		{
		case IndexType::UInt16: return GL_UNSIGNED_SHORT;
		case IndexType::UInt32: return GL_UNSIGNED_INT;
		default:                return GL_UNSIGNED_INT;
		}
	}

	void GLRendererAPI::BeginFrame()
	{
	}

	void zephyr::GLRendererAPI::EndFrame()
	{
	}

	void GLRendererAPI::SetDepthTest(bool enabled)
	{
		if (enabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void GLRendererAPI::SetScissorTest(bool enabled)
	{
		if (enabled)
			glEnable(GL_SCISSOR_TEST);
		else
			glDisable(GL_SCISSOR_TEST);
	}

	void GLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRendererAPI::Clear(bool color, bool depth)
	{
		GLbitfield mask = 0;
		if (color) mask |= GL_COLOR_BUFFER_BIT;
		if (depth) mask |= GL_DEPTH_BUFFER_BIT;

		glClear(mask);
	}

	void GLRendererAPI::DrawIndexed(const IVertexArray& vao, PrimitiveTopology topology)
	{
		vao.Bind();

		const uint32_t indexCount = vao.GetIndexCount();
		if (indexCount == 0)
			return;

		const auto indexType = vao.GetIndexType();

		glDrawElements(
			ToGLPrimitive(topology),
			static_cast<GLsizei>(indexCount),
			ToGLIndexType(indexType),
			nullptr
		);
	}
}