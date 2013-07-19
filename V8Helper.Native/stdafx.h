// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef MACINTOSH
// ignore VC10-provided char16_t type for compatibility with old code.
#define _CHAR16T
typedef wchar_t char16_t;
typedef unsigned int char32_t;

#if defined(_DEBUG) && !defined(ALLOW_CDECL_CALLCONV)
#define ALLOW_CDECL_CALLCONV
#endif

#define DllExport __declspec(dllexport)

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <OleAuto.h>
#include "targetver.h"
#else
#include <wchar.h>
#endif

#include "v8.h"

#include <string>

#ifdef MACINTOSH
#ifndef HAS_CHAR16_T
typedef uint16_t char16_t;
#endif
namespace stdext {
	typedef std::basic_string<char16_t> ustring;
}
//
//#define WIDE_TO_USTRING(s) utf32ToUstring(s)
//
//#define U16(x) static_cast<char16_t>(x)

#else

namespace stdext {
	typedef std::wstring ustring;
}
#define wstringToUstring(strWstring) (strWstring)
#endif
