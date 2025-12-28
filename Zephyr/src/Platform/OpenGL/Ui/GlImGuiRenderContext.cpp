module;

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

module Zephyr.Renderer.OpenGL.GlImGuiRenderContext;

namespace Zephyr::OpenGL
{
	GlImGuiRenderContext::GlImGuiRenderContext(GLFWwindow* window)
		:m_Window(window)
	{
		IMGUI_CHECKVERSION();
		m_Ctx = ImGui::CreateContext();
		ImGui::SetCurrentContext(m_Ctx);

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigDpiScaleFonts = true;
		io.ConfigDpiScaleViewports = true;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	GlImGuiRenderContext::~GlImGuiRenderContext()
	{
		ImGui::SetCurrentContext(m_Ctx);
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(m_Ctx);
	}

	void GlImGuiRenderContext::BeginFrame()
	{
		ImGui::SetCurrentContext(m_Ctx);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GlImGuiRenderContext::EndFrame()
	{
		ImGui::SetCurrentContext(m_Ctx);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup);
		}
	}
}