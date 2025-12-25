export module Zephyr.Renderer.OpenGL.GlTexture;

export import Zephyr.Renderer.Core.ITexture;

export namespace Zephyr::RHI::OpenGL
{
	class GlTexture final : public ITexture
	{
	public:
		explicit GlTexture(TextureDesc desc);
		~GlTexture() override;

	public:
		const TextureDesc& GetDesc() const noexcept override
		{
			return m_desc;
		}

		uint32_t GetId() const noexcept
		{
			return m_Id;
		}

	private:
		void Invalidate();

	private:
		TextureDesc m_desc{};
		uint32_t m_Id{};
	};
}