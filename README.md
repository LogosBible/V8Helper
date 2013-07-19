V8Helper
========

A simple cross-platform .NET project for embedding V8 that works on Windows and Mac (32-bit only for now).

V8Helper has a simple API that allows a JavaScript script to be run in V8 and the results or error returned back to the calling .NET code as strings. JavaScript to .NET object marshalling is handled via JSON strings using either the built in JSON apis in V8 or JSON.NET in C#

V8Helper currently includes 32-bit shared libraries of V8 built for Windows and MacOSX (10.6+).

Build Instructions
==================

Windows
--------
1. Open V8Helper.sln in Visual Studio 2012
2. Build.
3. Run V8HelperDemo.exe from the build products directory

Mac
---
1. Open V8Helper-Mac.sln in MonoDevelop.
2. Build.
3. Run "mono V8HelperDemo.exe" from the build products directory


Future Plans
============
- NuGet package
- 64-bit support
- Build v8 as a shared library from a git submodule

Prerequistes
============
- Windows: Visual Studio 2012
- Mac: MonoDevelop, Xcode, Xcode Command Line Tools
