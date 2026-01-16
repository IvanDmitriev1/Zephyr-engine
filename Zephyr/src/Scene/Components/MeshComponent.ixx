export module Zephyr.Scene.Components.MeshComponent;

export import Zephyr.Renderer.Renderables.Material;
export import Zephyr.Renderer.Renderables.Mesh;

export namespace Zephyr
{
	struct MeshComponent
	{
		Ref<Mesh> MeshData;
		Ref<Material> MaterialInstance;
	};
}