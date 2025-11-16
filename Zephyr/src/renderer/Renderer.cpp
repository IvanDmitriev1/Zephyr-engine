module zephyr.renderer.Renderer;

namespace zephyr
{
	void Renderer::Init(IRendererAPI* api, uint32_t width, uint32_t height)
	{
		s_API = api;

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = width;
		fbSpec.Height = height;

		s_SceneFramebuffer = IFrameBuffer::Create(fbSpec);
	}

	void Renderer::Shutdown()
	{
		s_SceneFramebuffer.reset();
		s_API = nullptr;
	}

	void Renderer::BeginFrame()
	{
		s_API->BeginFrame();
		s_SceneFramebuffer->Bind();

		s_API->Clear(true, true);
	}

	void Renderer::EndFrame()
	{
		s_Queue.Flush(*s_API, s_ViewProjection);

		s_SceneFramebuffer->UnBind();
		s_API->EndFrame();
		s_Queue.Clear();
	}

	void Renderer::Submit(const DrawCommand& cmd)
	{
		s_Queue.Submit(cmd);
	}

	void Renderer::SetViewProjection(const glm::mat4& viewProjection)
	{
		s_ViewProjection = viewProjection;
	}
}