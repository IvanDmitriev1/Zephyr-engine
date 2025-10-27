module;

#include <imgui.h>
#include <spdlog/spdlog.h>

export module zephyreditor;

import zephyr.app;
import zephyreditor.AppLayer;
import zephyreditor.EditorLayer;

class ZephyrEditor final : public zephyr::Application
{
public:
	ZephyrEditor(const zephyr::WindowSpecification& spec) : Application(spec)
	{
		auto& window = GetWindow();
		auto& gfx = window.Gfx();

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/Inter-VariableFont.ttf", 18);

		GetLayerStack().PushOverlay<EditorLayer>(gfx);
	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	zephyr::WindowSpecification spec{};
	spec.Title = "Zephyr Editor";

	spdlog::log(spdlog::level::info, "Creating Zephyr Editor application");

	return new ZephyrEditor(spec);
}
