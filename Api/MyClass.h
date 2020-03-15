#pragma once

#include "Projection\MyClass.g.h"

// NOTE: See Author APIs with C++/WinRT https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/author-apis

namespace winrt::Api::implementation
{
    struct MyClass : MyClassT<MyClass>
    {
        MyClass() = default;

    // IMyClass
        hstring Text()
        {
            return L"MyClass::Text";
        }

    // Windows.Foundation.IStringable
        hstring ToString()
        {
            throw hresult_not_implemented(L"MyClass::ToString");
        }
    };
}

namespace winrt::Api::factory_implementation
{
    struct MyClass : MyClassT<MyClass, implementation::MyClass>
    {
    };
}
