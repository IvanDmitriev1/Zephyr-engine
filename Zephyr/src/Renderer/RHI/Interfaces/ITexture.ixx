export module Zephyr.Renderer.RHI.Interfaces.ITexture;

import Zephyr.Renderer.RHI.Types.TextureTypes;
import std.compat;

export namespace Zephyr::RHI
{
	class ITexture
	{
	public:
		virtual ~ITexture() = default;

		virtual Extent2D GetSize() const noexcept = 0;
		virtual TextureFormat GetFormat() const noexcept = 0;
		virtual uint32_t GetMipLevels() const noexcept = 0;
		virtual uint32_t GetArrayLayers() const noexcept = 0;
	};

	class ISampler
	{
	public:
		virtual ~ISampler() = default;
	};
}
