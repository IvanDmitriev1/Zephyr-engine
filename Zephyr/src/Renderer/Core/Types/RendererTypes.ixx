export module Zephyr.Renderer.Types.RendererTypes;

export import Zephyr.Renderer.Types.DrawCategory;
import Zephyr.Renderer.Resources.Mesh;
import Zephyr.Renderer.Resources.Material;
import glm;
import Zephyr.Core.CoreTypes;

export namespace Zephyr
{	
	struct DrawItem
	{
		Ref<Mesh> Mesh{};
		Ref<Material> Material{};
		glm::mat4 Transform{};
		DrawCategory Category = DrawCategory::Opaque;

		float DistanceFromCamera = 0.0f;
	};

	struct CameraUniformData
	{
		glm::mat4 ViewProjection{ 1.0f };
		glm::vec4 Position{ 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct ObjectUniformData
	{
		glm::mat4 Model{};
	};
}
