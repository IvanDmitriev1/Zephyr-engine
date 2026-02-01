export module Zephyr.Renderer.RHI.RenderEncoderTypes;

export import Zephyr.Renderer.RHI.IBuffer;
export import Zephyr.Renderer.RHI.ITexture;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
	struct ResourceBinding
	{
		using BoundResource = std::variant<
			Ref<IBuffer>,
			Ref<ITexture>,
			Ref<ISampler>
		>;

		uint32_t BindingSlot{};
		BoundResource Resource{};

		inline ResourceBinding(uint32_t slot, Ref<IBuffer> b) : BindingSlot(slot), Resource(std::move(b)) {}
		inline ResourceBinding(uint32_t slot, Ref<ITexture> t) : BindingSlot(slot), Resource(std::move(t)) {}
		inline ResourceBinding(uint32_t slot, Ref<ISampler> s) : BindingSlot(slot), Resource(std::move(s)) {}
	};
}