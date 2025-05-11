#pragma once
#include "AddTeams.h"
#include "Scheduler.h"

namespace Hackathon {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            scheduler = new Scheduler(); // Initialize the Scheduler instance
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
            delete scheduler; // Clean up the Scheduler instance
        }

    private:
        Scheduler* scheduler; // Pointer to the Scheduler instance
        System::Windows::Forms::Label^ welcomeLabel;
        System::Windows::Forms::Label^ infoLabel;
        System::Windows::Forms::Button^ startButton;
        System::Windows::Forms::ToolTip^ buttonToolTip; // Tooltip for accessibility
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->welcomeLabel = (gcnew System::Windows::Forms::Label());
            this->infoLabel = (gcnew System::Windows::Forms::Label());
            this->startButton = (gcnew System::Windows::Forms::Button());
            this->buttonToolTip = (gcnew System::Windows::Forms::ToolTip());
            this->SuspendLayout();

            // Welcome Label
            this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26, System::Drawing::FontStyle::Bold));
            this->welcomeLabel->ForeColor = System::Drawing::Color::RoyalBlue;
            this->welcomeLabel->Text = L"\U0001F31F Welcome to Hackathon Scheduler!";
            this->welcomeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->welcomeLabel->Location = System::Drawing::Point(0, 40);
            this->welcomeLabel->Size = System::Drawing::Size(800, 70);

            // Info Label
            this->infoLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular));
            this->infoLabel->ForeColor = System::Drawing::Color::DimGray;
            this->infoLabel->Text = L"\u2728 Plan and manage cybersecurity hackathons seamlessly:\n"
                L"   \u2794 Organize matches dynamically\n"
                L"   \u2794 Simulate progress across rounds\n"
                L"   \u2794 Track match results with ease\n\n"
                L"Click the button below to begin!";
            this->infoLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->infoLabel->Location = System::Drawing::Point(0, 140);
            this->infoLabel->Size = System::Drawing::Size(800, 200);

            // Start Button
            this->startButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->startButton->FlatAppearance->BorderSize = 0;
            this->startButton->BackColor = System::Drawing::Color::DodgerBlue;
            this->startButton->ForeColor = System::Drawing::Color::White;
            this->startButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
            this->startButton->Location = System::Drawing::Point(300, 380);
            this->startButton->Size = System::Drawing::Size(200, 60);
            this->startButton->Text = L"Start \u2794";
            this->startButton->UseVisualStyleBackColor = false;
            this->startButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::startButton_MouseEnter);
            this->startButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::startButton_MouseLeave);
            this->startButton->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::startButton_Paint);
            this->startButton->Click += gcnew System::EventHandler(this, &MyForm::startButton_Click);

            // Tooltip
            this->buttonToolTip->SetToolTip(this->startButton, L"Click to start planning your hackathon!");

            // MyForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 500); // Fixed window size
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->BackColor = System::Drawing::Color::WhiteSmoke;
            this->Controls->Add(this->welcomeLabel);
            this->Controls->Add(this->infoLabel);
            this->Controls->Add(this->startButton);
            this->Name = L"MyForm";
            this->Text = L"Hackathon Scheduler";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->ResumeLayout(false);
        }

        void startButton_MouseEnter(System::Object^ sender, System::EventArgs^ e)
        {
            this->startButton->BackColor = System::Drawing::Color::MediumBlue; // Darker hover color
            this->startButton->ForeColor = System::Drawing::Color::LightGray; // Softer text color on hover
        }

        void startButton_MouseLeave(System::Object^ sender, System::EventArgs^ e)
        {
            this->startButton->BackColor = System::Drawing::Color::DodgerBlue; // Reset to original color
            this->startButton->ForeColor = System::Drawing::Color::White;      // Reset to original text color
        }

        void startButton_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
        {
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
            path->AddArc(0, 0, 20, 20, 180, 90);
            path->AddArc(this->startButton->Width - 20, 0, 20, 20, 270, 90);
            path->AddArc(this->startButton->Width - 20, this->startButton->Height - 20, 20, 20, 0, 90);
            path->AddArc(0, this->startButton->Height - 20, 20, 20, 90, 90);
            path->CloseFigure();
            this->startButton->Region = gcnew System::Drawing::Region(path);
        }

        void startButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            AddTeams^ addTeamsForm = gcnew AddTeams(scheduler);
            addTeamsForm->Show();
            this->Hide();
        }
    };
}