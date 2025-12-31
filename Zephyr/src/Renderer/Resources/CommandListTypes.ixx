export module Zephyr.Renderer.Resources.CommandListTypes;

export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Renderer.Core.ITexture;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
	struct ResourceBinding
	{
		uint32_t Slot{};
		Ref<IBuffer> UniformBuffer{};
		Ref<ITexture> Texture{};
		Ref<ISampler> Sampler{};
	};
}