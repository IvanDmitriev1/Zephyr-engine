module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlCommandBuffer;

import Zephyr.Renderer.OpenGL.GlRenderPassEncoder;

namespace Zephyr::RHI::OpenGL
{
	Scope<IRenderEncoder> GlCommandBuffer::BeginRenderPass(const RenderPassDesc& desc)
	{
		return CreateScope<GlRenderPassEncoder>(desc);
	}

	void GlCommandBuffer::Execute()
	{
		glFlush();
	}
}