export module Zephyr.Renderer.Graph.Passes.GBufferPass;

import Zephyr.Renderer.Graph.IRenderGraphPass;
import Zephyr.Renderer.Graph.GBuffer;

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
