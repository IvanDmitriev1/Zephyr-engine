export module ZephyrEditor.ProjectManager;

export import ZephyrEditor.ProjectRuntime;
export import Zephyr.Core.GameModuleLoader;

import Zephyr.Core.CoreTypes;
import ZephyrEditor.IProjectBuilder;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class ProjectManager
	{
	public:
		using GameModuleReloadedCallback = std::function<void(IGameModule*)>;

		ProjectManager();
		~ProjectManager() = default;

	public:
		[[nodiscard]] bool HasProject() const noexcept { return m_Project.has_value(); }
		[[nodiscard]] const ProjectRuntime& GetProject() const;
		[[nodiscard]] IGameModule* GetLoadedGameModule() const noexcept;

		[[nodiscard]] std::expected<void, std::string> OpenProject(const std::filesystem::path& zprojPath);

		// Build steps
		[[nodiscard]] std::expected<void, std::string> GenerateProjectFiles();
		[[nodiscard]] std::expected<void, std::string> Build();
		[[nodiscard]] std::expected<void, std::string> Rebuild();

		//Hot reload
		void EnableHotReload(GameModuleReloadedCallback callback);
		void DisableHotReload();

	private:
		void CloseProject();

		[[nodiscard]] std::expected<void, std::string> LoadModuleFromDll(const std::filesystem::path& builtDll);
		void UnloadModule();

	private:
		Scope<IProjectBuilder> m_ProjectBuilder;

		Scope<GameModuleLoader> m_ModuleLoader;
		std::optional<ProjectRuntime> m_Project;
		GameModuleReloadedCallback m_ReloadedCallback;
	};
}