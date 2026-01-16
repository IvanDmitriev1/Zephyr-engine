export module Zephyr.Scene.Components.TransformComponent;

export import glm;

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
}