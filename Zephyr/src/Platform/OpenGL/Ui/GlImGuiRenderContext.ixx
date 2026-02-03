export module Zephyr.Renderer.OpenGL.GlImGuiRenderContext;

export import Zephyr.Renderer.Platform.IUiRenderContext;

import <GLFW/glfw3.h>;
import <imgui.h>;

export namespace Zephyr::OpenGL
{
	class GlImGuiRenderContext : public IUiRenderContext
	{
	public:
		GlImGuiRenderContext(GLFWwindow* window);
		~GlImGuiRenderContext() override;

		void BeginFrame() override;
		void EndFrame() override;

	private:
		GLFWwindow* m_Window = nullptr;
		ImGuiContext* m_Ctx = nullptr;
	};
}