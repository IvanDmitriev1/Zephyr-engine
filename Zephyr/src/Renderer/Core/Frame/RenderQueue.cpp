module Zephyr.Renderer.Frame.RenderQueue;

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
		m_Queues[std::to_underlying(item.Category)].push_back(item);
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
		auto& opaque = m_Queues[std::to_underlying(DrawCategory::Opaque)];
		std::ranges::sort(opaque, std::less{}, &DrawItem::DistanceFromCamera);

		auto& alphaMasked = m_Queues[std::to_underlying(DrawCategory::AlphaMasked)];
		std::ranges::sort(alphaMasked, std::less{}, &DrawItem::DistanceFromCamera);

		// Back-to-front for transparent (correct blending)
		auto& transparent = m_Queues[std::to_underlying(DrawCategory::Transparent)];
		std::ranges::sort(transparent, std::greater{}, &DrawItem::DistanceFromCamera);
	}

	std::span<const DrawItem> Zephyr::RenderQueue::GetCategory(DrawCategory category) const
	{
		auto& queue = m_Queues[std::to_underlying(category)];

		return { queue.data(), queue.size() };
	}
}