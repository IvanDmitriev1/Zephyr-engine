export module ZephyrEditor.IGameModuleLoader;

export import Zephyr.Core.IGameModule;

export namespace ZephyrEditor
{
	class IGameModuleLoader
	{
	public:
		virtual ~IGameModuleLoader() = default;

		virtual Zephyr::IGameModule* CreateModule() = 0;
		virtual void DestroyModule() = 0;
	};
}