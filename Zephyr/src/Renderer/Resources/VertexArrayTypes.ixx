export module Zephyr.Renderer.Resources.VertexArrayTypes;

export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Renderer.Resources.VertexLayout;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
	enum class IndexType : uint8_t
	{
		UInt16,
		UInt32
	};

	struct IndexBinding
	{
		Ref<IBuffer> Buffer{};
		IndexType Type{ IndexType::UInt32 };
		uint64_t OffsetBytes{ 0 };
	};

	struct VertexArrayCreateInfo
	{
		VertexLayout Layout{};
		Ref<IBuffer> VertexBuffer{};
		std::optional<IndexBinding> Index{};

		std::string_view DebugName{};
	};

	constexpr uint32_t GetIndexSize(IndexType type)
	{
		switch (type)
		{
		case IndexType::UInt16: return sizeof(uint16_t);
		case IndexType::UInt32: return sizeof(uint32_t);
		default:
			break;
		}

		throw std::runtime_error("GetIndexSize: unsupported IndexType");
	}
}