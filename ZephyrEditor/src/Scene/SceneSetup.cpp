module ZephyrEditor.SceneSetup;

import ZephyrEditor.DemoSystem;

using namespace Zephyr;

namespace ZephyrEditor
{
	void SceneSetup::CreateTestScene(World& world)
	{
		// Load basic shader
		auto shader = ShaderLoader::LoadFromFile("Basic", "Assets/Shaders/Basic.glsl");

		// Create material
		MaterialDesc matDesc{
			.Name = "BasicMaterial",
			.Shader = shader,
			.Type = AlphaMode::Opaque,
			.Queue = RenderQueue::Geometry
		};
		auto material = CreateRef<Material>(matDesc);

		auto cubeMesh = GeometryGenerator::CreateCube(1);
		auto sphereMesh = GeometryGenerator::CreateSphere(2);

		Entity centerCube = world.CreateEntity();
		Entity sphere = world.CreateEntity();

		world.AddComponent(centerCube, TransformComponent{
			.Position = {0.0f, 0.f, 0.0f},
			.Scale = {1.5f, 1.5f, 1.5f},
						   });

		world.AddComponent(centerCube, MeshComponent{
			.MeshData = cubeMesh,
			.MaterialInstance = material
						   });

		world.AddComponent(centerCube, DemoComponent{});

		world.AddComponent(sphere, TransformComponent{
			.Position = {0.0f, 0.f, 0.0f},
			.Scale = {1.5f, 1.5f, 1.5f},
											 });

		world.AddComponent(sphere, MeshComponent{
			.MeshData = sphereMesh,
			.MaterialInstance = material
						   });

	}

	Entity SceneSetup::CreateEditorCamera(World& world, float aspectRatio)
	{
		Entity camera = world.CreateEntity();
		world.AddComponent(camera, TransformComponent{
						.Position = {8.0f, 5.0f, 8.0f},
						.Rotation = glm::quatLookAt(
							glm::normalize(glm::vec3(-1.0f, -0.5f, -1.0f)),
							glm::vec3(0.0f, 1.0f, 0.0f)
						)
						   });

		world.AddComponent(camera, CameraComponent{
			.Fov = 60.0f,
			.Near = 0.1f,
			.Far = 1000.0f,
			.AspectRatio = aspectRatio
						   });

		world.AddComponent(camera, MainCameraTag{});

		return camera;
	}
}