#pragma once
#include "Scheduler.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <thread>
#include <chrono>

namespace Hackathon {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ManageRounds : public Form {
    private:
        Form^ AddTeams;
        Scheduler* scheduler; // Pointer to the shared Scheduler instance

    protected:
        virtual void OnShown(EventArgs^ e) override {
            Form::OnShown(e);
            ResetFormState();
        }

    private:
        void ResetFormState() {
            this->roundsGridView->Rows->Clear();
            this->simulationProgressListBox->Items->Clear();
            scheduler->reset(); // Assuming you have a reset method in your Scheduler class
        }

        // GUI Components
        Label^ formTitle;
        DataGridView^ roundsGridView;
        Button^ scheduleRoundButton;
        Button^ simulateRoundButton;
        Button^ backButton;
        ListBox^ simulationProgressListBox;
        Label^ winnerLabel; // Add this line

        // Background worker for simulating the round
        System::ComponentModel::BackgroundWorker^ simulationWorker;

        void InitializeComponent(void) {
            // Initialize BackgroundWorker
            simulationWorker = gcnew System::ComponentModel::BackgroundWorker();
            simulationWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ManageRounds::OnSimulateRoundWorker);
            simulationWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ManageRounds::OnSimulationProgress);
            simulationWorker->WorkerReportsProgress = true;

            // Form properties
            this->Text = L"Manage Rounds";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Size = Drawing::Size(950, 750); // Increased height
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackColor = Color::FromArgb(240, 240, 240);
            this->MaximizeBox = false;

            // Title Label
            this->formTitle = gcnew Label();
            this->formTitle->Text = L"🏆 Manage Rounds";
            this->formTitle->Font = gcnew Drawing::Font("Segoe UI", 28, FontStyle::Bold);
            this->formTitle->ForeColor = Color::RoyalBlue;
            this->formTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->formTitle->Location = Point(10, 10);
            this->formTitle->Size = Drawing::Size(900, 60);
            this->Controls->Add(this->formTitle);

            // Rounds DataGridView
            this->roundsGridView = gcnew DataGridView();
            this->roundsGridView->Font = gcnew Drawing::Font("Segoe UI", 12);
            this->roundsGridView->Location = Point(30, 80);
            this->roundsGridView->Size = Drawing::Size(880, 300);
            this->roundsGridView->BackgroundColor = Color::White;
            this->roundsGridView->BorderStyle = BorderStyle::FixedSingle;
            this->roundsGridView->ColumnHeadersHeight = 40;
            this->roundsGridView->AllowUserToAddRows = false;
            this->roundsGridView->RowHeadersVisible = false;
            this->roundsGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->roundsGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // Add columns to DataGridView
            this->roundsGridView->Columns->Add(L"RoundName", L"Round Name");
            this->roundsGridView->Columns->Add(L"Team1", L"Team 1");
            this->roundsGridView->Columns->Add(L"Team2", L"Team 2");
            this->roundsGridView->Columns->Add(L"DateTime", L"Date & Time");
            this->roundsGridView->Columns->Add(L"Status", L"Status");
            this->roundsGridView->Columns->Add(L"Winner", L"Winner");
            this->Controls->Add(this->roundsGridView);

            // Simulation Progress ListBox
            this->simulationProgressListBox = gcnew ListBox();
            this->simulationProgressListBox->Font = gcnew Drawing::Font("Segoe UI", 12);
            this->simulationProgressListBox->Location = Point(30, 400);
            this->simulationProgressListBox->Size = Drawing::Size(880, 200);
            this->simulationProgressListBox->BorderStyle = BorderStyle::FixedSingle;
            this->simulationProgressListBox->BackColor = Color::White;
            this->Controls->Add(this->simulationProgressListBox);

            // Schedule Round Button
            this->scheduleRoundButton = CreateButton(L"Schedule ➕", Color::DodgerBlue, Point(30, 640));
            this->scheduleRoundButton->Click += gcnew EventHandler(this, &ManageRounds::OnScheduleRoundClick);
            this->Controls->Add(this->scheduleRoundButton);

            // Simulate Round Button
            this->simulateRoundButton = CreateButton(L"Simulate ▶️", Color::Orange, Point(250, 640));
            this->simulateRoundButton->Click += gcnew EventHandler(this, &ManageRounds::OnSimulateRoundClick);
            this->Controls->Add(this->simulateRoundButton);

            // Back Button
            this->backButton = CreateButton(L"Back ⬅️", Color::Gray, Point(470, 640));
            this->backButton->Click += gcnew EventHandler(this, &ManageRounds::OnBackClick);
            this->Controls->Add(this->backButton);

