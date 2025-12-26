export module Zephyr.Renderer.Resources.VertexArrayTypes;

export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Renderer.Resources.VertexLayout;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
	struct VertexArrayCreateInfo
	{
		Ref<IVertexBuffer> VertexBuffer{};
		VertexLayout Layout{};

		Ref<IIndexBuffer> IndexBuffer{};
		IndexType IndexType{};

		std::string_view DebugName{};
	};
}