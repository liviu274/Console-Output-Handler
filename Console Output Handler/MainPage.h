#pragma once

#include "MainPage.g.h"

// File open picker
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

// Win32 create process
#include <Windows.h>

// FileIO & StorageFile
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>

// CoreDispatcher
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>  // Include for DispatcherQueue

// Other
#include <iostream>
#include <string>
#include <sstream>


namespace winrt::Console_Output_Handler::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

       

        void pickFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void PickExecutableOrTextFile();
        void RunExecutableFile(LPCWSTR FILE_PATH);
        void ReadTextFile(winrt::Windows::Storage::StorageFile const& file);
        void DisplayFileName();
        void DisplayFileContent();

    private:

        LPCWSTR ConvertDWORDToLPCWSTR(DWORD value);
        hstring fileName;
        hstring fileContent;
    };
}

namespace winrt::Console_Output_Handler::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}


