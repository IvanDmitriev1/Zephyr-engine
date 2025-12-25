module zephyr.core.LayerStack;

namespace Zephyr
{
	LayerStack::~LayerStack()
	{
		Clear();
	}

	void LayerStack::PopLayer(Layer& layer)
	{

	}

	void LayerStack::Clear()
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnDetach();
		}

		m_Layers.clear();
		m_LayerInsertIndex = 0;
	}

	void LayerStack::OnEvent(const IEvent& event)
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnEvent(event);
		}
	}

	void LayerStack::OnUpdate(float ts)
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnUpdate(ts);
		}
	}

	void LayerStack::OnRender()
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnRender();
		}
	}

	void LayerStack::OnUiRender()
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnUi();
		}
	}
}