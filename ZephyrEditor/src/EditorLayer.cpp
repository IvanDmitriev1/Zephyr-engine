module;

#include <imgui.h>

module zephyreditor.EditorLayer;

EditorLayer::EditorLayer(zephyr::IRendererAPI& rendererApi) : Layer("EditorLayer")
    ,m_rendererApi(rendererApi)
{
}

void EditorLayer::OnUpdate(float ts)
{
    if (m_ResizeRequested)
    {
        m_rendererApi.GetFrameBuffer().Resize(m_PendingW, m_PendingH);
        m_ResizeRequested = false;
    }

}

void EditorLayer::OnUi()
{
    DrawMainDockspace();
    DrawViewPort();
}

void EditorLayer::DrawMainDockspace()
{
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(vp->Pos);
    ImGui::SetNextWindowSize(vp->Size);
    ImGui::SetNextWindowViewport(vp->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_MenuBar;

    ImGui::Begin("DockSpace", nullptr, flags);
    ImGui::PopStyleVar(2);

    ImGuiID dockspace_id = ImGui::GetID("Zephyr/MainDockSpace");
    ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), dockFlags);

    ImGui::End();
}

void EditorLayer::DrawViewPort()
{
    zephyr::IFrameBuffer& fbo = m_rendererApi.GetFrameBuffer();

    ImGui::Begin("Viewport", nullptr,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    const ImVec2 avail = ImGui::GetContentRegionAvail();

    const ImVec2 scale = ImGui::GetIO().DisplayFramebufferScale;
    const uint32_t desiredW = std::max(1u, (uint32_t)std::lround(avail.x * scale.x));
    const uint32_t desiredH = std::max(1u, (uint32_t)std::lround(avail.y * scale.y));

    // Queue resize only if size actually changed (avoid thrashing)
    if (desiredW != (uint32_t)fbo.Width() || desiredH != (uint32_t)fbo.Height())
    {
        m_PendingW = desiredW;
        m_PendingH = desiredH;
        m_ResizeRequested = true;
    }

    // Show the color attachment as an image
    const ImTextureID texID = (ImTextureID)(intptr_t)fbo.GetTexture(0);
    // Flip V for GL (0,0 is bottom-left): use UVs (0,1) to (1,0)
    ImGui::Image(
        texID,
        ImVec2((float)fbo.Width(), (float) fbo.Height()),
        ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}
