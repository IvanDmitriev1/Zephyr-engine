export module Zephyr.Renderer.RHI.Types.RenderEncoderTypes;

import Zephyr.Renderer.RHI.Interfaces.IBuffer;
import Zephyr.Renderer.RHI.Interfaces.ITexture;
import Zephyr.Core.CoreTypes;

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
