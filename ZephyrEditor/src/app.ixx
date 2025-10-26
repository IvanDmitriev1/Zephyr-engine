export module zephyreditor;

import zephyr.app;
import zephyreditor.AppLayer;

class ZephyrEditor final : public zephyr::Application
{
public:
	ZephyrEditor(const zephyr::WindowSpecification& spec) : Application(spec)
	{
		//auto& window = GetWindow();

		GetLayerStack().PushOverlay<AppLayer>();
	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	zephyr::WindowSpecification spec{};
	spec.Title = "Zephyr Editor";

	return new ZephyrEditor(spec);
}
