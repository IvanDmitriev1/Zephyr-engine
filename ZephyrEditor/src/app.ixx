export module zephyreditor;

import zephyr.app;


class ZephyrEditor final : public zephyr::Application
{
public:
	ZephyrEditor() : Application("Zephyr Editor")
	{

	}
};

export zephyr::Application* zephyr::CreateApplication()
{
	return new ZephyrEditor();
}
