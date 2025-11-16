module zephyr.renderer.RenderCommandQueue;

namespace zephyr
{
	void RenderCommandQueue::Submit(const DrawCommand& cmd)
	{
		m_Commands.push_back(cmd);
	}

	void RenderCommandQueue::Clear()
	{
		m_Commands.clear();
	}

	void RenderCommandQueue::Flush(IRendererAPI& api, const glm::mat4& viewProjection)
	{
		for (const auto& cmd : m_Commands)
		{
			if (!cmd.Shader || !cmd.VertexArray)
				continue;

			cmd.Shader->Bind();
			cmd.Shader->SetMat4("u_ViewProjection", viewProjection);
			cmd.Shader->SetMat4("u_ModelMatrix", cmd.Transform);

			api.DrawIndexed(*cmd.VertexArray, cmd.Topology);
		}
	}
}