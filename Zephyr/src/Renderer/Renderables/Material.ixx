export module Zephyr.Renderer.Renderables.Material;

export import Zephyr.Renderer.Core.IPipeline;
export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Renderer.Core.ITexture;
export import glm;

export namespace Zephyr
{
	struct MaterialCreateDesc
	{
		std::string Name{};
		Ref<RHI::IPipeline> Pipeline{};
	};

	class Material final
	{
	public:
		Material(const MaterialCreateDesc& desc)
			:m_Name(std::move(desc.Name)),
			m_Pipeline(std::move(desc.Pipeline))
		{

		}

		~Material() = default;

		std::string_view GetName() const noexcept { return m_Name; }
		const Ref<Zephyr::RHI::IPipeline>& GetPipeline() const noexcept { return m_Pipeline; }
		//const Ref<Zephyr::RHI::IBuffer>& GetParams() const noexcept { return m_Params; }

	private:
		std::string m_Name;

		Ref<RHI::IPipeline> m_Pipeline;
		//Ref<RHI::IBuffer> m_Params;
	};
}