            // Winner Label
            this->winnerLabel = gcnew Label();
            this->winnerLabel->Text = L"Winner: ";
            this->winnerLabel->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
            this->winnerLabel->ForeColor = Color::Green;
            this->winnerLabel->Location = Point(30, 600); // Adjusted position to stay above the buttons
            this->winnerLabel->Size = Drawing::Size(400, 30);
            this->winnerLabel->TextAlign = ContentAlignment::MiddleLeft;
            this->Controls->Add(this->winnerLabel);

        }

        Button^ CreateButton(String^ text, Color backgroundColor, Point location) {
            Button^ button = gcnew Button();
            button->Text = text;
            button->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Regular);
            button->BackColor = backgroundColor;
            button->ForeColor = Color::White;
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->Size = Drawing::Size(200, 50);
            button->Location = location;

            // Add rounded corners
            button->Paint += gcnew PaintEventHandler(this, &ManageRounds::OnButtonPaint);

            return button;
        }

        void OnButtonPaint(Object^ sender, PaintEventArgs^ e) {
            Button^ button = (Button^)sender;
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
            path->AddArc(0, 0, 20, 20, 180, 90); // Top-left corner
            path->AddArc(button->Width - 21, 0, 20, 20, 270, 90); // Top-right corner
            path->AddArc(button->Width - 21, button->Height - 21, 20, 20, 0, 90); // Bottom-right corner
            path->AddArc(0, button->Height - 21, 20, 20, 90, 90); // Bottom-left corner
            path->CloseFigure();
            button->Region = gcnew System::Drawing::Region(path);
        }

        ///////////////////////////////////////////
        //Actual code for the ManageRounds.h file//
		///////////////////////////////////////////

        void OnScheduleRoundClick(Object^ sender, EventArgs^ e) {
            try {
                int currentRound = scheduler->getCurrentRound();
                if (currentRound >= 4) {
                    MessageBox::Show(L"The tournament is complete!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                // First round scheduling
                if (currentRound == 0) {
                    scheduler->scheduleFirstRound();
                }
                else {
                    Match* match = scheduler->matchList[currentRound].head; 
                    while (match) {
                        if (!match->completed) {
                            MessageBox::Show(L"Simulate all matches before moving to the next round.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                            return;
                        }
                        match = match->next;
                    }
                    scheduler->scheduleNextRound(currentRound);
                }

                PopulateRoundsGrid(currentRound);
            }
            catch (Exception^ ex) {
                MessageBox::Show(L"Error: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void PopulateRoundsGrid(int round) {
            this->roundsGridView->Rows->Clear();
            Match* match = scheduler->matchList[round].head;
            while (match) {
                this->roundsGridView->Rows->Add(
                    "Round " + (round + 1).ToString(),
                    gcnew String(match->team1),
                    gcnew String(match->team2),
                    gcnew String(match->date),
                    match->completed ? "Completed" : "Scheduled",
                    match->completed ? gcnew String(match->winner) : "N/A"
                );
                match = match->next;
            }
        }

        void OnSimulateRoundClick(Object^ sender, EventArgs^ e) {
            if (!simulationWorker->IsBusy) {
				simulationWorker->RunWorkerAsync(); // Start the background worker
            }
        }

        void OnSimulateRoundWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
            int currentRound = scheduler->getCurrentRound();

            if (currentRound >= 4) {
                simulationWorker->ReportProgress(-1, L"The tournament is already complete!");
                return;
            }

            Match* match = scheduler->matchList[currentRound].head;
            int matchIndex = 0;

            while (match != nullptr) {
                // Report match simulation progress
                simulationWorker->ReportProgress(matchIndex, L"Simulating match: " + gcnew String(match->team1) + L" vs " + gcnew String(match->team2));

                // Simulate the match
				std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 second delay
				if (rand() % 2 == 0) // Randomly select a winner
                {
                    strcpy_s(match->winner, sizeof(match->winner), match->team1);
                }
                else {
                    strcpy_s(match->winner, sizeof(match->winner), match->team2);
                }
                match->completed = true;

                // Report match result
                simulationWorker->ReportProgress(matchIndex, L"Winner: " + gcnew String(match->winner));

                match = match->next;
                matchIndex++;
            }

            // Notify round completion
            simulationWorker->ReportProgress(-1, L"Round " + (currentRound + 1).ToString() + L" simulation complete.");
        }

        void OnSimulationProgress(Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
            String^ progressMessage = (String^)e->UserState;
            this->simulationProgressListBox->Items->Add(progressMessage);
            this->simulationProgressListBox->TopIndex = this->simulationProgressListBox->Items->Count - 1;

            if (progressMessage->StartsWith(L"Simulating match: ")) {
                // Update DataGridView Status to "Simulating"
                int matchIndex = e->ProgressPercentage;
                if (matchIndex >= 0 && matchIndex < this->roundsGridView->Rows->Count) {
                    this->roundsGridView->Rows[matchIndex]->Cells[4]->Value = "Simulating";
                }
            }
            else if (progressMessage->StartsWith(L"Winner: ")) {
                // Update DataGridView with "Completed" status and the winner
                int matchIndex = e->ProgressPercentage;
                String^ winner = progressMessage->Substring(8); // Extract the winner name
                if (matchIndex >= 0 && matchIndex < this->roundsGridView->Rows->Count) {
                    this->roundsGridView->Rows[matchIndex]->Cells[4]->Value = "Completed"; // Status
                    this->roundsGridView->Rows[matchIndex]->Cells[5]->Value = winner;     // Winner
                }
            }
            else if (progressMessage->StartsWith(L"Round")) {
                // Notify round completion
                MessageBox::Show(progressMessage, L"Simulation Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Check if the tournament is complete and display the winner
                if (scheduler->getCurrentRound() >= 4) {
                    try {
                        const char* winnerTeam = scheduler->getWinnerTeam();
                        this->winnerLabel->Text = L"Winner: " + gcnew String(winnerTeam);
                    }
                    catch (Exception^ ex) {
                        MessageBox::Show(L"Error: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
            }
            else if (progressMessage->StartsWith(L"The tournament is already complete")) {
                // Notify tournament completion
                MessageBox::Show(progressMessage, L"Tournament Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void OnBackClick(Object^ sender, EventArgs^ e) {
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                L"Are you sure you want to go back? All matches will be lost or will begin from start.",
                L"Confirm Navigation",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                this->Close(); // Close the current form
                AddTeams->Show(); // Show the previous form
            }
        }

    public:
        ManageRounds(Scheduler* schedulerInstance, Form^ prevForm) {
            scheduler = schedulerInstance;
            AddTeams = prevForm; // Store the reference to the previous form
            InitializeComponent();
        }
    };
}
