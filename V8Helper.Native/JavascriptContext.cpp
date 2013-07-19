#include "stdafx.h"
#include "JavaScriptContext.h"

#if MACINTOSH
#include <MacUtil/MacUtil.h>
#endif

#if DEBUG
#include <iostream>
#endif

using namespace v8;

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
Handle<Value> Print(const Arguments& args)
{
#if DEBUG
	for (int i = 0; i < args.Length(); i++)
	{
		HandleScope handle_scope;
		if (i != 0)
			std::cerr << " ";

		String::Utf8Value str(args[i]);
		const char* cstr = *str != 0 ? *str : "string conversion failed";
		std::cerr << cstr;
	}
	std::cerr << std::endl;
#endif
	return Undefined();
}

JavaScriptContext::JavaScriptContext() : m_disposed(false)
{
	m_isolate = Isolate::New();
	Locker v8Locker(m_isolate);
	Isolate::Scope isolate_scope(m_isolate);
	HandleScope scope;
	Local<ObjectTemplate> globalTemplate = ObjectTemplate::New();
	globalTemplate->Set("print", FunctionTemplate::New(Print));
	m_ctx = new Persistent<Context>(Context::New(NULL, globalTemplate));
	Context::Scope contextScope(*m_ctx);
}

JavaScriptContext::~JavaScriptContext()
{
	{
		Locker locker(m_isolate);
		Isolate::Scope isolate_scope(m_isolate);
		m_ctx->Dispose();
		delete m_ctx;
	}
	if (m_isolate != NULL)
		m_isolate->Dispose();
}

stdext::ustring JavaScriptContext::ExecuteReturnString(const stdext::ustring & source, const stdext::ustring & name, stdext::ustring & error)
{
	stdext::ustring resultString;
	error = wstringToUstring(L"");
	Locker locker(m_isolate); 
	Isolate::Scope isolate_scope(m_isolate);
	{
		Context::Scope contextScope(*m_ctx);
		HandleScope scope;
		Local<String> scriptSource = String::New(reinterpret_cast<const uint16_t *>(source.c_str()));
		Local<String> scriptName = String::New(reinterpret_cast<const uint16_t *>(name.c_str()));
		Local<Script> script = Script::New(scriptSource, scriptName);
		Local<Value> result;
		{
			TryCatch tryCatch;
			result = script->Run();
			if (!result.IsEmpty())
			{
				String::Value value(result);
				resultString.append(reinterpret_cast<const char16_t *>(*value));
			}

			if (tryCatch.HasCaught())
			{
				error.append(wstringToUstring(L"Error running script: "));
				error.append(name);
				error.append(wstringToUstring(L" - "));
				String::Value stackTrace(tryCatch.StackTrace());
				error.append(reinterpret_cast<const char16_t*>(*stackTrace));
			}
		}
	}

	return resultString;
}

