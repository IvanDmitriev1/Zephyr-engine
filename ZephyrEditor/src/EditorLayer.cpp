module;

#include <imgui.h>
#include <imgui_internal.h>

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
    DrawDockSpace();
    DrawViewPort();
    DrawConsole();

    if (m_ShowDemoWindow)
    {
        ImGui::ShowDemoWindow(nullptr);
    }
}

void EditorLayer::DrawDockSpace()
{
    static bool dockspaceOpen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    
    ImGui::Begin("Zephyr editor", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    ImGuiID dockspace_id = ImGui::GetID("Editor dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    static bool first_time = true;
    if (first_time)
    {
        first_time = false;
        BuildDefaultDockLayout(dockspace_id);
    }

    if (ImGui::BeginMenuBar())
    {
        DrawDockSpaceMenuBar();
        ImGui::EndMenuBar();
    }

    ImGui::End(); //Zephyr editor
}

void EditorLayer::DrawDockSpaceMenuBar()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New", "Ctrl+N"))
        {
        }
        if (ImGui::MenuItem("Open", "Ctrl+O"))
        {
        }
        if (ImGui::MenuItem("Save", "Ctrl+S"))
        {
        }
        if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
        {
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit"))
        {
            
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "Ctrl+Z"))
        {
        }
        if (ImGui::MenuItem("Redo", "Ctrl+Y"))
        {
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
        ImGui::MenuItem("Viewport", nullptr, &m_ShowViewport);
        ImGui::MenuItem("Console", nullptr, &m_ShowConsole);
        ImGui::MenuItem("Demo window", nullptr, &m_ShowDemoWindow);
        ImGui::EndMenu();
    }
}

void EditorLayer::BuildDefaultDockLayout(ImGuiID dockspace_id)
{
    // Clear out existing layout
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

    // Split the dockspace into multiple zones
    ImGuiID dock_main_id = dockspace_id;
    ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
    ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
    ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.3f, nullptr, &dock_main_id);

    // Dock windows into the created spaces
    ImGui::DockBuilderDockWindow("Hierarchy", dock_id_left);
    ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
    ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
    ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
    ImGui::DockBuilderDockWindow("Console", dock_id_bottom);

    ImGui::DockBuilderFinish(dockspace_id);
}

void EditorLayer::DrawViewPort()
{
    if (!m_ShowViewport)
        return;

    zephyr::IFrameBuffer& fbo = m_rendererApi.GetFrameBuffer();

    ImGui::Begin("Viewport", nullptr,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    const ImVec2 avail = ImGui::GetContentRegionAvail();

    const ImVec2 scale = ImGui::GetIO().DisplayFramebufferScale;
    const uint32_t desiredW = std::max(1u, (uint32_t)std::lround(avail.x * scale.x));
    const uint32_t desiredH = std::max(1u, (uint32_t)std::lround(avail.y * scale.y));

    // Queue resize
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

void EditorLayer::DrawConsole()
{
    if (!m_ShowConsole)
        return;

    ImGui::Begin("Console", nullptr);

    // Example console messages
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "[INFO] Engine initialized");
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "[WARNING] Missing texture");
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[ERROR] Failed to load shader");
    ImGui::Text("[LOG] Frame rendered in 16.7ms");

    ImGui::End();
}
