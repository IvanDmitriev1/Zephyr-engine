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

		GetLayerStack().PushOverlay<EditorLayer>(gfx);
	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	zephyr::WindowSpecification spec{};
	spec.Title = "Zephyr Editor";

	return new ZephyrEditor(spec);
}
