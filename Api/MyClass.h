#pragma once

#include "Projection\MyClass.g.h"

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
