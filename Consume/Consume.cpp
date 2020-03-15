#include <iostream>

#include <winstring.h>
#include <roapi.h>

extern "C" HRESULT __stdcall OS_RoGetActivationFactory(HSTRING classId, GUID const& iid, void** factory) noexcept;

#ifdef _M_IX86
    #pragma comment(linker, "/alternatename:_OS_RoGetActivationFactory@12=_RoGetActivationFactory@12")
#else
    #pragma comment(linker, "/alternatename:OS_RoGetActivationFactory=RoGetActivationFactory")
#endif

#include <unknwn.h>
#include <winrt\base.h>

HMODULE g_Library;

using DllGetActivationFactory = HRESULT WINAPI(HSTRING activatableClassId, IActivationFactory** factory);
DllGetActivationFactory* g_LibraryGetActivationFactory;

int32_t WINRT_CALL WINRT_RoGetActivationFactory(void* ClassIdentifier, winrt::guid const& InterfaceIdentifier, void** ActivationFactory) noexcept
{
    WINRT_ASSERT(ActivationFactory);
    *ActivationFactory = nullptr;
    winrt::com_ptr<IActivationFactory> LocalActivationFactory;
    HRESULT const Result = g_LibraryGetActivationFactory(reinterpret_cast<HSTRING>(ClassIdentifier), LocalActivationFactory.put());
    if(FAILED(Result))
        return OS_RoGetActivationFactory(reinterpret_cast<HSTRING>(ClassIdentifier), InterfaceIdentifier, ActivationFactory);
    if(InterfaceIdentifier != winrt::guid_of<IActivationFactory>())
        return LocalActivationFactory->QueryInterface(InterfaceIdentifier, ActivationFactory);
    *ActivationFactory = LocalActivationFactory.detach();
    return S_OK;
}

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
}
