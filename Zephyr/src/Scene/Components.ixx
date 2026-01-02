export module Zephyr.Scene.Components;

export import Zephyr.Scene.Entity;
export import Zephyr.Renderer.Renderables.Material;
export import Zephyr.Renderer.Renderables.Mesh;

export namespace Zephyr
{
	struct TransformComponent
	{
		glm::vec3 Position{ 0.0f };
		glm::quat Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f };

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Position)
				* glm::mat4_cast(Rotation)
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct MeshComponent
	{
		Ref<Mesh> MeshData;
		Ref<Material> MaterialInstance;
	};

	struct CameraComponent
	{
		glm::mat4 ViewMatrix{ 1.0f };
		glm::mat4 ProjectionMatrix{ 1.0f };
	};
}