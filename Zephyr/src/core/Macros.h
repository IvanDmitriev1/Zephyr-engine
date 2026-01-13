#pragma once

#define E_PASTE_IMPL(first, second) first##second
#define E_PASTE(first, second)		E_PASTE_IMPL(first, second)


#if defined(ZEPHYR_PLATFORM_WINDOWS)
	#if defined(ZEPHYR_MODULE_BUILD)
		#define ZEPHYR_MODULE_API __declspec(dllexport)
	#else
		#define ZEPHYR_MODULE_API __declspec(dllimport)
	#endif
	#else
		#define ZEPHYR_MODULE_API
#endif