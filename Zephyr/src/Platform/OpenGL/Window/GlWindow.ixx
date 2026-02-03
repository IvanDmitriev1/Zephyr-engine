export module Zephyr.Renderer.OpenGL.Window;

import Zephyr.Renderer.Platform.IWindow;

import <GLFW/glfw3.h>;

export namespace Zephyr::OpenGL
{
	class GlWindow : public IWindow
	{
	public:
		explicit GlWindow(const WindowSpecification& spec);
		~GlWindow() override;

	public:
		Scope<IUiRenderContext> CreateUiContext() const noexcept override;
		void* GetNativeHandle() const noexcept override { return m_window; }
		Extent2D GetSize() const noexcept override { return m_size; }
		float GetTime() const noexcept override;

		void SetEventCallback(const EventCallbackFn& callback) override;
		void PollEvents() override;
		bool ShouldClose() const override;
		void SwapBuffers() override;

	private:
		static void ErrorCallback(int error, const char* description);
		static void WindowCloseCallBack(GLFWwindow* window);
		static void FramebufferSizeCallback(GLFWwindow* window, int w, int h);
	private:
		GLFWwindow* m_window = nullptr;
		EventCallbackFn m_eventCallback;
		Extent2D m_size{};
		bool m_vsync{};
	};
}