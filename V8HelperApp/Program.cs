using System;
using V8Helper.NET;

namespace V8HelperApp
{
	class Program
	{
		static void Main(string[] args)
		{
			using (var engine = new ScriptEngine())
			{
				string error;
				string results = engine.Evaluate("var four = 2 + 2; four", "add.js", out error);
				if (error.Length == 0)
					Console.WriteLine("Results:\n{0}", results);
				else
					Console.WriteLine("Error:\n{0}", error);
			}
		}
	}
}
