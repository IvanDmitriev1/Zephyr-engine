export module zephyr.opengl.GLRendererAPI;

import zephyr.renderer.IRendererAPI;
import zephyr.renderer.FrameBufferSpecs;
import zephyr.opengl.GLFrameBuffer;
import zephyr.core.coreTypes;

export namespace zephyr
{
	class GLRendererAPI final : public IRendererAPI
	{
	public:
		GLRendererAPI() = default;
		~GLRendererAPI() override = default;

	public:
		void BeginFrame() override;
		void EndFrame() override;

		void SetDepthTest(bool enabled) override;
		void SetScissorTest(bool enabled) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear(bool color, bool depth) override;

	public:
		void DrawIndexed(const IVertexArray& vao, PrimitiveTopology topology) override;
	};
}