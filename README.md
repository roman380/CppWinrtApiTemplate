# C++/WinRT API Template

This repository hosts a template Visual Studio 2019 solution to author API in C++/WinRT as described in the following MSDN article: [Author APIs with C++/WinRT](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/author-apis).

The `Api` project is a DLL library project which includes a [WinRT IDL definition](Api/Api.idl) (see [Introduction to Microsoft Interface Definition Language 3.0](https://docs.microsoft.com/en-us/uwp/midl-3/intro)) which is compiled as a part of build process and a custom step generates module a implementation source code files to link the project into WinRT component library. The project produces .DLL code and .WINMD metadata output.

`Consume` project is straightforward consumption project in C++/WinRT which is consuming the API using a hook in activation factory lookup. The activation factory is loaded from a side loaded API library.

`SharpConsume` project is a standard .NET Framework console application project referencing WinRT component and importing API definitions from metadata.

## Miscellaneous

As of now the template is minimalistic and is used with:

- Visual Studio 2022
- Windows 10/11 SDK 10.0.26000
- C++/WinRT shipped with Windows 10/11 SDK
- x64 platform

It is assumed that the project is generally compatible with Win32 and ARM, ARM64 platforms too.

### Known Issues

With SDK .26000 `cppwinrt` does not seem to generate the projection automatically as a part of Custom Build Step.

One native prompt and execute with placeholders expanded:

```
cppwinrt.exe -in "$(TargetDir)$(TargetName).winmd" -reference "$(WindowsSDK_UnionMetadataPath)\Windows.winmd" -comp "$(ProjectDir)Component" -out "$(ProjectDir)Projection"
```

This will create the projection files and the code will be buidlable from there.
