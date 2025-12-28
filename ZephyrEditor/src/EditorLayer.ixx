export module ZephyrEditor.EditorLayer;

export import zephyr.core.Layer;

import <imgui.h>;

export class EditorLayer : public Zephyr::Layer
{
public:
	EditorLayer() : Layer("Editor layer") {}

	void OnAttach() override;
	void OnUpdate(float ts) override;
	void OnUiRender() override;

private:
	void DrawDockSpace();
	void DrawDockSpaceMenuBar();
	void BuildDefaultDockLayout(ImGuiID dock_main_id);

	void DrawViewPort();


private:
	bool m_ResizeRequested = false;
	uint32_t m_PendingW = 0;
	uint32_t m_PendingH = 0;
	bool m_ViewportFocused = false;
	bool m_ViewportHovered = false;
	bool m_ShowViewport = true;
	bool m_ShowConsole = true;
	bool m_ShowDemoWindow = false;
};