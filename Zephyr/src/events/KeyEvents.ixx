module;

#include "events/HelpEventMacroses.h"

export module zephyr.events.MouseEvents;

export import zephyr.events.IEvent;

export namespace zephyr
{
	using KeyCode = uint16_t;

	class KeyEvent : public IEvent
	{
	public:
		KeyCode GetKeyCode() const
		{
			return _keyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(const KeyCode keyCode)
			: _keyCode(keyCode)
		{
		}

		const KeyCode _keyCode;
	};


	class KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keyCode, const uint16_t repeatCount)
			:KeyEvent{ keyCode }, _repeatCount{ repeatCount }
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keyCode << " (" << _repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED_EVENT)

	private:
		uint16_t _repeatCount;
	};


	class KeyReleasedEvent  final : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED_EVENT)
	};
}