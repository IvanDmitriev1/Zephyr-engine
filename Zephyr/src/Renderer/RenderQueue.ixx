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
		std::span<const DrawItem> GetCategory(DrawCategory category) const;

	private:
		DrawCategoryArray<std::vector<DrawItem>> m_Queues;
	};
}