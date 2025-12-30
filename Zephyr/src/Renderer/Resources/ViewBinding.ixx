export module Zephyr.Renderer.Resources.ViewBinding;

export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Core.CoreTypes;
export import glm;

export namespace Zephyr::RHI
{
	struct ViewUniforms
	{
		glm::mat4 View{ 1.0f };
		glm::mat4 Projection{ 1.0f };
		glm::mat4 ViewProjection{ 1.0f };
		glm::vec4 CameraPosition{ 0.0f, 0.0f, 0.0f, 1.0f };
	};

	static_assert(sizeof(ViewUniforms) % 16 == 0, "ViewUniforms should be 16-byte sized/aligned for UBO safety.");

	struct ViewportDesc
	{
		float X = 0, Y = 0;
		float Width = 0, Height = 1;
		float MinDepth = 0, MaxDepth = 1;
	};

	struct ScissorDesc
	{
		int32_t X{ 0 }, Y{ 0 };
		uint32_t Width{ 0 }, Height{ 0 };
	};

	struct ViewBinding
	{
		ViewportDesc Viewport{};
		std::optional<ScissorDesc> ScissorRect{};
		Ref<IUniformBuffer> ViewUniformBuffer{};
	};
}