export module Zephyr.Renderer.SceneRenderer;

export import Zephyr.Renderer.Scene.Camera;
export import Zephyr.Renderer.Scene.RenderGraph;
export import Zephyr.Renderer.Renderables.Mesh;
export import Zephyr.Renderer.Renderables.Material;
export import Zephyr.Renderer.Resources.RendererTypes;
export import Zephyr.Renderer.Core.ICommandList;
export import Zephyr.Renderer.Core.IFrameBuffer;
export import glm;
export import std.compat;
import <format>;

export namespace Zephyr
{
	class SceneRenderer
	{
	public:
		SceneRenderer() = default;

		void BeginScene(const Camera& camera, Ref<RHI::IFrameBuffer> viewportTarget);
		void SubmitShadowCaster(std::string name);
		void SubmitMesh(Ref<Mesh> mesh, Ref<Material> material, const glm::mat4& transform, bool transparent = false);
		void EndScene();

		void Flush(RHI::ICommandList& cmdList);

	private:
		struct MeshSubmission
		{
			Ref<Mesh> MeshRef{};
			Ref<Material> MaterialRef{};
			glm::mat4 Transform{};
			bool Transparent = false;
		};

		struct ShadowSubmission
		{
			std::string Name{};
		};

		void BuildGraph();

		std::vector<MeshSubmission> m_Submissions{};
		std::vector<ShadowSubmission> m_ShadowSubmissions{};

		CameraData m_CameraData{};
		Ref<RHI::IFrameBuffer> m_ViewportTarget{};

		RenderGraph m_RenderGraph{};
		RenderGraphResourceHandle m_ViewportHandle{};
		RenderGraphResourceHandle m_DepthHandle{};
		RenderGraphResourceHandle m_OpaqueHandle{};
		RenderGraphResourceHandle m_TransparentHandle{};
		RenderGraphResourceHandle m_PostProcessHandle{};
		std::vector<RenderGraphResourceHandle> m_ShadowHandles{};

		bool m_SceneActive = false;
	};
}

namespace Zephyr
{
	void SceneRenderer::BeginScene(const Camera& camera, Ref<RHI::IFrameBuffer> viewportTarget)
	{
		Assert(!m_SceneActive, "SceneRenderer::BeginScene called while a scene is already active");

		m_SceneActive = true;
		m_Submissions.clear();
		m_ShadowSubmissions.clear();
		m_ShadowHandles.clear();

		m_ViewportTarget = std::move(viewportTarget);
		m_CameraData.ViewProjection = camera.GetViewProjection();
		m_CameraData.Position = camera.GetPosition();
	}

	void SceneRenderer::SubmitMesh(Ref<Mesh> mesh, Ref<Material> material, const glm::mat4& transform, bool transparent)
	{
		Assert(m_SceneActive, "SceneRenderer::SubmitMesh called outside of BeginScene/EndScene");

		auto& submission = m_Submissions.emplace_back();
		submission.MeshRef = std::move(mesh);
		submission.MaterialRef = std::move(material);
		submission.Transform = transform;
		submission.Transparent = transparent;
	}

	void SceneRenderer::SubmitShadowCaster(std::string name)
	{
		Assert(m_SceneActive, "SceneRenderer::SubmitShadowCaster called outside of BeginScene/EndScene");
		m_ShadowSubmissions.push_back({ std::move(name) });
	}

	void SceneRenderer::EndScene()
	{
		Assert(m_SceneActive, "SceneRenderer::EndScene called without BeginScene");
		m_SceneActive = false;
		BuildGraph();
	}

	void SceneRenderer::Flush(RHI::ICommandList& cmdList)
	{
		if (m_SceneActive)
		{
			EndScene();
		}

		m_RenderGraph.Execute(cmdList);

		m_Submissions.clear();
		m_ShadowSubmissions.clear();
		m_ShadowHandles.clear();
	}

	void SceneRenderer::BuildGraph()
	{
		m_RenderGraph = RenderGraph{};

		m_ViewportHandle = m_RenderGraph.ImportResource({ RenderGraphResourceType::External, "ViewportTarget" });
		m_DepthHandle = m_RenderGraph.CreateResource({ RenderGraphResourceType::Texture, "DepthPrepass" });
		m_OpaqueHandle = m_RenderGraph.CreateResource({ RenderGraphResourceType::Texture, "OpaqueColor" });
		m_TransparentHandle = m_RenderGraph.CreateResource({ RenderGraphResourceType::Texture, "TransparentColor" });
		m_PostProcessHandle = m_RenderGraph.CreateResource({ RenderGraphResourceType::Texture, "PostProcess" });

		for (size_t lightIndex = 0; lightIndex < m_ShadowSubmissions.size(); ++lightIndex)
		{
			const auto& shadow = m_ShadowSubmissions[lightIndex];
			auto handle = m_RenderGraph.CreateResource({ RenderGraphResourceType::Texture, shadow.Name });
			m_ShadowHandles.push_back(handle);

			auto builder = m_RenderGraph.AddPass(std::format("Shadow Pass {}", shadow.Name), []([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
			builder.Write(handle);
		}

		auto depthPrepass = m_RenderGraph.AddPass("Depth Prepass", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		depthPrepass.Write(m_DepthHandle);

		auto opaquePass = m_RenderGraph.AddPass("Opaque Pass", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		opaquePass.Read(m_DepthHandle);
		opaquePass.Write(m_OpaqueHandle);

		auto transparentPass = m_RenderGraph.AddPass("Transparent Pass", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		transparentPass.Read(m_DepthHandle);
		transparentPass.Read(m_OpaqueHandle);
		transparentPass.Write(m_TransparentHandle);

		auto gizmoPass = m_RenderGraph.AddPass("Gizmos/Overlay", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		gizmoPass.Read(m_TransparentHandle);
		gizmoPass.Write(m_TransparentHandle);

		auto postProcessPass = m_RenderGraph.AddPass("Post Process", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		postProcessPass.Read(m_TransparentHandle);
		postProcessPass.Write(m_PostProcessHandle);

		auto compositePass = m_RenderGraph.AddPass("Composite", [this]([[maybe_unused]] const RenderGraphExecutionContext& context, [[maybe_unused]] RHI::ICommandList& cmdList) {});
		compositePass.Read(m_PostProcessHandle);
		compositePass.Write(m_ViewportHandle);
	}
}
