module zephyr.core.LayerStack;

namespace Zephyr
{
	LayerStack::~LayerStack()
	{
		for (const auto& layer : m_Layers)
		{
			layer->OnDetach();
		}

		m_Layers.clear();
		m_Pending.clear();
		m_LayerInsertIndex = 0;
	}

	void LayerStack::PopByName(std::string_view name)
	{
		PendingOperation op
		{
			.Type = OperationType::PopByName,
			.NameToPop = std::string(name)
		};

		m_Pending.emplace_back(std::move(op));
	}

	void LayerStack::FlushPendingOps()
	{
		for (auto& op : m_Pending)
		{
			switch (op.Type)
			{
			case OperationType::PushLayer:
			{
				auto it = m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex);
				it = m_Layers.insert(it, std::move(op.Layer));
				++m_LayerInsertIndex;
				(*it)->OnAttach();
				break;
			}
			case OperationType::PushOverlay:
			{
				m_Layers.emplace_back(std::move(op.Layer));
				m_Layers.back()->OnAttach();
				break;
			}
			case OperationType::PopByName:
			{
				auto it = std::ranges::find_if(m_Layers, [&](const Scope<Layer>& p)
				{
					return p && p->GetName() == op.NameToPop;
				});


				if (it != m_Layers.end())
				{
					const std::size_t idx = static_cast<std::size_t>(std::distance(m_Layers.begin(), it));

					(*it)->OnDetach();
					m_Layers.erase(it);

					if (idx < m_LayerInsertIndex)
					{
						--m_LayerInsertIndex;
					}
				}

				break;
			}
			}

			m_Pending.clear();
		}
	}

	void LayerStack::OnEvent(IEvent& event)
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
			layer->OnUiRender();
		}
	}
}