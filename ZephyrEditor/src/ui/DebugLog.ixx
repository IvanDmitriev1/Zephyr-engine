export module zephyreditor.ui.DebugLog;

export import zephyr.logging.BufferedLogSink;
export import zephyr.core.coreTypes;

import <imgui.h>;

export class DebugLog
{
public:
	DebugLog(zephyr::LogBuffer& logBuffer);
	~DebugLog() = default;

public:
	void Draw();

	void Clear();
	void SetAutoScroll();

private:
	void DrawToolBar();
	void DrawLogs();
	constexpr ImU32 LogColor(zephyr::LogLevel level);


private:
	zephyr::LogBuffer& m_LogBuffer;
	zephyr::Scope<ImGuiTextFilter> m_filter;
	bool m_AutoScroll = true;
};