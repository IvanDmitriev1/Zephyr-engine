module Zephyr.Renderer.RenderQueue;

namespace Zephyr
{
	void RenderQueue::BeginFrame()
	{
		for (auto& queue : m_Queues)
		{
			queue.clear();
		}
	}

	void RenderQueue::Submit(const DrawItem& item)
	{
		m_Queues[std::to_underlying(item.Phase)].push_back(item);
	}

	void RenderQueue::Submit(std::span<const DrawItem> items)
	{
		for (const auto& item : items)
		{
			Submit(item);
		}
	}

	void RenderQueue::SortQueues()
	{
		// Front-to-back (early-Z)
		auto& geometry = m_Queues[std::to_underlying(RenderPhase::Geometry)];
		std::ranges::sort(geometry, std::less{}, &DrawItem::DistanceFromCamera);

		auto& alphaTest = m_Queues[std::to_underlying(RenderPhase::AlphaTest)];
		std::ranges::sort(alphaTest, std::less{}, &DrawItem::DistanceFromCamera);

		// Back-to-front (transparency)
		auto& transparent = m_Queues[std::to_underlying(RenderPhase::Transparent)];
		std::ranges::sort(transparent, std::greater{}, &DrawItem::DistanceFromCamera);
	}

	std::span<const DrawItem> Zephyr::RenderQueue::GetPhase(RenderPhase phase) const
	{
		auto& queue = m_Queues[std::to_underlying(phase)];

		return { queue.data(), queue.size() };
	}
}