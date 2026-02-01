module Zephyr.Renderer.PipelineCache;

namespace Zephyr
{
	void PipelineCache::Clear()
	{
		m_Cache.clear();
	}

	void PipelineCache::ClearShader(const RHI::IShader* shader)
	{
		size_t shaderHash = shader->GetHash();
		std::erase_if(m_Cache, [&](const auto& pair)
		{
			return pair.first.ShaderHash == shaderHash;
		});
	}

	RHI::GraphicsPipelineDesc PipelineCache::BuildDesc(const Material& material, const Ref<RHI::IFrameBuffer>& target) noexcept
	{
		RHI::GraphicsPipelineDesc desc{};
		desc.Shader = material.GetShader();
		desc.Topology = RHI::PrimitiveTopology::Triangles;

		const auto& targetDesc = target->GetDesc();

		if (!targetDesc.ColorAttachments.empty())
		{
			desc.ColorFormat = targetDesc.ColorAttachments[0].Format;
		}
		if (targetDesc.DepthStencilAttachment)
		{
			desc.DepthFormat = targetDesc.DepthStencilAttachment->Format;
		}

		ApplyMaterialDefaults(desc, material);

		return desc;
	}

	void PipelineCache::ApplyMaterialDefaults(RHI::GraphicsPipelineDesc& desc, const Material& material) noexcept
	{
		desc.Rasterizer.Polygon = RHI::PolygonMode::Fill;
		desc.Rasterizer.Face = RHI::FrontFace::CounterClockwise;
		desc.Depth.DepthCompare = RHI::CompareOp::LessEqual;

		switch (material.GetAlphaMode())
		{
		case AlphaMode::Opaque:
		case AlphaMode::Masked:
			desc.Blend.Enable = false;
			desc.Rasterizer.Cull = RHI::CullMode::Back;
			desc.Depth.DepthTestEnable = true;
			desc.Depth.DepthWriteEnable = true;
			break;

		case AlphaMode::Blend:
			desc.Blend.Enable = true;
			desc.Rasterizer.Cull = RHI::CullMode::None;
			desc.Depth.DepthTestEnable = true;
			desc.Depth.DepthWriteEnable = false;  // Transparent doesn't write depth
			break;
		}
	}

	size_t PipelineCache::HashPipelineDesc(const RHI::GraphicsPipelineDesc& desc) noexcept
	{
		size_t h = 0;

		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.Topology));
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.Rasterizer.Cull)) << 1;
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.Rasterizer.Face)) << 2;
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.Rasterizer.Polygon)) << 3;
		h ^= std::hash<bool>{}(desc.Rasterizer.DepthClampEnable) << 4;
		h ^= std::hash<bool>{}(desc.Depth.DepthTestEnable) << 5;
		h ^= std::hash<bool>{}(desc.Depth.DepthWriteEnable) << 6;
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.Depth.DepthCompare)) << 7;
		h ^= std::hash<bool>{}(desc.Depth.StencilTestEnable) << 8;
		h ^= std::hash<bool>{}(desc.Blend.Enable) << 9;
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.ColorFormat)) << 10;
		h ^= std::hash<uint8_t>{}(static_cast<uint8_t>(desc.DepthFormat)) << 11;
		h ^= std::hash<uint32_t>{}(desc.SampleCount) << 12;

		return h;
	}

}