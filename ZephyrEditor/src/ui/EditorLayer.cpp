module;

#include <imgui_internal.h>

module zephyreditor.ui.EditorLayer;

import zephyr.renderer.Renderer;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Color;
};



EditorLayer::EditorLayer(zephyr::IRendererAPI& rendererApi, zephyr::LogBuffer& logBuffer) : Layer("EditorLayer")
    ,m_rendererApi(rendererApi), m_DebugLog(logBuffer)
{
    
}

void EditorLayer::OnAttach()
{
    zephyr::ShaderCreateInfo shaderInfo;
    shaderInfo.Name = "TriangleShader";
    shaderInfo.Stages =
    {
        zephyr::ShaderStageDesc{ zephyr::ShaderStage::Vertex,   "assets/shaders/Triangle.vert.glsl" },
        zephyr::ShaderStageDesc{ zephyr::ShaderStage::Fragment, "assets/shaders/Triangle.frag.glsl" }
    };

    m_Shader = zephyr::IShader::Create(shaderInfo);


    Vertex vertices[3] = {
        { {  0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
    };

    std::uint32_t indices[3] = { 0, 1, 2 };

    zephyr::BufferCreateInfo vbInfo;
    vbInfo.Type = zephyr::BufferType::Vertex;
    vbInfo.Usage = zephyr::BufferUsage::StaticDraw;
    vbInfo.Size = sizeof(vertices);
    vbInfo.Data = vertices;

    zephyr::BufferCreateInfo ibInfo;
    ibInfo.Type = zephyr::BufferType::Index;
    ibInfo.Usage = zephyr::BufferUsage::StaticDraw;
    ibInfo.Size = sizeof(indices);
    ibInfo.Data = indices;

    auto vertexBuffer = zephyr::IBuffer::Create(vbInfo);
    auto indexBuffer = zephyr::IBuffer::Create(ibInfo);

    zephyr::VertexLayout layout =
    {
        { "a_Position", zephyr::ShaderDataType::Float3 },
        { "a_Color",    zephyr::ShaderDataType::Float3 }
    };

    zephyr::VertexArrayCreateInfo vaoInfo(
        vertexBuffer,
        std::move(layout),
        indexBuffer,
        zephyr::IndexType::UInt32);

    m_VertexArray = zephyr::IVertexArray::Create(vaoInfo);
    m_IndexCount = m_VertexArray->GetIndexCount();
}

void EditorLayer::OnUpdate(float ts)
{
    if (m_ResizeRequested)
    {
        zephyr::Renderer::GetFrameBuffer().Resize(m_PendingW, m_PendingH);
        m_ResizeRequested = false;
    }
}

void EditorLayer::OnUi()
{
    DrawDockSpace();
    DrawViewPort();

    m_DebugLog.Draw();

    //DrawConsole();

    if (m_ShowDemoWindow)
    {
        ImGui::ShowDemoWindow(nullptr);
    }
}

void EditorLayer::OnRender()
{
    zephyr::DrawCommand cmd;
    cmd.Shader = m_Shader;
    cmd.VertexArray = m_VertexArray;
    cmd.Topology = zephyr::PrimitiveTopology::Triangles;
    cmd.Transform = glm::mat4(1.0f);

    zephyr::Renderer::Submit(cmd);
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

void EditorLayer::BuildDefaultDockLayout(ImGuiID dock_main_id)
{
    // Clear out existing layout
    ImGui::DockBuilderRemoveNode(dock_main_id);
    ImGui::DockBuilderAddNode(dock_main_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dock_main_id, ImGui::GetMainViewport()->Size);

    ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
    ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
    ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.3f, nullptr, &dock_main_id);

    ImGui::DockBuilderDockWindow("Hierarchy", dock_id_left);
    ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
    ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
    ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
    ImGui::DockBuilderDockWindow("Debug log", dock_id_bottom);

    ImGui::DockBuilderFinish(dock_main_id);
}

void EditorLayer::DrawViewPort()
{
    if (!m_ShowViewport)
        return;

    zephyr::IFrameBuffer& fbo = zephyr::Renderer::GetFrameBuffer();

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

