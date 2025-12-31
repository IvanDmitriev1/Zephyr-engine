export module Zephyr.Scene.Entity;

import std.compat;

export namespace Zephyr
{
	using EntityId = uint32_t;

	class Entity
	{
	private:
		EntityId Id{};
	};
}