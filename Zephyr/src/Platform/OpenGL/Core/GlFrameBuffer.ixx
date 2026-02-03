export module Zephyr.Renderer.OpenGL.GlFrameBuffer;

import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.RHI.Types.RenderPassTypes;
import std.compat;

export namespace Zephyr::RHI::OpenGL
{
	class GlFrameBuffer final : public IFrameBuffer
	{
	public:
		explicit GlFrameBuffer(const FrameBufferDesc& desc);
		~GlFrameBuffer() override;

	public:
		inline Extent2D GetSize() const noexcept override { return m_Size; }
		inline size_t GetColorAttachmentCount() const noexcept override { return m_ColorAttachments.size(); }
		inline std::optional<std::reference_wrapper<const ITexture>> GetDepthAttachment() const override { return m_DepthAttachment; }
		const ITexture& GetColorAttachment(size_t index) const override;

		void Resize(Extent2D newSize) override;

	public:
		inline uint32_t GetHandle() const noexcept { return m_FBO; }

	public:
		void Bind() const;
		void Unbind() const;
		void ClearForRenderPass(const RenderPassDesc& rp) const;

	private:
		void Destroy() noexcept;
		void Invalidate();

		void CreateAttachments();
		void AttachTextures();
		void CheckStatus();

	public:
		Extent2D m_Size{};
		std::vector<TextureFormat> m_ColorAttachmentDescs;
		std::optional<TextureFormat> m_DepthAttachmentDesc;
		std::string m_Name;

		uint32_t m_FBO = 0;
		std::vector<GlTexture> m_ColorAttachments;
		std::optional<GlTexture> m_DepthAttachment;
	};
}