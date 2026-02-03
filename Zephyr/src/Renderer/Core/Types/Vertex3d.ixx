export module Zephyr.Renderer.Types.Vertex3d;

import Zephyr.Renderer.RHI.Types.VertexLayout;
import glm;

export namespace Zephyr
{
	struct Vertex3D
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;

		static constexpr RHI::VertexLayout GetLayout()
		{
			return RHI::MakeLayoutFromMembers<Vertex3D>(std::to_array(
			{
				RHI::VertexAttribute{ "a_Position", RHI::VertexAttributeType::Float3 },
				RHI::VertexAttribute{ "a_Normal",   RHI::VertexAttributeType::Float3 },
				RHI::VertexAttribute{ "a_TexCoord", RHI::VertexAttributeType::Float2 }
			}));
		}
	};
}
