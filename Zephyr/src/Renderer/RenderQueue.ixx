export module Zephyr.Renderer.RenderQueue;

export import Zephyr.Renderer.Types.RendererTypes;

export namespace Zephyr
{
	class RenderQueue final
	{
	public:
		void BeginFrame();
		void Submit(const DrawItem& item);
		void Submit(std::span<const DrawItem> items);
		void SortQueues();

	public:
		std::span<const DrawItem> GetPhase(RenderPhase phase) const;

	private:
		RenderPhaseArray<std::vector<DrawItem>> m_Queues;
	};
}