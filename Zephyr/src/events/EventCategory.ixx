export module zephyr.events.EventCategory;

import zephyr.core.coreTypes;

export namespace zephyr
{
	enum EventCategory
	{
		EventCategoryApplication = bit(0),
		EventCategoryInput = bit(1),
		EventCategoryKeyboard = bit(2),
		EventCategoryMouse = bit(3),
		EventCategoryMouseButton = bit(4)
	};
}