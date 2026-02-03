export module ZephyrEditor.SceneSetup;

import ZephyrEditor.GeometryGenerator;
import Zephyr.Scene.World;
import Zephyr.Renderer.Shaders.ShaderLoader;
import Zephyr.Renderer.Resources.Material;

import Zephyr.Scene.Components.TransformComponent;
import Zephyr.Scene.Components.MeshComponent;
import Zephyr.Scene.Components.CameraComponent;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class SceneSetup
	{
	public:
		static void CreateTestScene(World& world);
		static Entity CreateEditorCamera(World& world, float aspectRatio);
	};
}