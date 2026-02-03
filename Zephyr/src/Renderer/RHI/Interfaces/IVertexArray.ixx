export module Zephyr.Renderer.RHI.Interfaces.IVertexArray;

export import Zephyr.Renderer.RHI.Types.VertexArrayTypes;

export namespace Zephyr::RHI
{
	class IVertexArray
	{
	public:
		virtual ~IVertexArray() = default;

		virtual const VertexLayout& GetLayout() const noexcept = 0;
		virtual const Ref<IBuffer>& GetVertexBuffer() const noexcept = 0;
		virtual const std::optional<IndexBinding>& GetIndexBinding() const noexcept = 0;
	};
}
