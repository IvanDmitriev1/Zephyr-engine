export module ZephyrEditor.App;

import ZephyrEditor.MainLayer;

import Zephyr.App;
import Zephyr.Renderer.Core.IFrameBuffer;
import Zephyr.Renderer.Core.IRenderPassEncoder;
import Zephyr.Scene.World;
import Zephyr.Renderer.SceneRenderer;

import ZephyrEditor.Ui.CreateProjectDialog;

import ZephyrEditor.ProjectManager;

import <imgui.h>;

using namespace Zephyr;

class EditorApp final : public Zephyr::Application
{
public:
	static EditorApp& Instance();

	EditorApp(const Zephyr::WindowSpecification& spec);
	~EditorApp() override;

	void OnInit() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnUiRender() override;
	void OnEvent(Zephyr::IEvent& e) override;

private:
	void DrawDockSpace();
	void DrawDockSpaceMenuBar();
	void BuildDefaultDockLayout(ImGuiID dock_main_id);

	void DrawViewPort();

private:
	void OnProjectCreated(const ZephyrEditor::ProjectFile& file);

private:
	inline static EditorApp* s_Instance = nullptr;

	Ref<RHI::IFrameBuffer> m_Framebuffer;
	Scope<MainLayer> m_MainLayer;
	World m_Scene;
	CameraUniformData m_Camera;

	ZephyrEditor::ProjectManager m_ProjectManager{};
	Scope<ZephyrEditor::CreateProjectDialog> m_CreateProjectDialog;

	bool m_ResizeRequested = false;
	uint32_t m_PendingW = 0;
	uint32_t m_PendingH = 0;
	bool m_ViewportFocused = false;
	bool m_ViewportHovered = false;
	bool m_ShowViewport = true;
	bool m_ShowConsole = true;
	bool m_ShowDemoWindow = false;
};

struct Person
{
	std::string first_name;
	std::string last_name = "Simpson";
	std::string town = "Springfield";
	unsigned int age;
	std::vector<Person> children;
};

export Zephyr::Application* Zephyr::CreateApplication()
{
	Zephyr::WindowSpecification spec{};
	spec.Width = 1920;
	spec.Height = 1080;
	spec.Title = "Zephyr Editor";

	return new EditorApp(spec);
}
