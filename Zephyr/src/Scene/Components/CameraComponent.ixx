export module Zephyr.Scene.Components.CameraComponent;

export import glm;

export namespace Zephyr
{
	struct CameraComponent
	{
		float Fov = 60.0f;
		float Near = 0.1f;
		float Far = 1000.0f;
		float AspectRatio = 16.0f / 9.0f;
	};

	struct CameraRuntimeComponent
	{
		glm::mat4 Projection{ 1.0f };
		glm::mat4 View{ 1.0f };
		glm::mat4 ViewProjection{ 1.0f };
		glm::vec3 Position{ 0.0f };
		glm::vec3 Forward{ 0.0f, 0.0f, -1.0f };
		glm::vec3 Up{ 0.0f, 1.0f, 0.0f };
		glm::vec3 Right{ 1.0f, 0.0f, 0.0f };
	};

	struct MainCameraTag {};
}