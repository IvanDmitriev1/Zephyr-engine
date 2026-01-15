module;

#ifdef ZEPHYR_PLATFORM_WINDOWS
	#include <windows.h>
#else
	#error "Unsupported platform"
#endif

module Zephyr.Core.GameModuleLoader;

import zephyr.logging.LogHelpers;

namespace Zephyr
{
	GameModuleLoader::GameModuleLoader(std::filesystem::path libraryPath)
		:m_LibraryPath(std::move(libraryPath))
	{
		
	}

	GameModuleLoader::~GameModuleLoader()
	{
		Unload();
	}

	bool GameModuleLoader::Load()
	{
		if (IsLoaded())
			return true;

#ifdef ZEPHYR_PLATFORM_WINDOWS
		m_LibraryHandle = LoadLibraryW(m_LibraryPath.c_str());
		if (!m_LibraryHandle)
		{
			log::Error("Failed to load game module library: {}", m_LibraryPath.string());
			return false;
		}

		m_CreateModule = reinterpret_cast<GameModuleSymbols::CreateModuleFunc>(GetProcAddress(static_cast<HMODULE>(m_LibraryHandle), GameModuleSymbols::kCreateName));
		m_DestroyModule = reinterpret_cast<GameModuleSymbols::DestroyModuleFunc>(GetProcAddress(static_cast<HMODULE>(m_LibraryHandle), GameModuleSymbols::kDestroyName));

		if (!m_CreateModule || !m_DestroyModule)
		{
			log::Error("Failed to load game module symbols from library: {}", m_LibraryPath.string());
			Unload();
			return false;
		}

		m_Module = m_CreateModule();
		if (!m_Module)
		{
			log::Error("Failed to create game module instance from library: {}", m_LibraryPath.string());
			Unload();
			return false;
		}

		m_Module->OnInit();
		return true;
#endif
	}

	void GameModuleLoader::Unload() noexcept
	{
		if (m_Module)
		{
			m_DestroyModule(m_Module);
			m_Module = nullptr;
		}

		if (m_LibraryHandle)
		{
#ifdef ZEPHYR_PLATFORM_WINDOWS
			FreeLibrary(static_cast<HMODULE>(m_LibraryHandle));
			m_LibraryHandle = nullptr;
#endif
		}
	}
	
}