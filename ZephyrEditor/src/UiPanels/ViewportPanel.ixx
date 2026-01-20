export module ZephyrEditor.ViewportPanel;

export import ZephyrEditor.UiPanel;

import Zephyr.Renderer.Core.IFrameBuffer;
import Zephyr.Scene.World;

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
		inline std::string_view GetId() const noexcept override { return GetTitle(); }
		inline ImGuiWindowFlags GetWindowFlags() const noexcept override
		{
			return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		}

		void OnImGuiRender() override;

	private:
		std::string m_Title;
		World& m_World;

		Ref<RHI::IFrameBuffer> m_Framebuffer;
		Entity m_CameraEntity;
		bool m_ResizeRequested = false;
		Extent2D m_newSize;
	};
}