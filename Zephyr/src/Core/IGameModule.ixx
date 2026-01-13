module;

#include "Macros.h"

export module Zephyr.Core.IGameModule;

export import Zephyr.Renderer.SceneRenderer;
export import zephyr.events.IEvent;

export namespace Zephyr
{
	class IGameModule
	{
	public:
		virtual ~IGameModule() = default;

		virtual void OnInit() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnRender(SceneRenderer& renderer) = 0;
		virtual void OnEvent(IEvent& event) {}
	};

	extern "C"
	{
		ZEPHYR_MODULE_API IGameModule* CreateGameModule();
		ZEPHYR_MODULE_API void DestroyGameModule(IGameModule* module);
	}
}

export namespace Zephyr::GameModuleSymbols
{
	using CreateModuleFunc = Zephyr::IGameModule* (*)();
	using DestroyModuleFunc = void (*)(Zephyr::IGameModule*);

	constexpr const char* kCreateName = "CreateGameModule";
	constexpr const char* kDestroyName = "DestroyGameModule";
}