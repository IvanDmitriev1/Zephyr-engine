export module Zephyr.Renderer.Resources.RendererTypes;

export import Zephyr.Renderer.Renderables.Mesh;
export import Zephyr.Renderer.Renderables.Material;
export import glm;

export namespace Zephyr
{	
	struct DrawItem
	{
		Ref<Mesh> Mesh{};
		Ref<Material> Material{};
		glm::mat4 Transform{};
		RenderQueue Queue = RenderQueue::Geometry;

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