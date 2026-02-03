export module Zephyr.Renderer.Resources.PipelineCache;

export import Zephyr.Renderer.RHI.Interfaces.IPipeline;
import Zephyr.Renderer.Types.PipelineCacheTypes;
import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
import Zephyr.Renderer.Resources.Material;
import Zephyr.Renderer.RHI.Interfaces.Device;
import Zephyr.Core.CoreTypes;
import std;

export namespace Zephyr
{
	template <class T>
	concept GraphicsPipelineConfigurator =
		std::invocable<T, RHI::GraphicsPipelineDesc&>;

	class PipelineCache final
	{
	public:
		static PipelineCache& Get()
		{
			static PipelineCache instance;
			return instance;
		}

		PipelineCache(const PipelineCache&) = delete;
		PipelineCache& operator=(const PipelineCache&) = delete;
		PipelineCache(PipelineCache&&) = delete;
		PipelineCache& operator=(PipelineCache&&) = delete;

	public:
		template<GraphicsPipelineConfigurator ConfigFn>
		Ref<RHI::IPipeline> GetOrCreate(
			const Material& material,
			const Ref<RHI::IFrameBuffer>& target,
			ConfigFn&& configurator);

		void Clear();
		void ClearShader(const RHI::IShader* shader);

	private:
		PipelineCache() = default;
		~PipelineCache() = default;

		static RHI::GraphicsPipelineDesc BuildDesc(const Material& material, const Ref<RHI::IFrameBuffer>& target) noexcept;
		static void ApplyMaterialDefaults(RHI::GraphicsPipelineDesc& desc, const Material& material) noexcept;
		static size_t HashPipelineDesc(const RHI::GraphicsPipelineDesc& desc) noexcept;

	private:
		std::unordered_map<PipelineKey, Ref<RHI::IPipeline>> m_Cache;
	};

	template<GraphicsPipelineConfigurator ConfigFn>
	Ref<RHI::IPipeline> PipelineCache::GetOrCreate(const Material& material, const Ref<RHI::IFrameBuffer>& target, ConfigFn&& configurator)
	{
		auto desc = BuildDesc(material, target);
		std::invoke(std::forward<ConfigFn>(configurator), desc);

		const PipelineKey key = PipelineKey{
			.ShaderHash = desc.Shader->GetHash(),
			.ConfigHash = HashPipelineDesc(desc)};

		auto [it, inserted] = m_Cache.try_emplace(key, Ref<RHI::IPipeline>{});
		if (inserted)
		{
			it->second = RHI::Device::CreatePipeline(desc);
		}
		return it->second;
	}
}
