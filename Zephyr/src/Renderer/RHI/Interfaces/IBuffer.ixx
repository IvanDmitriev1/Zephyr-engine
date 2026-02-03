export module Zephyr.Renderer.RHI.Interfaces.IBuffer;

import Zephyr.Renderer.RHI.Types.BufferTypes;

export namespace Zephyr::RHI
{
	class IBuffer
	{
	public:
		virtual ~IBuffer() = default;

		virtual const BufferDesc& GetDesc() const noexcept = 0;
		virtual void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes = 0) = 0;
	};
}
