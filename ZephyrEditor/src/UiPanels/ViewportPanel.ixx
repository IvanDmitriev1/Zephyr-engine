export module ZephyrEditor.ViewportPanel;

export import ZephyrEditor.UiPanel;

import Zephyr.Renderer.RHI.IFrameBuffer;
import Zephyr.Scene.World;
import Zephyr.Renderer.Types.RendererTypes;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class ViewportPanel final : public UiPanel
	{
	public:
		ViewportPanel(std::string_view title, World& world);
		~ViewportPanel() override = default;

		void OnUpdate(float deltaTime) override;

		inline std::string_view GetTitle() const noexcept { return m_Title; }
		inline ImGuiWindowFlags GetWindowFlags() const noexcept override
		{
			return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse;
		}

		void RenderViewPort();

		void OnDisplay() override;

	private:
		std::string m_Title;
		World& m_World;

		Ref<RHI::IFrameBuffer> m_Framebuffer;
		Entity m_CameraEntity;
		CameraUniformData m_CameraData{};

		bool m_ResizeRequested = false;
		Extent2D m_newSize;
	};
}