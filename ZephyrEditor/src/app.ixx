export module zephyreditor;

import zephyr.app;
import zephyreditor.AppLayer;

import <imgui.h>;

class ZephyrEditor final : public Zephyr::Application
{
public:
	ZephyrEditor(const Zephyr::WindowSpecification& spec) : Application(spec)
	{
		Zephyr::applog::Info("Creating Zephyr Editor application");

		//ImGuiIO& io = ImGui::GetIO();
		//io.Fonts->AddFontFromFileTTF("assets/fonts/Inter-VariableFont.ttf", 18);

		GetLayerStack().PushLayer<AppLayer>();
	}
};

export Zephyr::Application* Zephyr::CreateApplication()
{
	Zephyr::WindowSpecification spec{};
	spec.Width = 1920;
	spec.Height = 1080;
	spec.Title = "Zephyr Editor";

	return new ZephyrEditor(spec);
}
