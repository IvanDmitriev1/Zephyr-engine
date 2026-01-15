export module ZephyrEditor.Process;

export import std.compat;

export namespace ZephyrEditor::Process
{
	struct ProcessDesc
	{
		std::filesystem::path Executable{};
		std::span<const std::wstring> Args{};
		std::filesystem::path WorkingDir{};
	};

	[[nodiscard]] std::expected<std::string, std::string>
		RunProcess(const ProcessDesc& desc);
}