module ZephyrEditor.ViewportPanel;

import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Renderer.RHI.Interfaces.Device;

import ZephyrEditor.SceneSetup;

#ifdef ZEPHYR_RENDERER_OPENGL
import Zephyr.Renderer.OpenGL.GlTexture;
#endif // ZEPHYR_RENDERER_OPENGL

using namespace Zephyr;

namespace ZephyrEditor
{
	static bool ModeButton(const char* label, bool selected)
	{
		// Simple "toggle" look: selected button is darker.
		if (selected)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
		}

		const bool pressed = ImGui::Button(label);

		if (selected)
			ImGui::PopStyleColor(3);

		return pressed;
	}


	ViewportPanel::ViewportPanel(std::string_view title, World& world)
		:m_Title(title), m_World(world), m_SceneRenderer(world)
	{
		auto colorFormats = std::to_array<RHI::TextureFormat>({ RHI::TextureFormat::RGBA8 });

		RHI::FrameBufferDesc desc
		{
			.Size = {720, 1080},
			.ColorFormats = colorFormats,
			.DepthFormat = { RHI::TextureFormat::DEPTH24STENCIL8 }
		};

		m_Framebuffer = RHI::Device::CreateFrameBuffer(std::move(desc));
		m_CameraEntity = ZephyrEditor::SceneSetup::CreateEditorCamera(world, 16.0f / 9.f);
	}

	void ViewportPanel::OnUpdate(float deltaTime)
	{
		if (m_ResizeRequested)
		{
			m_Framebuffer->Resize(m_newSize);
			m_ResizeRequested = false;

			auto& component = m_World.GetComponent<CameraComponent>(m_CameraEntity);
			component.AspectRatio = static_cast<float>(m_newSize.Width) / static_cast<float>(m_newSize.Height);
		}
	}

	void ViewportPanel::RenderViewPort()
	{
		m_SceneRenderer.BeginFrame();
		m_SceneRenderer.RenderWorld(m_CameraEntity);

		m_SceneRenderer.Execute(m_Framebuffer, m_RenderMode);
	}

	void ViewportPanel::OnDisplay()
	{
		// --- Toolbar row ---
		{
			ImGui::PushID("ViewportToolbar");

			// Keep the toolbar compact
			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Mode:");
			ImGui::SameLine();

			// Shaded
			if (ModeButton("Shaded", m_RenderMode == ViewportRenderMode::Shaded))
				m_RenderMode = ViewportRenderMode::Shaded;

			ImGui::SameLine();

			// Wireframe
			if (ModeButton("Wireframe", m_RenderMode == ViewportRenderMode::Wireframe))
				m_RenderMode = ViewportRenderMode::Wireframe;

			ImGui::PopID();
		}

		ImGui::Separator();

		auto fboSize = m_Framebuffer->GetSize();
		const ImVec2 avail = ImGui::GetContentRegionAvail();

		const ImVec2 scale = ImGui::GetIO().DisplayFramebufferScale;
		const uint32_t desiredW = std::max(1u, (uint32_t)std::lround(avail.x * scale.x));
		const uint32_t desiredH = std::max(1u, (uint32_t)std::lround(avail.y * scale.y));

		// Queue resize
		if (desiredW != fboSize.Width || desiredH != fboSize.Height)
		{
			m_newSize = { desiredW, desiredH };
			m_ResizeRequested = true;
		}

		const auto& texture = m_Framebuffer->GetColorAttachment(0);

#ifdef ZEPHYR_RENDERER_OPENGL

		const RHI::OpenGL::GlTexture& glTexture = static_cast<const RHI::OpenGL::GlTexture&>(texture);
		const ImTextureID texID = (ImTextureID)(intptr_t)glTexture.GetId();
		// Flip V for GL (0,0 is bottom-left): use UVs (0,1) to (1,0)
		ImGui::Image(
			texID,
			ImVec2((float)fboSize.Width, (float)fboSize.Height),
			ImVec2(0, 1), ImVec2(1, 0));

#endif // ZEPHYR_RENDERER_OPENGL
	}

}