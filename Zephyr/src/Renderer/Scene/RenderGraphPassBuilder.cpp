module Zephyr.Renderer.RenderGraphPassBuilder;

namespace Zephyr
{
	RenderGraphPassBuilder::RenderGraphPassBuilder(RenderGraphPass& pass)
	: m_Pass(pass)
	{
		m_Pass.GetColorAttachments().push_back(
		{
			.Load = RHI::LoadOp::Clear,
			.Store = RHI::StoreOp::Store,
			.Clear = { 0.1f, 0.1f, 0.1f, 1.0f }
		});

		m_Pass.GetDepthAttachment() = 
		{
			.Load = RHI::LoadOp::Clear,
			.Store = RHI::StoreOp::DontCare,
			.ClearDepth = 1.0f
		};

		m_Pass.GetQueueFilter() =
		{
			RenderQueue::Background,
			RenderQueue::Geometry,
			RenderQueue::AlphaTest,
			RenderQueue::Transparent,
			RenderQueue::Overlay
		};
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::ClearColor(float r, float g, float b, float a)
	{
		auto& colorAttachment = m_Pass.GetColorAttachments().at(0);
		colorAttachment.Clear = { r, g, b, a };
		colorAttachment.Load = RHI::LoadOp::Clear;

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::LoadColor()
	{
		auto& colorAttachment = m_Pass.GetColorAttachments().at(0);
		colorAttachment.Load = RHI::LoadOp::Load;

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::DontCareColor()
	{
		auto& colorAttachment = m_Pass.GetColorAttachments().at(0);
		colorAttachment.Load = RHI::LoadOp::DontCare;

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::ClearDepth(float depth)
	{
		if (!m_Pass.GetDepthAttachment())
			return *this;

		m_Pass.GetDepthAttachment()->ClearDepth = depth;
		m_Pass.GetDepthAttachment()->Load = RHI::LoadOp::Clear;

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::LoadDepth()
	{
		if (!m_Pass.GetDepthAttachment())
		{
			m_Pass.GetDepthAttachment() = RHI::DepthAttachment{};
		}

		m_Pass.GetDepthAttachment()->Load = RHI::LoadOp::Load;
		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::NoDepth()
	{
		m_Pass.GetDepthAttachment() = std::nullopt;

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::StoreDepth()
	{
		if (m_Pass.GetDepthAttachment())
		{
			m_Pass.GetDepthAttachment()->Store = RHI::StoreOp::Store;
		}

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::OnlyGeometry()
	{
		m_Pass.GetQueueFilter() =
		{
			RenderQueue::Geometry
		};

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::OnlyTransparent()
	{
		m_Pass.GetQueueFilter() =
		{
			RenderQueue::Transparent
		};

		return *this;
	}

	RenderGraphPassBuilder& RenderGraphPassBuilder::Execute(RenderGraphPass::ExecuteFunc&& func)
	{
		m_Pass.SetExecuteFunc(std::move(func));
		return *this;
	}

}