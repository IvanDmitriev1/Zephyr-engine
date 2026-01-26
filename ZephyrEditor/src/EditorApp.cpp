module;

#include <imgui_internal.h>

module ZephyrEditor.App;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.Renderer;

import Zephyr.Scene.Systems.TransformSystem;
import Zephyr.Scene.Systems.RenderingSystem;
import Zephyr.Scene.Systems.CameraSystem;

import ZephyrEditor.SceneSetup;
import ZephyrEditor.ViewportPanel;
import ZephyrEditor.SceneHierarchyPanel;
import ZephyrEditor.InspectorPanel;
import ZephyrEditor.DemoSystem;

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

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/Inter-VariableFont.ttf", 18);
}

EditorApp::~EditorApp()
{
	s_Instance = nullptr;
}

void EditorApp::OnInit()
{
	m_Scene.AddSystem<ZephyrEditor::DemoSystem>();
	m_Scene.AddSystem<TransformSystem>();
	m_Scene.AddSystem<CameraSystem>();
	m_Scene.AddSystem<RenderingSystem>();

	auto& world = m_Scene.GetWorld();
	ZephyrEditor::SceneSetup::CreateTestScene(world);

	m_PanelHost.Add<ZephyrEditor::ViewportPanel>("Viewport", world);
	m_PanelHost.Add<ZephyrEditor::ViewportPanel>("Viewport2", world);
	auto& hierarchy = m_PanelHost.Add<ZephyrEditor::SceneHierarchyPanel>(world);
	auto& inspector = m_PanelHost.Add<ZephyrEditor::InspectorPanel>(world);

	hierarchy.m_OnSelectionChanged = [&](Entity entity)
	{
		inspector.SetSelectedEntity(entity);
	};

	SetupMenuBar();
}

void EditorApp::OnUpdate(float dt)
{
	m_PanelHost.OnUpdate(dt);
	m_Scene.OnUpdate(dt);
}

void EditorApp::OnRender()
{
	auto& panel = m_PanelHost.Get("Viewport");
	auto& viewPort = static_cast<ZephyrEditor::ViewportPanel&>(panel);

	auto& panel2 = m_PanelHost.Get("Viewport2");
	auto& viewPort2 = static_cast<ZephyrEditor::ViewportPanel&>(panel2);

	viewPort.RenderViewPort();
	viewPort2.RenderViewPort();
}

void EditorApp::OnUiRender()
{
	m_PanelHost.OnImGuiRender();
}

void EditorApp::OnEvent(Zephyr::IEvent& e)
{
	
}

void EditorApp::SetupMenuBar()
{
	auto& menuBar = m_PanelHost.GetMenuBar();

	menuBar.AddMenu("File")
		.AddItem("New Scene", [this]()
	{
		// TODO: New scene
	}, "Ctrl+N")
		.AddItem("Open Scene", [this]()
	{
		// TODO: Open scene dialog
	}, "Ctrl+O")
		.AddItem("Save Scene", [this]()
	{
		// TODO: Save scene
	}, "Ctrl+S")
		.AddSeparator()
		.AddItem("Exit", [this]()
	{
		// TODO: Trigger shutdown
	}, "Alt+F4");


	menuBar.AddMenu("View")
		.AddItem("Reset Layout", [this]()
	{
		
	})
		.AddSeparator()
		.AddItem("Scene Hierarchy", [this]()
	{
		
	})
		.AddItem("Inspector", [this]()
	{
		
	})
		.AddItem("Viewport", [this]()
	{
		
	})
		.AddItem("Stats", [this]()
	{
		
	});

}
