module;
export module zephyr.opengl.GLRendererAPI;

import zephyr.renderer.IRendererAPI;
import zephyr.renderer.FrameBufferSpecs;
import zephyr.opengl.GLFrameBuffer;
import zephyr.core.coreTypes;

export namespace zephyr
{
	class GLRendererAPI final : public IRendererAPI
	{
	public:
		GLRendererAPI(int width, int height);
		~GLRendererAPI() override = default;

	public:
		IFrameBuffer& GetFrameBuffer() const override
		{
			return *m_frameBuffer;
		}

	public:
		void OnEvent(const ApplicationEvent& e) override;
		void StartOfTheFrame() override;
		void EndOfTheFrame() override;

	private:
		Scope<GLFrameBuffer> m_frameBuffer;
	};
}