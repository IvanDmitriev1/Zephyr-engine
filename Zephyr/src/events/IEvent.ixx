export module zephyr.events.IEvent;

export import zephyr.events.EventType;
export import zephyr.events.EventCategory;

export namespace zephyr
{
	class IEvent
	{
	public:
		IEvent() = default;
		virtual ~IEvent() = default;

	public:
		inline virtual constexpr EventType GetEventType() const = 0;
		inline virtual constexpr std::string_view GetName() const = 0;
		inline virtual constexpr int GetCategoryFlags() const = 0;

		inline constexpr bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		virtual std::string ToString() const
		{
			return std::string{ GetName() };
		}
	};


	using EventCallbackFn = std::function<void(const IEvent&)>;
}