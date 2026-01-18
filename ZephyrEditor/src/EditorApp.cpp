module;

#include <imgui_internal.h>

module ZephyrEditor.App;

import Zephyr.Renderer.Core.Device;
import Zephyr.Renderer.Renderer;

import Zephyr.Scene.Systems.TransformSystem;
import Zephyr.Scene.Systems.RenderingSystem;
import Zephyr.Scene.Systems.CameraSystem;

import ZephyrEditor.SceneSetup;
import Zephyr.Scene.Components.CameraComponent;

using namespace Zephyr;

EditorApp& EditorApp::Instance()
{
	Assert(s_Instance, "EditorApp::Instance called before construction");
	return *s_Instance;
}

EditorApp::EditorApp(const Zephyr::WindowSpecification& spec)
	:Application(spec)
{
	s_Instance = this;
	Zephyr::applog::Info("Creating Zephyr Editor application");

	RHI::FrameBufferDesc desc
	{
		.Size = {spec.Width, spec.Height},
		.ColorAttachments = { {RHI::TextureFormat::RGBA8 }},
		.DepthStencilAttachment = { { RHI::TextureFormat::DEPTH24STENCIL8 }}
	};

	m_Framebuffer = RHI::Device::CreateFrameBuffer(std::move(desc));
	
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/Inter-VariableFont.ttf", 18);
}

EditorApp::~EditorApp()
{
	s_Instance = nullptr;
}

void EditorApp::OnInit()
{
	m_Scene.AddSystem<TransformSystem>();
	m_Scene.AddSystem<CameraSystem>();
	m_Scene.AddSystem<RenderingSystem>();

	auto& world = m_Scene.GetWorld();
	ZephyrEditor::SceneSetup::CreateTestScene(world);
	m_Camera = ZephyrEditor::SceneSetup::CreateEditorCamera(world, 16.0f / 9.f);

	Renderer::GetRenderGraph().AddPass("MainPass", m_Framebuffer)
		.ClearColor(0.53f, 0.81f, 0.92f, 1.0f)
		.Execute([this](SceneRenderer& renderer)
	{
		
	});
}

void EditorApp::OnUpdate(float dt)
{
	if (m_ResizeRequested)
	{
		m_Framebuffer->Resize({ m_PendingW, m_PendingH });
		m_ResizeRequested = false;

		auto& component = m_Scene.GetWorld().GetComponent<CameraComponent>(m_Camera);
		component.AspectRatio = static_cast<float>(m_PendingW) / static_cast<float>(m_PendingH);
	}

	m_Scene.OnUpdate(dt);
}

void EditorApp::OnRender()
{
	Renderer::Render();
}

void EditorApp::OnUiRender()
{
	DrawDockSpace();
	DrawViewPort();

	if (m_ShowDemoWindow)
	{
		ImGui::ShowDemoWindow(nullptr);
	}
}

void EditorApp::OnEvent(Zephyr::IEvent& e)
{
	
}

void EditorApp::DrawDockSpace()
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

void EditorApp::DrawDockSpaceMenuBar()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("File/New Project..."))
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

void EditorApp::BuildDefaultDockLayout(ImGuiID dock_main_id)
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

void EditorApp::DrawViewPort()
{
	if (!m_ShowViewport)
		return;

	auto fboSize = m_Framebuffer->GetDesc().Size;

	ImGui::Begin("Viewport", nullptr,
				 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	const ImVec2 avail = ImGui::GetContentRegionAvail();

	const ImVec2 scale = ImGui::GetIO().DisplayFramebufferScale;
	const uint32_t desiredW = std::max(1u, (uint32_t)std::lround(avail.x * scale.x));
	const uint32_t desiredH = std::max(1u, (uint32_t)std::lround(avail.y * scale.y));

	// Queue resize
	if (desiredW != fboSize.Width || desiredH != fboSize.Height)
	{
		m_PendingW = desiredW;
		m_PendingH = desiredH;
		m_ResizeRequested = true;
	}

	// Show the color attachment as an image
	const auto& texture = m_Framebuffer->GetColorAttachment(0);

	const ImTextureID texID = (ImTextureID)(intptr_t)texture.GetId();
	// Flip V for GL (0,0 is bottom-left): use UVs (0,1) to (1,0)
	ImGui::Image(
		texID,
		ImVec2((float)fboSize.Width, (float)fboSize.Height),
		ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void EditorApp::OnProjectCreated(const ZephyrEditor::ProjectFile& file)
{}
