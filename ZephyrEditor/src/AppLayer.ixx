module;
export module zephyreditor.AppLayer;

export import zephyr.core.Layer;

export class AppLayer : public zephyr::Layer
{
public:
	AppLayer() : Layer("test1")
	{

	}

	~AppLayer() override = default;

	void OnAttach() override
	{
	}

	void OnDetach() override
	{
	}

	void OnEvent(const zephyr::IEvent& event) override
	{
	}

	void OnUpdate(float ts) override
	{
	}

	void OnRender() override
	{
		
	}
};