export module Zephyr.Scene.Components.TransformComponent;

export import glm;

export namespace Zephyr
{
	struct TransformComponent
	{
		glm::vec3 Position{ 0.0f };
		glm::quat Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f };

		bool IsDirty = true;
	};

	struct TransformRuntimeComponent
	{
		glm::mat4 LocalToWorld{ 1.0f };
		glm::mat4 WorldToLocal{ 1.0f };
		glm::vec3 WorldPosition{ 0.0f };
	};
}