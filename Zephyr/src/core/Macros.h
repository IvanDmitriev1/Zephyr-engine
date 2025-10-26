#pragma once

#define BIT(x) (1 << (x))

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


#ifdef _DEBUG

	#ifdef Zephyr_PLATFORM_WINDOWS
		#define E_DEBUGBREAK() __debugbreak()
	#endif //Zephyr_PLATFORM_WINDOWS


	#define E_ASSERT(condition, message)										\
	{																			\
		if ( !(condition)  )													\
		{																		\
			E_DEBUGBREAK();														\
			throw std::runtime_error(message);									\
		}																		\
	}																			\

#else
	#define E_ASSERT(condition, message) static_cast<void>(condition)

#endif //_DEBUG

#define E_PASTE_IMPL(first, second) first##second
#define E_PASTE(first, second)		E_PASTE_IMPL(first, second)

