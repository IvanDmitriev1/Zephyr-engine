export module Zephyr.Renderer.Core.IVertexArray;

export import Zephyr.Renderer.Resources.VertexArrayTypes;

export namespace Zephyr::RHI
{
	class IVertexArray
	{
	public:
		virtual ~IVertexArray() = default;

		virtual const VertexLayout& GetLayout() const noexcept = 0;
		virtual const Zephyr::Ref<IVertexBuffer>& GetVertexBuffer() const noexcept = 0;
		virtual const Zephyr::Ref<IIndexBuffer>& GetIndexBuffer() const noexcept = 0;
		virtual bool HasIndexBuffer() const noexcept = 0;
	};
}