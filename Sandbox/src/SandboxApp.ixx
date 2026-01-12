export module Sandbox.App;

import Zephyr.App;

using namespace Zephyr;

class SandboxApp final : public Zephyr::Application
{
public:
	SandboxApp(const Zephyr::WindowSpecification& spec)
		: Zephyr::Application(spec)
	{
	}

	void OnInit() override { }
	void OnUpdate(float) override { }
	void OnRender() override { }
	void OnUiRender() override { }
	void OnEvent(Zephyr::IEvent&) override { }
};

export Zephyr::Application* Zephyr::CreateApplication()
{
	Zephyr::WindowSpecification spec{};
	spec.Width = 1280;
	spec.Height = 720;
	spec.Title = "Zephyr Sandbox";

	return new SandboxApp(spec);
}
