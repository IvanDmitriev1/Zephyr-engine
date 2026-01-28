export module Zephyr.Renderer.Passes.GBufferPass;

export import Zephyr.Renderer.IRenderGraphPass;
import Zephyr.Renderer.GBuffer;

export namespace Zephyr
{
	class GBufferPass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "GBufferPass"; }
		void Execute(PassExecutionContext& ctx) override;

	private:
		GBuffer m_GBuffer;
	};
}
