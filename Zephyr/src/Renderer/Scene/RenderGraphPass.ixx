export module Zephyr.Renderer.RenderGraphPass;

export import Zephyr.Renderer.Resources.RenderPassTypes;
export import Zephyr.Renderer.SceneRenderer;

export namespace Zephyr
{
	class RenderGraphPass final
	{
	public:
		using ExecuteFunc = std::function<void(SceneRenderer& renderer)>;

		RenderGraphPass(std::string_view name, Ref<RHI::IFrameBuffer> target)
			: m_Name(name), m_Target(std::move(target)) {}

		~RenderGraphPass() = default;

		void Execute(SceneRenderer& renderer) const
		{
			if (m_ExecuteFunc)
			{
				m_ExecuteFunc(renderer);
			}
		}

		RHI::RenderPassDesc GetDesc() const
		{
			return
			{
				.Target = m_Target,
				.Colors = { m_ColorAttachments.data(), m_ColorAttachments.size() },
				.Depth = m_DepthAttachment,
				.QueuesFilter = m_QueueFilter,
				.DebugName = m_Name
			};
		}

	public:
		std::vector<RHI::ColorAttachment>& GetColorAttachments() { return m_ColorAttachments; }
		std::optional<RHI::DepthAttachment>& GetDepthAttachment() { return m_DepthAttachment; }
		RenderQueueArray<RenderQueue>& GetQueueFilter() { return m_QueueFilter; }

		void SetExecuteFunc(ExecuteFunc&& func) { m_ExecuteFunc = std::move(func); }

	private:
		std::string m_Name;
		Ref<RHI::IFrameBuffer> m_Target;

		ExecuteFunc m_ExecuteFunc;
		std::vector<RHI::ColorAttachment> m_ColorAttachments;
		std::optional<RHI::DepthAttachment> m_DepthAttachment;
		RenderQueueArray<RenderQueue> m_QueueFilter;
	};
}