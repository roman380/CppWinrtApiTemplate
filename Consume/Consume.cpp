#include <iostream>

#include <winstring.h>
#include <roapi.h>

#include <unknwn.h>
#include <winrt\base.h>

HMODULE g_Library;

using DllGetActivationFactory = HRESULT WINAPI(HSTRING activatableClassId, IActivationFactory** factory);
DllGetActivationFactory* g_LibraryGetActivationFactory;

#pragma comment(lib, "windowsapp.lib")
#pragma comment(lib, "runtimeobject.lib")

#include <winrt\Windows.Foundation.h>
#include "winrt\Api.h"

int main()
{
    winrt::init_apartment();
    g_Library = LoadLibraryW(L"Api.dll");
    g_LibraryGetActivationFactory = reinterpret_cast<DllGetActivationFactory*>(GetProcAddress(g_Library, "DllGetActivationFactory"));
    winrt::Api::MyClass Instance;
    std::wcout << Instance.Text().c_str() << std::endl;
    return 0;
}
