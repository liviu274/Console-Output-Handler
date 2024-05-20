#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;



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

    void MainPage::pickFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        pickFileButton().Content(box_value(L"clicked"));
        PickExecutableFile();

        for (const auto &filePath : myFilePaths)
            OutputDebugString((filePath + L"\n").c_str());
    }

    void MainPage::PickExecutableFile()
    {
        // Initialize the FileOpenPicker

        FileOpenPicker picker;
        picker.ViewMode(PickerViewMode::List);
        picker.SuggestedStartLocation(PickerLocationId::Desktop);
        picker.FileTypeFilter().Append(L".exe");

        // Show the picker and get the selected file
        picker.PickSingleFileAsync().Completed([this](IAsyncOperation<StorageFile> const& operation, AsyncStatus const status) {
            if (status == AsyncStatus::Completed)
            {
                StorageFile file = operation.GetResults();
                if (file)
                {
                    // Handle the selected file
                    myFilePaths.push_back(file.Path());
                    // Do something with the file path (e.g., display it, use it in your app, etc.)
                    OutputDebugString(file.Path().c_str());
                }
            }
            });
    }
}






