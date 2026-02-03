export module Zephyr.Scene.Components.MeshComponent;

export import Zephyr.Renderer.Resources.Material;
export import Zephyr.Renderer.Resources.Mesh;
import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	struct MeshComponent
	{
		Ref<Mesh> MeshData;
		Ref<Material> MaterialInstance;
	};
}