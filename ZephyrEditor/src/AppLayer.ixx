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
};