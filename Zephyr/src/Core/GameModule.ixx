export module Zephyr.Core.GameModule;

export import Zephyr.Core.IGameModule;
export import std;

export namespace Zephyr
{
	class GameModule
	{
	public:
		explicit GameModule(std::filesystem::path libraryPath);
		~GameModule();

		GameModule(const GameModule&) = delete;
		GameModule& operator=(const GameModule&) = delete;

		GameModule(GameModule&& other) = delete;
		GameModule& operator=(GameModule&& other) = delete;

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

