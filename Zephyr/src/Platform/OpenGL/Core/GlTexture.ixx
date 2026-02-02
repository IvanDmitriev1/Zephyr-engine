export module Zephyr.Renderer.OpenGL.GlTexture;

export import Zephyr.Renderer.RHI.ITexture;

export namespace Zephyr::RHI::OpenGL
{
	class GlTexture final : public ITexture
	{
	public:
		GlTexture() = default;
		explicit GlTexture(const TextureDesc& desc);
		~GlTexture() override;

		GlTexture(const GlTexture&) = delete;
		GlTexture& operator=(const GlTexture&) = delete;
		GlTexture(GlTexture&& other) noexcept;
		GlTexture& operator=(GlTexture&& other) noexcept;

	public:
		inline Extent2D GetSize() const noexcept override { return m_Size; }
		inline TextureFormat GetFormat() const noexcept override { return m_Format; }
		inline uint32_t GetMipLevels() const noexcept override { return m_MipLevels; }
		inline uint32_t GetArrayLayers() const noexcept override { return m_ArrayLayers; }

	public:
		inline uint32_t GetId() const noexcept { return m_Id; }

	private:
		void Destroy() noexcept;
		void Invalidate();

	private:
		Extent2D m_Size{};
		TextureFormat m_Format = TextureFormat::RGBA8;
		uint32_t m_MipLevels{ 1 };
		uint32_t m_ArrayLayers{ 1 };
		std::string m_Name;

		uint32_t m_Id{};
	};
}