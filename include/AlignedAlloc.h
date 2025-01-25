#pragma once

#ifdef _MSC_VER
#include <malloc.h>
#include <Windows.h>
#else
#include <stdlib.h>
#include <unistd.h>
#endif

#include "maybe_unused.h"

FRAMEWORK_MAYBE_UNUSED
static size_t framework_getpagesize()
{
#if defined(_MSC_VER)
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
#elif defined(__SWITCH__)
	return 4096;
#else
	return sysconf(_SC_PAGESIZE);
#endif
}

FRAMEWORK_MAYBE_UNUSED
static void* framework_aligned_alloc(size_t allocSize, size_t alignment)
{
#if defined(_MSC_VER)
	return _aligned_malloc(allocSize, alignment);
#elif defined(__ANDROID__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__linux__) || defined(__EMSCRIPTEN__)
	void* result = nullptr;
	if(posix_memalign(&result, alignment, allocSize) != 0)
	{
		return nullptr;
	}
	return result;
#else
	return malloc(allocSize);
#endif
}

FRAMEWORK_MAYBE_UNUSED
static void framework_aligned_free(void* ptr)
{
#if defined(_MSC_VER)
	_aligned_free(ptr);
#else
	free(ptr);
#endif
}
