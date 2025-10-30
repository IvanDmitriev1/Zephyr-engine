module;

export module zephyr.opengl.ImGuiGLRenderContext;

export import zephyr.renderer.IUiRenderContext;

import <GLFW/glfw3.h>;
import <imgui.h>;

export namespace zephyr
{
	class ImGuiGLRenderContext : public IUiRenderContext
	{
	public:
		ImGuiGLRenderContext(GLFWwindow* window);
		~ImGuiGLRenderContext() override;

	public:
		void OnEvent(const IEvent& e) override;
		void BeginFrame() override;
		void EndFrame() override;

	private:
		GLFWwindow* m_Window = nullptr;
		ImGuiContext* m_Ctx = nullptr;
	};
}