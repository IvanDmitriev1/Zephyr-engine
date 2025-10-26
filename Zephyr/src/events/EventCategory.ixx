module;

#include "core/Macros.h"

export module zephyr.events.EventCategory;

export namespace zephyr
{
	enum EventCategory
	{
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
}