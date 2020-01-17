// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX						// No min and max macros
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <string_view>
#include <filesystem>

#if defined(_WIN32)
#include <Windows.h>
#endif

#define CXXTEST_HAVE_EH
#define CXXTEST_HAVE_STD
#define CXXTEST_ABORT_TEST_ON_FAIL

#include <cxxtest/TestSuite.h>
