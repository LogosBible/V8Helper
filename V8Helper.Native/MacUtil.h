#ifndef V8Helper_MacUtil_h
#define V8Helper_MacUtil_h
#include "stdafx.h"

stdext::ustring wstringToUstring(const std::wstring & string);

// char16_t equivalent of strdup
char16_t * wcsdup(const char16_t * str);

#endif
