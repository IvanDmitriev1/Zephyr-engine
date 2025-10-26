export module zephyr.renderer.IFrameBuffer;

export import std.compat;

export namespace zephyr
{
	class IFrameBuffer
	{
	public:
		IFrameBuffer() = default;
		virtual ~IFrameBuffer() = default;

		IFrameBuffer(const IFrameBuffer&) = delete;
		IFrameBuffer& operator=(const IFrameBuffer&) = delete;

	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
		virtual void Resize(int32_t width, int32_t height) = 0;

		virtual uint32_t GetTexture(uint32_t index) = 0;
	};
}