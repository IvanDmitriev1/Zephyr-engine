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

			glViewport(0, 0, resizeEvent.GetWidth(), resizeEvent.GetHeight());
			m_frameBuffer->Resize(resizeEvent.GetWidth(), resizeEvent.GetHeight());
		}
	}

	void GLRendererAPI::StartOfTheFrame()
	{

	}

	void GLRendererAPI::EndOfTheFrame()
	{

	}
}