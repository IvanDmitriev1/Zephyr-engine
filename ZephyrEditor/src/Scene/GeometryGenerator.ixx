export module ZephyrEditor.GeometryGenerator;

import Zephyr.Renderer.Resources.Mesh;
import Zephyr.Renderer.Types.Vertex3d;
import Zephyr.Renderer.RHI.Interfaces.Device;
import Zephyr.Core.CoreTypes;
import std.compat;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class GeometryGenerator
	{
	public:
		static Ref<Mesh> CreateCube(float size = 1.0f);
		static Ref<Mesh> CreateSphere(float radius = 0.5f,
									  uint32_t stacks = 16,
									  uint32_t slices = 32);

	private:
		static Ref<Mesh> CreateMeshFromData(
			const std::vector<Vertex3D>& vertices,
			const std::vector<uint32_t>& indices);
	};
}