#pragma once

#define BIT(x) (1 << (x))

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


#define E_PASTE_IMPL(first, second) first##second
#define E_PASTE(first, second)		E_PASTE_IMPL(first, second)

