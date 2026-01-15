module;

#include <windows.h>

module ZephyrEditor.Process;

namespace ZephyrEditor::Process
{
	static void TrimTrailingWhitespace(std::string& s)
	{
		while (!s.empty())
		{
			const unsigned char c = static_cast<unsigned char>(s.back());
			if (c == '\r' || c == '\n' || c == ' ' || c == '\t')
				s.pop_back();
			else
				break;
		}
	}

	static std::wstring QuoteArg(std::wstring_view arg)
	{
		const bool needsQuotes =
			arg.empty() || arg.find_first_of(L":") != std::wstring_view::npos;

		if (!needsQuotes)
			return std::wstring(arg);

		std::wstring out;
		out.reserve(arg.size() + 2);

		out.push_back(L'"');
		out.append(arg);
		out.push_back(L'"');

		return out;
	}

	static std::wstring BuildCommandLine(const std::filesystem::path& exe, std::span<const std::wstring> args)
	{
		std::wstring cmd = QuoteArg(exe.generic_wstring());

		for (auto& a : args)
		{
			cmd.push_back(L' ');
			cmd += QuoteArg(a);
		}

		return cmd;
	}

	std::expected<std::string, std::string> ZephyrEditor::Process::RunProcess(const ProcessDesc& desc)
	{
		if (desc.Executable.empty())
			return std::unexpected("RunProcess: Executable path is empty.");

		if (!std::filesystem::exists(desc.Executable))
			return std::unexpected("RunProcess: Executable does not exist: " + desc.Executable.string());

		SECURITY_ATTRIBUTES sa{};
		sa.nLength = sizeof(sa);
		sa.bInheritHandle = TRUE;

		HANDLE readPipe = nullptr;
		HANDLE writePipe = nullptr;

		if (!CreatePipe(&readPipe, &writePipe, &sa, 0))
			return std::unexpected("Failed to create pipe for command execution.");

		SetHandleInformation(readPipe, HANDLE_FLAG_INHERIT, 0);

		STARTUPINFOW si{};
		si.cb = sizeof(si);
		si.dwFlags |= STARTF_USESTDHANDLES;
		si.hStdOutput = writePipe;
		si.hStdError = writePipe;
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

		PROCESS_INFORMATION pi{};

		std::wstring cmdLine = BuildCommandLine(desc.Executable, desc.Args);
		const std::wstring wd = desc.WorkingDir.wstring();

		if (!CreateProcessW(
			nullptr,
			cmdLine.data(),
			nullptr, nullptr,
			TRUE, // child inherits writePipe
			CREATE_NO_WINDOW,
			nullptr,
			wd.c_str(),
			&si,
			&pi))
		{
			CloseHandle(readPipe);
			CloseHandle(writePipe);
			return std::unexpected("CreateProcessW failed for command.");
		}

		CloseHandle(writePipe);

		std::string output;
		std::array<char, 128> buffer{};
		DWORD bytesRead = 0;

		while (ReadFile(readPipe, buffer.data(), (DWORD)buffer.size(), &bytesRead, nullptr) && bytesRead > 0)
		{
			output.append(buffer.data(), buffer.data() + bytesRead);
		}

		WaitForSingleObject(pi.hProcess, INFINITE);

		DWORD exitCode = 1;
		GetExitCodeProcess(pi.hProcess, &exitCode);

		CloseHandle(readPipe);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		if (exitCode != 0)
		{
			return std::unexpected(output);
		}

		TrimTrailingWhitespace(output);
		return output;
	}
}