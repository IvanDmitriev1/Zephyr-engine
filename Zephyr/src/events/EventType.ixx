export module zephyr.events.EventType;

export import std.compat;

export namespace zephyr
{
	enum class EventType : uint8_t
	{
		MOUSE_MOVED_EVENT = 1,
		MOUSE_SCROLLED_EVENT,
		MOUSE_BUTTON_PRESSED_EVENT,
		MOUSE_BUTTON_RELEASED_EVENT,

		KEY_PRESSED_EVENT,
		KEY_RELEASED_EVENT,

		WINDOW_CLOSING_EVENT,
		WINDOW_RESIZE_EVENT
	};
}