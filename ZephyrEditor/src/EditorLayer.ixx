module;

#include <imgui.h>

export module zephyreditor.EditorLayer;

export import zephyr.core.Layer;
export import zephyr.renderer.IRendererAPI;

export class EditorLayer : public zephyr::Layer
{
public:
	EditorLayer(zephyr::IRendererAPI& rendererApi);
	~EditorLayer() = default;

	void OnUpdate(float ts) override;
	void OnUi() override;

private:
	void DrawDockSpace();
	void DrawDockSpaceMenuBar();
	void BuildDefaultDockLayout(ImGuiID dockspace_id);


	void DrawViewPort();
	void DrawConsole();

private:
	zephyr::IRendererAPI& m_rendererApi;
	bool m_ResizeRequested = false;
	uint32_t m_PendingW = 0;
	uint32_t m_PendingH = 0;
	bool m_ViewportFocused = false;
	bool m_ViewportHovered = false;
	bool m_ShowViewport = true;
	bool m_ShowConsole = true;
	bool m_ShowDemoWindow = false;
};
