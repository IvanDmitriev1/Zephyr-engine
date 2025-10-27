module;

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

module zephyr.opengl.ImGuiGLRenderContext;

namespace zephyr
{
	ImGuiGLRenderContext::ImGuiGLRenderContext(GLFWwindow* window)
		: m_Window(window)
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

	ImGuiGLRenderContext::~ImGuiGLRenderContext()
	{
		ImGui::SetCurrentContext(m_Ctx);
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(m_Ctx);
	}

	void ImGuiGLRenderContext::BeginFrame()
	{
		ImGui::SetCurrentContext(m_Ctx);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiGLRenderContext::EndFrame()
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

	void ImGuiGLRenderContext::OnEvent(const IEvent& e)
	{
	}
}