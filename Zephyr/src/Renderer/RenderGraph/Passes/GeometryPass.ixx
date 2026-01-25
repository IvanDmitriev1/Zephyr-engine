export module Zephyr.Renderer.Passes.GeometryPass;

export import Zephyr.Renderer.BaseGeometryPass;

export namespace Zephyr
{
	class GeometryPass : public BaseGeometryPass
	{
		// Inherited via BaseGeometryPass
		inline std::string_view GetName() const noexcept override { return "Geometry"; }

		void Initialize() override {}
		void Execute(PassExecutionContext& ctx) override;
	};
}