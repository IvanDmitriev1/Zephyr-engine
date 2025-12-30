export module Zephyr.Renderer.OpenGL.GlFrameBuffer;

export import Zephyr.Renderer.Core.IFrameBuffer;
export import Zephyr.Renderer.OpenGL.GlTexture;
export import Zephyr.Renderer.Resources.RenderPassTypes;

export namespace Zephyr::RHI::OpenGL
{
	class GlFrameBuffer final : public IFrameBuffer
	{
	public:
		explicit GlFrameBuffer(FrameBufferDesc desc);
		~GlFrameBuffer() override;

	public:
		const FrameBufferDesc& GetDesc() const noexcept override
		{
			return m_Spec;
		}

		size_t GetColorAttachmentCount() const noexcept override
		{
			return m_ColorAttachments.size();
		}

		std::optional<std::reference_wrapper<const ITexture>> GetDepthAttachment() const override
		{
			return m_DepthAttachment;
		}

		uint32_t GetHandle() const noexcept
		{
			return m_FBO;
		}

		const ITexture& GetColorAttachment(size_t index) const override;
		void Resize(Extent2D newSize) override;

	public:
		void Bind();
		void ClearForRenderPass(const RenderPassDesc& rp);

	private:
		void Destroy() noexcept;
		void Invalidate();

		void CreateAttachments();
		void AttachTextures();
		void CheckStatus();

	public:
		FrameBufferDesc m_Spec;
		uint32_t m_FBO = 0;
		std::vector<GlTexture> m_ColorAttachments;
		std::optional<GlTexture> m_DepthAttachment;
	};
}