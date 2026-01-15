module;

#include <rfl.hpp>

export module ZephyrEditor.ProjectTypes;

export import std.compat;

export namespace ZephyrEditor
{
	struct ProjectFile
	{
		uint32_t Version = 1;
		std::string Name{};

		std::filesystem::path BinDirectory{};
	};
}