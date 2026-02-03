export module Zephyr.Scene.Components.MeshComponent;

export import Zephyr.Renderer.Resources.Material;
export import Zephyr.Renderer.Resources.Mesh;

export namespace Zephyr
{
	struct MeshComponent
	{
		Ref<Mesh> MeshData;
		Ref<Material> MaterialInstance;
	};
}