export module Zephyr.Renderer.OpenGL.GlSwapchain;

export import Zephyr.Renderer.Core.ISwapchain;
export import Zephyr.Renderer.IWindow;
import Zephyr.Renderer.OpenGL.GlFrameBuffer;

export namespace Zephyr::RHI::OpenGL
{
	class GlSwapchain final : public ISwapchain
	{
	public:
		GlSwapchain(IWindow& window, SwapchainDesc desc);

		IFrameBuffer& GetBackBuffer() const override
		{
			return *m_BackBuffer;
		}

		void BeginFrame() override;
		void Present() override;
		void Resize(glm::vec2 newSize) override;

	private:
		IWindow& m_window;
		Scope<GlFrameBuffer> m_BackBuffer;
	};
}