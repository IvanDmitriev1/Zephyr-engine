export module Zephyr.Renderer.Core.ITexture;

export import Zephyr.Renderer.Resources.TextureTypes;

export namespace Zephyr::RHI
{
	class ITexture
	{
	public:
		virtual ~ITexture() = default;

		virtual const TextureDesc& GetDesc() const noexcept = 0;
		virtual const uint32_t GetId() const noexcept = 0;
	};

	class ISampler
	{
	public:
		virtual ~ISampler() = default;
	};
}