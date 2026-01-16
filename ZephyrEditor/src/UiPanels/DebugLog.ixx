export module zephyreditor.ui.DebugLog;

export import zephyr.logging.BufferedLogSink;
export import Zephyr.Core.CoreTypes;

import <imgui.h>;

export class DebugLog
{
public:
	DebugLog(Zephyr::LogBuffer& logBuffer);
	~DebugLog() = default;

public:
	void Draw();

	void Clear();
	void SetAutoScroll();

private:
	void DrawToolBar();
	void DrawLogs();
	constexpr ImU32 LogColor(Zephyr::LogLevel level);


private:
	Zephyr::LogBuffer& m_LogBuffer;
	Zephyr::Scope<ImGuiTextFilter> m_filter;
	bool m_AutoScroll = true;
};