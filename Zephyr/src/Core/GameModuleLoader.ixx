export module Zephyr.Core.GameModuleLoader;

export import Zephyr.Core.IGameModule;
export import std;

export namespace Zephyr
{
	class GameModuleLoader
	{
	public:
		explicit GameModuleLoader(std::filesystem::path libraryPath);
		~GameModuleLoader();

		GameModuleLoader(const GameModuleLoader&) = delete;
		GameModuleLoader& operator=(const GameModuleLoader&) = delete;

		GameModuleLoader(GameModuleLoader&& other) = delete;
		GameModuleLoader& operator=(GameModuleLoader&& other) = delete;

	public:
		bool Load();
		void Unload() noexcept;

		IGameModule* GetModule() const { return m_Module; }
		bool IsLoaded() const { return m_Module != nullptr; }

	private:
		std::filesystem::path m_LibraryPath;

		void* m_LibraryHandle = nullptr;
		IGameModule* m_Module = nullptr;
		GameModuleSymbols::CreateModuleFunc m_CreateModule = nullptr;
		GameModuleSymbols::DestroyModuleFunc m_DestroyModule = nullptr;
	};
}

