﻿#include "pch.h"
#include "ViewModel.h"
#if __has_include("ViewModel.g.cpp")
#include "ViewModel.g.cpp"
#endif
//#include <winrt/VerifyMetadata.h>

namespace winrt::StaticLibrary1::implementation
{
    int32_t ViewModel::MyProperty()
    {
        return 42;
    }

    void ViewModel::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
