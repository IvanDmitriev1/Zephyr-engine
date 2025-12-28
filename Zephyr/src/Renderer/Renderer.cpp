module Zephyr.Renderer.Renderer;

namespace Zephyr::Renderer
{
	struct RendererData
	{
		Ref<RHI::IFrameBuffer> SceneFramebuffer;
	};

	RendererData* s_Data{};
	void Init(InitInfo&& info)
	{
		s_Data = new RendererData();
		s_Data->SceneFramebuffer = info.Swapchain->GetBackBuffer();
	}
	void ShutDown()
	{
		if (s_Data)
		{
			delete s_Data;
		}
	}
	Ref<RHI::IFrameBuffer> GetMainFrameBuffer()
	{
		return s_Data->SceneFramebuffer;
	}
}