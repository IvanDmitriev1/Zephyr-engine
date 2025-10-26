#pragma once

#define EVENT_CLASS_TYPE(type) virtual constexpr EventType GetEventType() const override { return EventType::type; }\
								virtual constexpr std::string_view GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual constexpr int GetCategoryFlags() const override { return category; }