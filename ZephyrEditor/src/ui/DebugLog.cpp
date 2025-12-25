module;

#include <imgui.h>

module zephyreditor.ui.DebugLog;

DebugLog::DebugLog(Zephyr::LogBuffer& logBuffer)
	:m_LogBuffer(logBuffer)
{

}

void DebugLog::Draw()
{
	ImGui::Begin("Debug log");


	DrawToolBar();
	ImGui::Separator();
	DrawLogs();

	ImGui::End();
}

void DebugLog::Clear()
{
	m_LogBuffer.Clear();
}

void DebugLog::SetAutoScroll()
{

}

void DebugLog::DrawToolBar()
{
	if (ImGui::Button("Clear"))
		Clear();

	ImGui::SameLine();

	if (ImGui::Button("Test"))
	{
		Zephyr::applog::Warn("Warning");
		Zephyr::applog::Error("Error");
		Zephyr::applog::Critical("Critical");
	}
}

void DebugLog::DrawLogs()
{
	ImGui::BeginChild("##scroll", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);

	const auto& logs = m_LogBuffer.GetView();

	ImGuiListClipper clipper;
	clipper.Begin(static_cast<int>(logs.size()));

	while (clipper.Step())
	{
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			const auto& log = logs[i];

			ImGui::PushStyleColor(ImGuiCol_Text, LogColor(log.Level));
			ImGui::TextUnformatted(log.Message.c_str());
			ImGui::PopStyleColor();
		}
	}

	if (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
	{
		ImGui::SetScrollHereY(1.0f);
	}

	ImGui::EndChild();
}

constexpr ImU32 DebugLog::LogColor(Zephyr::LogLevel level)
{
	switch (level)
	{
	case Zephyr::LogLevel::Trace:    return IM_COL32(160, 160, 160, 255);
	case Zephyr::LogLevel::Debug:    return IM_COL32(120, 180, 255, 255);
	case Zephyr::LogLevel::Info:     return IM_COL32_WHITE;
	case Zephyr::LogLevel::Warning:  return IM_COL32(255, 200, 80, 255);
	case Zephyr::LogLevel::Error:    return IM_COL32(255, 120, 120, 255);
	case Zephyr::LogLevel::Critical: return IM_COL32(255, 80, 80, 255);
	default:					     return IM_COL32_WHITE;
	}
}

