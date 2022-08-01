#pragma once

#if defined(PLATFORM_WINDOWS)
#include "sleeper_windows.h"
#elif defined(PLATFORM_UNIX)
#error Only Windows supported for now!
//#include "sleeper_unix.h"
#else
#error Only Windows and Unix supported for now!
#endif