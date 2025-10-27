export module zephyr.opengl.GLFrameBuffer;

import zephyr.renderer.IFrameBuffer;
import zephyr.renderer.FrameBufferSpecs;

export namespace zephyr
{
	class GLFrameBuffer final : public IFrameBuffer
	{
	public:
		explicit GLFrameBuffer(const FramebufferSpecification& spec);
		~GLFrameBuffer() override;

	public:
		uint32_t Width() const override
		{
			return m_Spec.Width;
		}

		uint32_t Height() const override
		{
			return m_Spec.Height;
		}

	public:
		void Bind() override;
		void UnBind() override;
		void ClearAttachment(uint32_t attachmentIndex, int value) override;
		void Resize(uint32_t width, uint32_t height) override;

		uint32_t GetTexture(uint32_t index) override;

	private:
		void Invalidate();
		void Destroy();

	private:
		FramebufferSpecification m_Spec;
		uint32_t m_FBO = 0;
		uint32_t m_RBO = 0; // depth-stencil renderbuffer
		std::vector<uint32_t> m_ColorAttachments; // GL texture names
	};
}