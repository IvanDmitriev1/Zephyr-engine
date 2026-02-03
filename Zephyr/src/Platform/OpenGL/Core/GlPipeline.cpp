module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlPipeline;

import Zephyr.Renderer.OpenGL.Types.GlPipelineTypes;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::RHI::OpenGL
{
    GlPipeline::GlPipeline(const GraphicsPipelineDesc& desc)
        : m_Desc(desc)
    {
    
    }

    void GlPipeline::Bind()
    {
		auto& glShader = StaticCast<GlShader>(m_Desc.Shader);
		glShader.Bind();

		ApplyRasterizerState();
		ApplyDepthState();
		ApplyBlendState();
	}

    void GlPipeline::ApplyRasterizerState()
    {
        if (m_Desc.Rasterizer.Cull == CullMode::None)
        {
            glDisable(GL_CULL_FACE);
        }
        else
        {
            glEnable(GL_CULL_FACE);
            glCullFace(ToGlCull(m_Desc.Rasterizer.Cull));
        }

        glFrontFace(ToGlFrontFace(m_Desc.Rasterizer.Face));
		glPolygonMode(GL_FRONT_AND_BACK, ToGlPolygonMode(m_Desc.Rasterizer.Polygon));

		if (m_Desc.Rasterizer.DepthClampEnable)
			glEnable(GL_DEPTH_CLAMP);
		else
			glDisable(GL_DEPTH_CLAMP);

		if (m_Desc.Rasterizer.Polygon == PolygonMode::Wireframe)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-1.0f, -1.0f);
		}
		else
		{
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
    }

    void GlPipeline::ApplyDepthState()
    {
        if (m_Desc.Depth.DepthTestEnable)
        {
            glEnable(GL_DEPTH_TEST);
			glDepthFunc(ToGlCompare(m_Desc.Depth.DepthCompare));
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
		
        glDepthMask(m_Desc.Depth.DepthWriteEnable ? GL_TRUE : GL_FALSE);

		if (m_Desc.Depth.StencilTestEnable)
		{
			glEnable(GL_STENCIL_TEST);
		}
		else
		{
			glDisable(GL_STENCIL_TEST);
		}
    }

    void GlPipeline::ApplyBlendState()
    {
        if (m_Desc.Blend.Enable)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }
}