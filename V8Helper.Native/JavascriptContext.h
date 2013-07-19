#ifndef _PERSISTENT_CONTEXT_H_
#define _PERSISTENT_CONTEXT_H_

#ifdef WINDOWS
// Allow other projects, such as test projects to export internal functions by defining
// V8HELPER_EXPORT as necessary
#ifdef V8HELPER_EXPORTS
#define V8HELPER_API __declspec(dllexport)
#else
#define V8HELPER_API __declspec(dllimport)
#endif
#endif

#ifdef MACINTOSH
#define V8HELPER_API __attribute__ ((visibility("default")))
#endif

#include "stdafx.h"
#include "v8.h"

class JavaScriptContext
{
private:
	bool m_disposed;
	v8::Persistent<v8::Context> *m_ctx;
	v8::Isolate *m_isolate;

public:
	V8HELPER_API JavaScriptContext();
	V8HELPER_API virtual ~JavaScriptContext();
	V8HELPER_API stdext::ustring ExecuteReturnString(const stdext::ustring & source, const stdext::ustring & name, stdext::ustring & error);
};

#endif
