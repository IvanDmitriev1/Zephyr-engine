module;
export module zephyr.opengl.GLContext;

import zephyr.renderer.IGraphicsContext;

import <GLFW/glfw3.h>;

export namespace zephyr
{
	class GLContext final : public IGraphicsContext
	{
	public:
		explicit GLContext(GLFWwindow* window);
		~GLContext() override = default;

	public:
		Scope<IRendererAPI> CreateRendererAPI(uint32_t width, uint32_t height) override;
		Scope<IUiRenderContext> CreateUiContext() override;
		void SetSwapInterval(int interval) override;

	public:
		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_window = nullptr;
	};
}