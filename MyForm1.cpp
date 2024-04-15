#include "MyForm1.h"

System::Void Project4::MyForm1::CloseButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    prev_page->Show();
    this->Close();
}

System::Void Project4::MyForm1::ShowSubject_Click(System::Object^ sender, System::EventArgs^ e)
{
    while (this->Screen->Rows->Count > 1)
    {
        for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
        {
            this->Screen->Rows->Remove(this->Screen->Rows[i]);
        }
    }
    
    int counter = 0;
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == SUBJECT)
            {
                this->Screen->Rows->Add();
                this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data);
                this->Screen->Rows[counter]->Cells[1]->Value = word.frequency;
                this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included);
            }
        }
   }
}

System::Void Project4::MyForm1::ShowPredicate_Click(System::Object^ sender, System::EventArgs^ e)
{
    while (this->Screen->Rows->Count > 1)
    {
        for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
        {
            this->Screen->Rows->Remove(this->Screen->Rows[i]);
        }
    }
    int counter = 0;
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == PREDICATE)
            {
                this->Screen->Rows->Add();
                this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data);
                this->Screen->Rows[counter]->Cells[1]->Value = word.frequency;
                this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included);
            }
        }
    }
}

System::Void Project4::MyForm1::ShowAttribute_Click(System::Object^ sender, System::EventArgs^ e)
{
    while (this->Screen->Rows->Count > 1)
    {
        for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
        {
            this->Screen->Rows->Remove(this->Screen->Rows[i]);
        }
    }
    int counter = 0;
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == DEFINITION)
            {
                this->Screen->Rows->Add();
                this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data);
                this->Screen->Rows[counter]->Cells[1]->Value = word.frequency;
                this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included);
            }
        }
    }
}

System::Void Project4::MyForm1::ShowObject_Click(System::Object^ sender, System::EventArgs^ e)
{
    while (this->Screen->Rows->Count > 1)
    {
        for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
        {
            this->Screen->Rows->Remove(this->Screen->Rows[i]);
        }
    }
    int counter = 0;
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == ADDITION)
            {
                this->Screen->Rows->Add();
                this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data);
                this->Screen->Rows[counter]->Cells[1]->Value = word.frequency;
                this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included);
            }
        }
    }
}

System::Void Project4::MyForm1::ShowAdverbialModifier_Click(System::Object^ sender, System::EventArgs^ e)
{
    while (this->Screen->Rows->Count > 1)
    {
        for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
        {
            this->Screen->Rows->Remove(this->Screen->Rows[i]);
        }
    }
    int counter = 0;
    for (const auto& sentence : sentences)
    {
        for (const auto& word : sentence)
        {
            if (word.type == CIRCUMSTANCE)
            {
                this->Screen->Rows->Add();
                this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data);
                this->Screen->Rows[counter]->Cells[1]->Value = word.frequency;
                this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included);
            }
        }
    }
}
