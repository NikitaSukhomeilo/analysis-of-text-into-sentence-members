#include "MyForm1.h"

System::Void Project4::MyForm1::CloseButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    prev_page->Show();
    this->Close();
}

System::Void Project4::MyForm1::ShowSubject_Click(System::Object^ sender, System::EventArgs^ e)
{
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == SUBJECT)
            {
               // this->Screen->Rows->Add(word.data.c_str());
            }
        }
   }
}
