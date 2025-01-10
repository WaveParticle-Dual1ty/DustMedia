#pragma once

#ifdef _WIN32
#define ME_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define ME_PLATFORM_MACOS
#elif defined(__linux__)
#define ME_PLATFORM_LINUX
#error "Linux is not supported!"
#endif