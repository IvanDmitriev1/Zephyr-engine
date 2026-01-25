export module Zephyr.Core.StringUnorderedMap;

import std;

export namespace Zephyr
{
	struct TransparentStringHash
	{
		using is_transparent = void;

		// Hash stored key type
		size_t operator()(std::string const& s) const noexcept
		{
			return std::hash<std::string_view>{}(std::string_view{ s });
		}

		// Hash lookup key type
		size_t operator()(std::string_view sv) const noexcept
		{
			return std::hash<std::string_view>{}(sv);
		}

		// Optional: allow const char* lookups too
		size_t operator()(char const* s) const noexcept
		{
			return std::hash<std::string_view>{}(std::string_view{ s });
		}
	};

	template<class T>
	using StringUnorderedMap =
		std::unordered_map<std::string, T, TransparentStringHash, std::equal_to<>>;
}