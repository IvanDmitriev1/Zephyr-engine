export module ZephyrEditor.App;

import Zephyr.App;
import Zephyr.Renderer.Core.IFrameBuffer;
import Zephyr.Renderer.Core.IRenderPassEncoder;
import Zephyr.Scene.World;

import <imgui.h>;

using namespace Zephyr;

class EditorApp final : public Zephyr::Application
{
public:
	EditorApp(const Zephyr::WindowSpecification& spec);

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
	Ref<RHI::IFrameBuffer> m_Framebuffer;
	Ref<RHI::IRenderPassEncoder> m_CommandList;
	World m_Scene;

	bool m_ResizeRequested = false;
	uint32_t m_PendingW = 0;
	uint32_t m_PendingH = 0;
	bool m_ViewportFocused = false;
	bool m_ViewportHovered = false;
	bool m_ShowViewport = true;
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
