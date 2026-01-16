module;

#include "Core/Macros.h"

export module Sandbox.Module;

import Zephyr.Core.IGameModule;
import Zephyr.Renderer.Renderer;

using namespace Zephyr;

export class SandboxModule final : public Zephyr::IGameModule
{
	void OnInit() override
	{
	}

	void OnUpdate(float deltaTime) override
	{
		
	}

	void OnRender() override
	{
		
	}

	void OnEvent(IEvent& event) override
	{
		
	}
};

export extern "C"
{
	ZEPHYR_MODULE_API Zephyr::IGameModule* CreateGameModule()
	{
		return new SandboxModule();
	}

	ZEPHYR_MODULE_API void DestroyGameModule(Zephyr::IGameModule* module)
	{
		delete module;
	}
}