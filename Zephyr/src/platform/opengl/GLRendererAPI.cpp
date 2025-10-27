module;

#include <glad/glad.h>

module zephyr.opengl.GLRendererAPI;

namespace zephyr
{
	GLRendererAPI::GLRendererAPI(int width, int height)
	{
		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = width;
		fbSpec.Height = height;

		m_frameBuffer = CreateScope<GLFrameBuffer>(fbSpec);
	}

	void GLRendererAPI::OnEvent(const ApplicationEvent& e)
	{
		if (e.GetEventType() == EventType::WINDOW_RESIZE_EVENT)
		{
			const auto& resizeEvent = (WindowResizeEvent&)e;
			m_frameBuffer->Resize(resizeEvent.GetWidth(), resizeEvent.GetHeight());
		}
	}

	void GLRendererAPI::StartOfTheFrame()
	{
		m_frameBuffer->Bind();
		
		//TODO remove
		glViewport(0, 0, (GLsizei)m_frameBuffer->Width(), (GLsizei)m_frameBuffer->Height());
		glDisable(GL_SCISSOR_TEST);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRendererAPI::EndOfTheFrame()
	{
		m_frameBuffer->UnBind();
	}
}