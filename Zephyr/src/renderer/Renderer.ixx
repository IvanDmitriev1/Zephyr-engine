export module zephyr.renderer.Renderer;

import zephyr.renderer.IRendererAPI;
import zephyr.renderer.IFrameBuffer;
import zephyr.renderer.RenderCommandQueue;

export namespace zephyr
{
	class Renderer
	{
	public:
		static void Init(IRendererAPI* api, uint32_t width, uint32_t height);
		static void Shutdown();

	public:
		static void BeginFrame();
		static void EndFrame();

		static void Submit(const DrawCommand& cmd);
		static void SetViewProjection(const glm::mat4& viewProjection);

	public:
		static IRendererAPI& GetAPI()
		{
			return *s_API;
		}

		static IFrameBuffer& GetFrameBuffer()
		{
			return *s_SceneFramebuffer;
		}

	private:
		static inline IRendererAPI* s_API = nullptr;
		static inline Ref<IFrameBuffer> s_SceneFramebuffer;
		static inline RenderCommandQueue s_Queue{};

		static inline glm::mat4 s_ViewProjection{ 1.0f };
	};
}