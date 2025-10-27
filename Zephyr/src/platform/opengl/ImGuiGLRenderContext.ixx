module;

#include <GLFW/glfw3.h>
#include <imgui.h>

export module zephyr.opengl.ImGuiGLRenderContext;

export import zephyr.renderer.IUiRenderContext;

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