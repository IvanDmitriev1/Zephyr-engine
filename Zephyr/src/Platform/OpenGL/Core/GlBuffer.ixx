export module Zephyr.Renderer.OpenGL.GlBuffer;

export import Zephyr.Renderer.Resources.BufferTypes;

export namespace Zephyr::RHI::OpenGL
{
	class GlBuffer final
	{
	public:
		explicit GlBuffer(BufferDesc desc);
		~GlBuffer();

		GlBuffer(const GlBuffer&) = delete;
		GlBuffer& operator=(const GlBuffer&) = delete;

	public:
		uint32_t RendererID() const noexcept
		{
			return m_RendererID;
		}
		const BufferDesc& GetDesc() const noexcept
		{
			return m_Desc;
		}

		void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes = 0);

	private:
		uint32_t m_RendererID = 0;
		BufferDesc m_Desc;
	};
}