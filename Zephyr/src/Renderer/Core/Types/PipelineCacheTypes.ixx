export module Zephyr.Renderer.Types.PipelineCacheTypes;

import std;

export namespace Zephyr
{
	struct PipelineKey
	{
		size_t ShaderHash{};
		size_t ConfigHash{};

		bool operator==(const PipelineKey&) const = default;
	};
}

namespace std
{
	export template<>
	struct std::hash<Zephyr::PipelineKey>
	{
		size_t operator()(const Zephyr::PipelineKey& key) const noexcept
		{
			size_t h = key.ShaderHash;
			h ^= key.ConfigHash << 1;
			return h;
		}
	};
}
