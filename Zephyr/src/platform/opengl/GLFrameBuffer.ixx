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
		void Bind() override;
		void UnBind() override;
		void ClearAttachment(uint32_t attachmentIndex, int value) override;
		void Resize(int32_t width, int32_t height) override;

		uint32_t GetTexture(uint32_t index) override;

	private:
		FramebufferSpecification m_spec;
	};
}