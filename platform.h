#pragma once

#define PLATFORM_WIN 1
#define PLATFORM_OTHER 2
#define PLATFORM_ANDROID 3

#if defined(__WIN32__) || defined(_WIN32) || defined(_WINDOWS) || defined(WIN) || defined(_WIN64) || defined(__WIN64__)
#define PLATFORM PLATFORM_WIN
#elif defined(__ANDROID__)
#define PLATFORM PLATFORM_ANDROID
#else
#define PLATFORM PLATFORM_OTHER
#endif

#if PLATFORM == PLATFORM_WIN
#define EXPORT extern "C" __declspec(dllexport)
#elif PLATFORM == PLATFORM_ANDROID
#define EXPORT extern "C" __attribute ((visibility("default")))
#elif PLATFORM == PLATFORM_OTHER
#define EXPORT extern "C" __attribute ((visibility("default")))
#endif
