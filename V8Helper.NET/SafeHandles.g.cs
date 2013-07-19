
// This file was automatically generated by GenerateInterface v5.99.0.0 at 2013-07-17T22:28:09Z.
// DO NOT MODIFY.

using System.Runtime.CompilerServices;

namespace V8Helper.NET
{
	[CompilerGenerated]
	internal sealed class SafeJavaScriptContextHandle : SafeHandleZeroIsInvalid
	{
		public SafeJavaScriptContextHandle()
			: this(true)
		{
		}

		private SafeJavaScriptContextHandle(bool bOwnsHandle)
			: base(bOwnsHandle)
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
	}

}
