export module zephyreditor;

import zephyr.app;

class ZephyrEditor final : public zephyr::Application
{
public:
	ZephyrEditor(const zephyr::WindowSpecification& spec) : Application(spec)
	{

	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	zephyr::WindowSpecification spec{};
	spec.Title = "Zephyr Editor";

	return new ZephyrEditor(spec);
}
