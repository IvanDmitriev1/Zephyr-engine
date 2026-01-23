export module ZephyrEditor.App;

import Zephyr.App;
import Zephyr.Renderer.Core.IFrameBuffer;
import Zephyr.Renderer.Core.IRenderPassEncoder;
import Zephyr.Scene.World;
import Zephyr.Renderer.SceneRenderer;
import Zephyr.Scene;

import ZephyrEditor.UiPanelHost;
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
	void SetupMenuBar();

private:
	inline static EditorApp* s_Instance = nullptr;

	Ref<RHI::IFrameBuffer> m_Framebuffer;
	ZephyrEditor::UiPanelHost m_PanelHost{};
	Scene m_Scene{};

	bool m_ShowConsole = true;
	bool m_ShowDemoWindow = false;
};

export Zephyr::Application* Zephyr::CreateApplication()
{
	Zephyr::WindowSpecification spec{};
	spec.Width = 1920;
	spec.Height = 1080;
	spec.Title = "Zephyr Editor";

	return new EditorApp(spec);
}
