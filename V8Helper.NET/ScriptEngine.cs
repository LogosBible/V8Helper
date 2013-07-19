using System;

namespace V8Helper.NET
{
	public class ScriptEngine : IDisposable
	{
		public ScriptEngine()
		{
			m_context = SafeJavaScriptContextHandle.Create();
		}

		public void Execute(string script, string name, out string error)
		{
			Evaluate(script, name, out error);
		}

		public string Evaluate(string script, string name, out string error)
		{
			return m_context.ExecuteReturnString(script, name, out error);
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		protected virtual void Dispose(bool disposing)
		{
			if (disposing)
				m_context.Dispose();
		}

		readonly SafeJavaScriptContextHandle m_context;
	}
}
