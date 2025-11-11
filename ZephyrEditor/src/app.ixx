export module zephyreditor;

import zephyr.app;
import zephyreditor.AppLayer;
import zephyreditor.ui.EditorLayer;

import <imgui.h>;

class ZephyrEditor final : public zephyr::Application
{
public:
	ZephyrEditor(const zephyr::WindowSpecification& spec) : Application(spec)
	{
		zephyr::applog::Info("Creating Zephyr Editor application");

		auto& window = GetWindow();
		auto& gfx = window.Gfx();

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/Inter-VariableFont.ttf", 18);

		GetLayerStack().PushOverlay<EditorLayer>(gfx, GetLogBuffer());
	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	zephyr::WindowSpecification spec{};
	spec.Title = "Zephyr Editor";

	return new ZephyrEditor(spec);
}
