module;

#include "events/HelpEventMacroses.h"

export module zephyr.events.ApplicationEvents;

export import zephyr.events.IEvent;

export namespace Zephyr
{
	class ApplicationEvent : public IEvent
	{
	protected:
		ApplicationEvent(uint32_t width, uint32_t height)
			: _width(width), _height(height) {}

	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)


		uint32_t GetWidth() const
		{
			return _width;
		}

		uint32_t GetHeight() const
		{
			return _height;
		}

	private:
		const uint32_t _width;
		const uint32_t _height;
	};


	class WindowClosingEvent final : public ApplicationEvent
	{
	public:
		WindowClosingEvent()
			:ApplicationEvent{ 0, 0 }
		{
		}

		EVENT_CLASS_TYPE(WINDOW_CLOSING_EVENT)
	};

	class WindowResizeEvent final : public ApplicationEvent
	{
	public:
		WindowResizeEvent(const uint32_t width, const uint32_t height)
			:ApplicationEvent{ width, height }
		{
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZE_EVENT)
	};
}