module;

#include "events/HelpEventMacroses.h"

export module zephyr.events.MouseEvents;

export import zephyr.events.IEvent;

export namespace Zephyr
{
	using MouseCode = uint16_t;

	enum class MouseWheelScroll
	{
		Unknown = 0,
		Up,
		Down
	};


	class MouseMovedEvent final : public IEvent
	{
	public:
		MouseMovedEvent(const float x, const float y)
			:_mouseX(x), _mouseY(y)
		{
		}

		float GetX() const
		{
			return _mouseX;
		}
		float GetY() const
		{
			return  _mouseY;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_MOVED_EVENT)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		const float _mouseX, _mouseY;
	};


	class MouseScrolledEvent final : public IEvent
	{
	public:
		MouseScrolledEvent(const MouseWheelScroll mouseScroll)
			: _mouseScroll(mouseScroll)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: ";

			switch (_mouseScroll)
			{
			case MouseWheelScroll::Down:
				ss << "Down";
				break;

			case MouseWheelScroll::Up:
				ss << "Up";
				break;

			case MouseWheelScroll::Unknown:
				ss << "Unknown direction";
				break;
			}

			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLLED_EVENT)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		const MouseWheelScroll _mouseScroll;
	};


	class MouseButtonEvent : public IEvent
	{
	public:
		const MouseCode GetMouseButton() const
		{
			return _button;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const MouseCode mouseCode)
			: _button(mouseCode)
		{
		}

		const MouseCode _button;
	};

	class MouseButtonPressedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << _button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED_EVENT)
	};


	class MouseButtonReleasedEvent final : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << _button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED_EVENT)
	};
}