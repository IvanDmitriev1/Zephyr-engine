export module Zephyr.Renderer.Renderables.Material;

export import Zephyr.Renderer.Types.MaterialTypes;

export namespace Zephyr
{
	class Material final
	{
	public:
		explicit Material(const MaterialDesc& desc);
		~Material() = default;

		inline std::string_view GetName() const noexcept { return m_Name; }
		inline const Ref<RHI::IShader>& GetShader() const noexcept { return m_Shader; }
		inline AlphaMode GetType() const noexcept { return m_Type; }
		inline const MaterialProperties& GetProperties() const noexcept { return m_Properties; }
		inline std::span<const RHI::ResourceBinding> GetBindings() const noexcept { return { m_Bindings.data(), m_Bindings.size() }; }

	private:
		std::string m_Name;
		Ref<RHI::IShader> m_Shader;
		AlphaMode m_Type;

		MaterialProperties m_Properties;
		std::vector<RHI::ResourceBinding> m_Bindings;
	};
}