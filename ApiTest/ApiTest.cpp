#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// NOTE: Write unit tests for C/C++ in Visual Studio https://docs.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp
//       Write the tests https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-microsoft-test-framework-for-cpp#write-the-tests
//       Microsoft.VisualStudio.TestTools.CppUnitTestFramework API reference https://docs.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference

#pragma region C++/WinRT Base

#include <winstring.h>
#include <roapi.h>

#include <unknwn.h>
#include <winrt\base.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

HMODULE g_Library;

using DllGetActivationFactory = HRESULT WINAPI(HSTRING activatableClassId, IActivationFactory** factory);
DllGetActivationFactory* g_LibraryGetActivationFactory;

#pragma comment(lib, "windowsapp.lib")
#pragma comment(lib, "runtimeobject.lib")

#pragma endregion

#include <shlwapi.h>
#include <winrt\Windows.Foundation.h>
#include "winrt\Api.h"

#pragma comment(lib, "shlwapi.lib")

namespace ApiTestNamespace
{
	TEST_CLASS(ApiTestClass)
	{
	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			Logger::WriteMessage(__FUNCTION__);
			//winrt::init_apartment();
			WCHAR Path[MAX_PATH];
			WINRT_VERIFY(GetModuleFileName(reinterpret_cast<HMODULE>(&__ImageBase), Path, static_cast<DWORD>(std::size(Path))));
			PathRemoveFileSpecW(Path);
			PathCombineW(Path, Path, L"Api.dll");
			WINRT_ASSERT(!g_Library);
			g_Library = LoadLibraryW(Path);
			WINRT_ASSERT(g_Library);
			g_LibraryGetActivationFactory = reinterpret_cast<DllGetActivationFactory*>(GetProcAddress(g_Library, "DllGetActivationFactory"));
			WINRT_ASSERT(g_LibraryGetActivationFactory);
		}
		TEST_CLASS_CLEANUP(Cleanup)
		{
			Logger::WriteMessage(__FUNCTION__);
			if(g_Library)
			{
				FreeLibrary(std::exchange(g_Library, nullptr));
				g_LibraryGetActivationFactory = nullptr;
			}
			//winrt::uninit_apartment();
		}
		ApiTestClass()
		{
			Logger::WriteMessage(__FUNCTION__);
		}
		~ApiTestClass()
		{
			Logger::WriteMessage(__FUNCTION__);
		}
		TEST_METHOD(Method)
		{
			winrt::Api::MyClass Instance;
			Assert::IsTrue(static_cast<std::wstring>(Instance.Text()).compare(L"MyClass::Text") == 0);
		}
		TEST_METHOD(ExceptionMethod)
		{
			winrt::Api::MyClass Instance;
			Assert::ExpectException<winrt::hresult_error>([&] () { Instance.ToString(); });
		}
	};
}
