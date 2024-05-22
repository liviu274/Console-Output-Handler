#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


// File open picker
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;



namespace winrt::Console_Output_Handler::implementation
{
    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    LPCWSTR MainPage::ConvertDWORDToLPCWSTR(DWORD value)   // Private function used for OutpputDeebug error logs
    {
        std::wstringstream wss;
        wss << value;
        return wss.str().c_str();
    }

    void MainPage::pickFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        PickExecutableOrTextFile();
    }

    void MainPage::loadFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        fileContentTextBlock_SelectionChanged(sender, e);
    }

    void MainPage::PickExecutableOrTextFile()
    {
        // Initialize the FileOpenPicker

        FileOpenPicker picker;
        picker.ViewMode(PickerViewMode::List);
        picker.SuggestedStartLocation(PickerLocationId::Desktop);
        picker.FileTypeFilter().Append(L".exe");
        picker.FileTypeFilter().Append(L".txt");

        // Show the picker and get the selected file
        picker.PickSingleFileAsync().Completed([this](IAsyncOperation<StorageFile> const& operation, AsyncStatus const status) {
            if (status == AsyncStatus::Completed)
            {
                StorageFile file = operation.GetResults();
                if (file)
                {
                    // Handle the selected file
                    
                    // Output the file for debuging purposes
                    OutputDebugString((L"FILE PATH: " + file.Path() + L"\n").c_str());

                    //Execute file from path
                    if (file.FileType() == L".exe")
                        RunExecutableFile(file.Path().c_str());
                    else if (file.FileType() == L".txt")
                        ReadTextFile(file);
                    else
                        OutputDebugString(L"ERROR FILE TYPE NOT SUPPORTED");
 
                }
                
            }
            });
        
    }

    void MainPage::RunExecutableFile(LPCWSTR FILE_PATH)
    {
        // Prepare to start the selected executable
        STARTUPINFO startupInfo = { sizeof(startupInfo) };
        PROCESS_INFORMATION processInfo;

        // ZeroMemory is not strictly necessary but ensures fields are initialized to zero
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&processInfo, sizeof(processInfo));

        // Start the process
        if (CreateProcess(
            FILE_PATH,                  // Path of the .exe file
            nullptr,                   // Command line
            nullptr,                   // Process handle not inheritable
            nullptr,                   // Thread handle not inheritable
            FALSE,                     // Set handle inheritance to FALSE
            0,                         // No creation flags
            nullptr,                   // Use parent's environment block
            nullptr,                   // Use parent's starting directory
            &startupInfo,              // Pointer to STARTUPINFO structure
            &processInfo               // Pointer to PROCESS_INFORMATION structure
        ))
        {
            // Successfully created the process
            // Close process and thread handles
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
        }
        else
        {
            // Failed to create the process, handle error
            OutputDebugString(L"Exited with error code - ");
            OutputDebugString(ConvertDWORDToLPCWSTR(GetLastError()));  // Return error code
            OutputDebugString(L"\n");
        }
    }

    void MainPage::ReadTextFile(winrt::Windows::Storage::StorageFile const& file)
    {
        

        FileIO::ReadTextAsync(file).Completed([this, file](IAsyncOperation<hstring> const& readOperation, AsyncStatus const readStatus) {
            if (readStatus == AsyncStatus::Completed)
            {
                this->fileContent = readOperation.GetResults();
                this->fileName = file.DisplayName();
                OutputDebugString(fileContent.c_str());  // for debug puposes
                
            }
            else
            {
                OutputDebugString(L"Failed to read the text file.\n");
            }
            });

        
    }

    void MainPage::fileContentTextBlock_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        fileContentTextBlock().Text(this->fileContent);
    }

}







void winrt::Console_Output_Handler::implementation::MainPage::ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e)
{

}
