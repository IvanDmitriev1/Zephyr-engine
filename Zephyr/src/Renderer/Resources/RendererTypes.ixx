export module Zephyr.Renderer.Resources.RendererTypes;

export import Zephyr.Renderer.Renderables.Mesh;
export import Zephyr.Renderer.Renderables.Material;
export import glm;

export namespace Zephyr::RHI
{
	struct RenderableObject
	{
		Ref<Mesh> Mesh{};
		Ref<Material> Material{};
		glm::mat4 Transform{};
	};

	struct CameraData
	{
		glm::mat4 ViewProjection{};
		glm::vec3 Position{};
	};
}