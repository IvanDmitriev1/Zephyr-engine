export module Zephyr.Renderer.GBuffer;

export import Zephyr.Renderer.Types.GBufferTypes;
import Zephyr.Renderer.RHI.IFrameBuffer;
import Zephyr.Renderer.RHI.Device;

export namespace Zephyr
{
	struct GBuffer
	{
	public:
		GBuffer() = default;

		void EnsureSize(Extent2D size);

		const RHI::ITexture& GetAlbedoMetallic() const { return FrameBuffer->GetColorAttachment(static_cast<uint32_t>(GBufferAttachment::AlbedoMetallic)); }
		const RHI::ITexture& GetNormalRoughness() const { return FrameBuffer->GetColorAttachment(static_cast<uint32_t>(GBufferAttachment::NormalRoughness)); }
		const RHI::ITexture& GetEmissiveAO() const { return FrameBuffer->GetColorAttachment(static_cast<uint32_t>(GBufferAttachment::EmissiveAO)); }
		const RHI::ITexture& GetDepth() const { return *FrameBuffer->GetDepthAttachment(); }

		Ref<RHI::IFrameBuffer> FrameBuffer;

	private:
		void Create(const GBufferDesc& desc);
	};

	void GBuffer::EnsureSize(Extent2D size)
	{
		if (!FrameBuffer)
		{
			GBufferDesc desc{
				.Size = size,
				.DebugName = "MainGBuffer"
			};

			Create(desc);
			return;
		}

		if (FrameBuffer->GetSize() != size)
		{
			FrameBuffer->Resize(size);
		}
	}

	void GBuffer::Create(const GBufferDesc& desc)
	{
		auto colorFormats = std::to_array<RHI::TextureFormat>(
		{
			{ desc.AlbedoFormat },
			{ desc.NormalFormat },
			{ desc.EmissiveFormat }
		});

		RHI::FrameBufferDesc fbDesc{};
		fbDesc.Size = desc.Size;
		fbDesc.ColorFormats = colorFormats;
		fbDesc.DepthFormat = desc.DepthFormat;
		fbDesc.DebugName = desc.DebugName;

		FrameBuffer = RHI::Device::CreateFrameBuffer(fbDesc);
	}
}