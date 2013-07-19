using System;
using System.Runtime.ConstrainedExecution;
using System.Runtime.InteropServices;

namespace V8Helper.NET
{
	/// <summary>
	/// The <see cref="SafeHandleZeroIsInvalid"/> class provides a base class for safe handles that represent
	/// native pointers.
	/// </summary>
	public abstract class SafeHandleZeroIsInvalid : SafeHandle
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SafeHandleZeroIsInvalid"/> class.
		/// </summary>
		/// <param name="ownsHandle"><b>true</b> to reliably let <see cref="SafeHandle"/> release the handle
		/// during the finalization phase; otherwise, <b>false</b> (not recommended).</param>
		[ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
		protected SafeHandleZeroIsInvalid(bool ownsHandle)
			: base(IntPtr.Zero, ownsHandle)
		{
		}

		/// <summary>
		/// Gets a value indicating whether the handle value is invalid.
		/// </summary>
		/// <returns>true if the handle value is invalid; otherwise, false.</returns>
		public override bool IsInvalid
		{
			get { return handle == IntPtr.Zero; }
		}
	}
}
