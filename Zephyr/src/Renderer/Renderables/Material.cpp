module Zephyr.Renderer.Renderables.Material;

import Zephyr.Core.HashUtils;

namespace Zephyr
{
	Material::Material(const MaterialDesc& desc)
		:m_Name(std::move(desc.Name)),
		m_Shader(std::move(desc.Shader)),
		m_Type(desc.Type),
		m_Properties(desc.Properties),
		m_Bindings(std::move(desc.Bindings))
	{
		
	}
}