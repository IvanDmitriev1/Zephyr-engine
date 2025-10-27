module;
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
	void DrawMainDockspace();
	void DrawViewPort();

private:
	zephyr::IRendererAPI& m_rendererApi;
	bool m_ResizeRequested = false;
	uint32_t m_PendingW = 0;
	uint32_t m_PendingH = 0;
};
