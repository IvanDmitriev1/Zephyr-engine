export module Zephyr.Renderer.OpenGL.GlTexture;

export import Zephyr.Renderer.Core.ITexture;

export namespace Zephyr::RHI::OpenGL
{
	class GlTexture final : public ITexture
	{
	public:
		explicit GlTexture(TextureDesc desc);
		~GlTexture() override;

		GlTexture(const GlTexture&) = delete;
		GlTexture& operator=(const GlTexture&) = delete;

		GlTexture(GlTexture&& other) noexcept;
		GlTexture& operator=(GlTexture&& other) noexcept;

	public:
		const TextureDesc& GetDesc() const noexcept override
		{
			return m_desc;
		}

		const uint32_t GetId() const noexcept
		{
			return m_Id;
		}

	private:
		void Destroy() noexcept;
		void Invalidate();

	private:
		TextureDesc m_desc{};
		uint32_t m_Id{};
	};
}