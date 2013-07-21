#include "stdafx.h"
#include "JavascriptContext.h"

#ifdef MACINTOSH
#include "MacUtil.h"
#endif

extern "C"
{

#ifndef MACINTOSH

__declspec(dllexport) JavaScriptContext * __cdecl JavaScriptContext_New()
{
	return new JavaScriptContext();
}

__declspec(dllexport) BSTR __cdecl JavaScriptContext_ExecuteReturnString(JavaScriptContext * p, const char16_t * source, const char16_t * name, BSTR * error)
{
	const stdext::ustring str_source(source);
	const stdext::ustring str_name(name);
	stdext::ustring str_error;
	stdext::ustring retval = p->ExecuteReturnString(str_source, str_name, str_error);
	*error = ::SysAllocStringLen(str_error.data(), str_error.length());
	return ::SysAllocStringLen(retval.data(), retval.length());
}

__declspec(dllexport) void __cdecl JavaScriptContext_Delete(JavaScriptContext * p)
{
	delete p;
}

#else

JavaScriptContext * JavaScriptContext_New()
{
	return new JavaScriptContext();
}

const char16_t * JavaScriptContext_ExecuteReturnString(JavaScriptContext * p, char16_t * source, char16_t * name, char16_t ** error)
{
	stdext::ustring str_source(source);
	stdext::ustring str_name(name);
	stdext::ustring str_error;
	stdext::ustring retval = p->ExecuteReturnString(str_source, str_name, str_error);
	*error = wcsdup(str_error.c_str());
	return wcsdup(retval.c_str());
}

void JavaScriptContext_Delete(JavaScriptContext * p)
{
	delete p;
}

#endif

}