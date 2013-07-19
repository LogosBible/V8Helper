
using System;
using System.Runtime.InteropServices;

namespace V8Helper.NET
{
	internal sealed class SafeJavaScriptContextHandle : SafeHandle
	{
		public SafeJavaScriptContextHandle()
			: this(true)
		{
		}

		private SafeJavaScriptContextHandle(bool bOwnsHandle)
			: base(IntPtr.Zero, bOwnsHandle)
		{
		}

		public static SafeJavaScriptContextHandle Create()
		{
			return NativeMethods.JavaScriptContext_New();
		}

		public string ExecuteReturnString(string source, string name, out string error)
		{
			return NativeMethods.JavaScriptContext_ExecuteReturnString(this, source, name, out error);
		}

		protected override bool ReleaseHandle()
		{
			NativeMethods.JavaScriptContext_Delete(handle);
			return true;
		}

		public override bool IsInvalid
		{
			get { return handle == IntPtr.Zero; }
		}
	}

}
