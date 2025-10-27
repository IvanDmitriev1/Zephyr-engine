module;

#include <GLFW/glfw3.h>

export module zephyr.opengl.GLWindow;

import zephyr.core.coreTypes;
import zephyr.renderer.IWindow;
import zephyr.renderer.IGraphicsContext;
import zephyr.renderer.IUiRenderContext;

export namespace zephyr
{
	class GLWindow : public IWindow
	{
	public:
		GLWindow(const WindowSpecification& spec);
		~GLWindow() override;

	public:
		void* GetNativeWindow() const override
		{
			return m_window;
		}

		IRendererAPI& Gfx() const override
		{
			return *m_rendererAPI;
		}

		IUiRenderContext& UiContext() const override
		{
			return *m_uiContext;
		}

		float GetTime() const override;
		void SetEventCallback(const EventCallbackFn& callback) override;
		void Update() override;
		bool ShouldClose() const override;

	private:
		static void WindowSizeCallBack(GLFWwindow* window, int width, int height);
		static void WindowCloseCallBack(GLFWwindow* window);
		static void ErrorCallback(int error, const char* description);

	private:
		WindowSpecification m_windowSpec;
		GLFWwindow* m_window = nullptr;
		EventCallbackFn m_eventCallback;
		Scope<IGraphicsContext> m_context;
		Scope<IRendererAPI> m_rendererAPI;
		Scope<IUiRenderContext> m_uiContext;
	};
}