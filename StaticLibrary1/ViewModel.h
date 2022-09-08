#pragma once

#include "ViewModel.g.h"

namespace winrt::StaticLibrary1::implementation
{
    struct ViewModel : ViewModelT<ViewModel>
    {
        ViewModel() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::StaticLibrary1::factory_implementation
{
    struct ViewModel : ViewModelT<ViewModel, implementation::ViewModel>
    {
    };
}
