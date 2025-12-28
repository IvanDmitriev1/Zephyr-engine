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
		m_window.SwapBuffers();
	}
}