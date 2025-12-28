export module zephyreditor;

import zephyr.app;
import ZephyrEditor.EditorLayer;
import ZephyrEditor.AppLayer;

import <imgui.h>;

class ZephyrEditor final : public Zephyr::Application
{
public:
	ZephyrEditor(const Zephyr::WindowSpecification& spec) : Application(spec)
	{
		Zephyr::applog::Info("Creating Zephyr Editor application");

		GetLayerStack().PushLayer<AppLayer>();
		GetLayerStack().PushOverlay<EditorLayer>();
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
