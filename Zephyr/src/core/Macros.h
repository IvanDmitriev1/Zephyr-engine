#pragma once

#define E_PASTE_IMPL(first, second) first##second
#define E_PASTE(first, second)		E_PASTE_IMPL(first, second)

