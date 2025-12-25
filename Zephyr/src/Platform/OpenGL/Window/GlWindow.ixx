export module Zephyr.Renderer.OpenGL.Window;

export import Zephyr.Renderer.Window;
import <GLFW/glfw3.h>;

export namespace Zephyr::OpenGL
{
	class GlWindow : public IWindow
	{
	public:
		explicit GlWindow(const WindowSpecification& spec);
		~GlWindow() override;

	public:
		void* GetNativeHandle() const noexcept override
		{
			return m_window;
		}

		glm::ivec2 GetSize() const noexcept override
		{
			return m_size;
		}

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
		glm::ivec2 m_size{};
		bool m_vsync{};
	};
}