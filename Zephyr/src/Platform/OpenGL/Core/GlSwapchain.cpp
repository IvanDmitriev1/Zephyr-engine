module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlSwapchain;

namespace Zephyr::RHI::OpenGL
{
	GlSwapchain::GlSwapchain(IWindow& window, SwapchainDesc desc)
		:m_window(window)
	{
		FrameBufferDesc fb{};
		fb.Size = desc.Size;
		fb.DebugName = "Swapchain backBuffer";
		fb.ColorAttachments =
		{
			FrameBufferAttachmentDesc{ desc.ColorFormat }
		};
		fb.DepthStencilAttachment = FrameBufferAttachmentDesc{ desc.DepthFormat };

		m_BackBuffer = CreateRef<GlFrameBuffer>(fb);
	}

	void GlSwapchain::BeginFrame()
	{
		m_BackBuffer->Bind();
	}

	void GlSwapchain::Present()
	{
		const uint32_t fbo = m_BackBuffer->GetHandle();
		const auto& spec = m_BackBuffer->GetDesc();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		int width = spec.Size.x;
		int height = spec.Size.y;

		glBlitNamedFramebuffer(
			fbo, 0,
			0, 0, width, height,
			0, 0, width, height,
			GL_COLOR_BUFFER_BIT,
			GL_NEAREST);

		m_window.SwapBuffers();
	}

	void GlSwapchain::Resize(glm::vec2 newSize)
	{
		m_BackBuffer->Resize(newSize);
	}
}