#pragma once
#include "ManageRounds.h"
#include "Scheduler.h"
#include <msclr/marshal_cppstd.h> 
#include <fstream>

namespace Hackathon {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AddTeams : public Form {
    private:
		Scheduler* scheduler; // Pointer to the shared Scheduler instance

        // UI Components
        Label^ formTitle;
        GroupBox^ inputGroupBox;
        Label^ teamNameLabel;
        Label^ membersLabel;
        Label^ rankLabel;
        TextBox^ teamNameTextBox;
        TextBox^ member1TextBox;
        TextBox^ member2TextBox;
        TextBox^ member3TextBox;
        TextBox^ member4TextBox;
        TextBox^ rankTextBox;
        Button^ addButton;
        Button^ browseButton;
        Button^ finishButton;
        Button^ deleteButton;
        TextBox^ searchBox;
        DataGridView^ teamGridView;

        void InitializeComponent(void) {
            // Form properties
            this->Text = L"Add Teams";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Size = Drawing::Size(1000, 720);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackColor = Color::FromArgb(250, 250, 250);
            this->MaximizeBox = false;

            // Title Label
            this->formTitle = gcnew Label();
            this->formTitle->Text = L"🏆 Add Teams";
            this->formTitle->Font = gcnew Drawing::Font("Segoe UI", 28, FontStyle::Bold);
            this->formTitle->ForeColor = Color::RoyalBlue;
            this->formTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->formTitle->Location = Point(10, 10);
            this->formTitle->Size = Drawing::Size(950, 60);
            this->Controls->Add(this->formTitle);

            // Input GroupBox
            this->inputGroupBox = gcnew GroupBox();
            this->inputGroupBox->Text = L"Team Information 📝";
            this->inputGroupBox->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
            this->inputGroupBox->ForeColor = Color::DarkSlateGray;
            this->inputGroupBox->BackColor = Color::White;
            this->inputGroupBox->Location = Point(30, 100);
            this->inputGroupBox->Size = Drawing::Size(420, 480);
            this->Controls->Add(this->inputGroupBox);

            // Labels and Textboxes inside Input GroupBox
            CreateInputFields();

            // Search Box with Placeholder
            InitializeSearchBox();

            // Team DataGridView
            this->teamGridView = gcnew DataGridView();
            this->teamGridView->Font = gcnew Drawing::Font("Segoe UI", 12);
            this->teamGridView->Location = Point(470, 140);
            this->teamGridView->Size = Drawing::Size(480, 440);
            this->teamGridView->BackgroundColor = Color::White;
            this->teamGridView->BorderStyle = BorderStyle::FixedSingle;
            this->teamGridView->ColumnHeadersHeight = 40;
            this->teamGridView->AllowUserToAddRows = false;
            this->teamGridView->RowHeadersVisible = false;
            this->teamGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->teamGridView->TabStop = false; // Disable TabStop for DataGridView

            // Add columns to DataGridView
            this->teamGridView->Columns->Add(L"TeamName", L"Team Name");
            this->teamGridView->Columns->Add(L"Rank", L"Rank");
            this->teamGridView->Columns->Add(L"Members", L"Members");

            // Adjust column widths
            this->teamGridView->Columns["Rank"]->AutoSizeMode = DataGridViewAutoSizeColumnMode::None;
            this->teamGridView->Columns["Rank"]->Width = 65; // Smaller width for Rank column
            this->teamGridView->Columns["Members"]->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill; // Fill remaining space
            this->teamGridView->Columns["TeamName"]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells; // Auto-size based on content
            this->Controls->Add(this->teamGridView);

            // Buttons
            AddButtons();
        }

        void CreateInputFields() {
            // Team Name
            this->teamNameLabel = CreateLabel(L"Team Name:", Point(20, 40));
            this->teamNameTextBox = CreateTextBox(Point(150, 40));

            // Members
            this->membersLabel = CreateLabel(L"Members (Max 4):", Point(20, 90));

            Label^ member1Label = CreateLabel(L"Member 1:", Point(20, 130));
            this->member1TextBox = CreateTextBox(Point(150, 130));

            Label^ member2Label = CreateLabel(L"Member 2:", Point(20, 170));
            this->member2TextBox = CreateTextBox(Point(150, 170));

            Label^ member3Label = CreateLabel(L"Member 3:", Point(20, 210));
            this->member3TextBox = CreateTextBox(Point(150, 210));

            Label^ member4Label = CreateLabel(L"Member 4:", Point(20, 250));
            this->member4TextBox = CreateTextBox(Point(150, 250));

            // Rank
            this->rankLabel = CreateLabel(L"Rank:", Point(20, 300));
            this->rankTextBox = CreateTextBox(Point(150, 300));

            this->inputGroupBox->Controls->Add(this->teamNameLabel);
            this->inputGroupBox->Controls->Add(this->teamNameTextBox);
            this->inputGroupBox->Controls->Add(this->membersLabel);

            this->inputGroupBox->Controls->Add(member1Label);
            this->inputGroupBox->Controls->Add(this->member1TextBox);

            this->inputGroupBox->Controls->Add(member2Label);
            this->inputGroupBox->Controls->Add(this->member2TextBox);

            this->inputGroupBox->Controls->Add(member3Label);
            this->inputGroupBox->Controls->Add(this->member3TextBox);

            this->inputGroupBox->Controls->Add(member4Label);
            this->inputGroupBox->Controls->Add(this->member4TextBox);

            this->inputGroupBox->Controls->Add(this->rankLabel);
            this->inputGroupBox->Controls->Add(this->rankTextBox);
        }

        Label^ CreateLabel(String^ text, Point location) {
            Label^ label = gcnew Label();
            label->Text = text;
            label->Font = gcnew Drawing::Font("Segoe UI", 12);
            label->Location = location;
            label->Size = Drawing::Size(120, 30);
            return label;
        }

        TextBox^ CreateTextBox(Point location) {
            TextBox^ textBox = gcnew TextBox();
            textBox->Font = gcnew Drawing::Font("Segoe UI", 12);
            textBox->Location = location;
            textBox->Size = Drawing::Size(200, 30);
            return textBox;
        }

        void AddButtons() {
            this->addButton = CreateButton(L"Add ➕", Color::DodgerBlue, Point(30, 610));
            this->addButton->Click += gcnew EventHandler(this, &AddTeams::OnAddClick);
            this->Controls->Add(this->addButton);

            this->browseButton = CreateButton(L"Browse 📁", Color::Orange, Point(200, 610));
            this->browseButton->Click += gcnew EventHandler(this, &AddTeams::OnBrowseClick);
            this->Controls->Add(this->browseButton);

            this->finishButton = CreateButton(L"Finish ✅", Color::Green, Point(380, 610));
            this->finishButton->Click += gcnew EventHandler(this, &AddTeams::OnFinishClick);
            this->Controls->Add(this->finishButton);

            this->deleteButton = CreateButton(L"Delete ❌", Color::Red, Point(560, 610));
            this->deleteButton->Click += gcnew EventHandler(this, &AddTeams::OnDeleteClick);
            this->Controls->Add(this->deleteButton);

            // New Clear All Button
            Button^ clearAllButton = CreateButton(L"Clear All 🗑️", Color::DarkOrange, Point(740, 610));
            clearAllButton->Click += gcnew EventHandler(this, &AddTeams::OnClearAllClick);
            this->Controls->Add(clearAllButton);
        }


        Button^ CreateButton(String^ text, Color backgroundColor, Point location) {
            Button^ button = gcnew Button();
            button->Text = text;
            button->Font = gcnew Drawing::Font("Segoe UI", 12);
            button->BackColor = backgroundColor;
            button->ForeColor = Color::White;
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->Size = Drawing::Size(140, 50);
            button->Location = location;
            button->Paint += gcnew PaintEventHandler(this, &AddTeams::OnButtonPaint);
            return button;
        }

        void OnButtonPaint(Object^ sender, PaintEventArgs^ e) {
            Button^ button = (Button^)sender;
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
            path->AddArc(0, 0, 20, 20, 180, 90);
            path->AddArc(button->Width - 20, 0, 20, 20, 270, 90);
            path->AddArc(button->Width - 20, button->Height - 20, 20, 20, 0, 90);
            path->AddArc(0, button->Height - 20, 20, 20, 90, 90);
            path->CloseFigure();
            button->Region = gcnew System::Drawing::Region(path);
        }

        void InitializeSearchBox() {
            this->searchBox = CreateTextBox(Point(470, 100));
            this->searchBox->Size = Drawing::Size(400, 30);
            this->searchBox->ForeColor = Color::Gray;
            this->searchBox->Text = L"Search teams...";
            this->searchBox->TabStop = false; // Disable TabStop for the search box
            this->searchBox->GotFocus += gcnew EventHandler(this, &AddTeams::OnSearchBoxGotFocus);
            this->searchBox->LostFocus += gcnew EventHandler(this, &AddTeams::OnSearchBoxLostFocus);
            this->searchBox->TextChanged += gcnew EventHandler(this, &AddTeams::OnSearchTextChanged);
            this->Controls->Add(this->searchBox);
        }

        void OnSearchBoxKeyDown(Object^ sender, KeyEventArgs^ e) {
            // Prevent placeholder resetting when using Tab to navigate
            if (e->KeyCode == Keys::Tab) {
                if (String::IsNullOrWhiteSpace(this->searchBox->Text)) {
                    this->searchBox->Text = L""; // Ensure it's empty for navigation
                }
            }
        }

        void OnSearchBoxLostFocus(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(this->searchBox->Text)) {
                this->searchBox->Text = L"Search teams...";
                this->searchBox->ForeColor = Color::Gray;

                // Reset DataGridView to show all rows
                for (int i = 0; i < this->teamGridView->Rows->Count; i++) {
                    this->teamGridView->Rows[i]->Visible = true;
                }
            }
        }

        void OnSearchBoxGotFocus(Object^ sender, EventArgs^ e) {
            if (this->searchBox->Text == L"Search teams...") {
                this->searchBox->Text = L"";
                this->searchBox->ForeColor = Color::Black;
            }
        }

        void OnSearchTextChanged(Object^ sender, EventArgs^ e) {
            String^ query = this->searchBox->Text->ToLower();

            // Show all rows when search box is empty or contains default placeholder
            if (String::IsNullOrWhiteSpace(query) || query == L"search teams...") {
                for (int i = 0; i < this->teamGridView->Rows->Count; i++) {
                    this->teamGridView->Rows[i]->Visible = true;
                }
            }
            else {
                // Filter rows based on the search query
                for (int i = 0; i < this->teamGridView->Rows->Count; i++) {
                    bool visible = this->teamGridView->Rows[i]->Cells[0]->Value->ToString()->ToLower()->Contains(query);
                    this->teamGridView->Rows[i]->Visible = visible;
                }
            }
        }

        public:
            AddTeams(Scheduler* schedulerInstance) {
                scheduler = schedulerInstance;
                InitializeComponent();
            }

        void OnDeleteClick(Object^ sender, EventArgs^ e) {
            if (this->teamGridView->SelectedRows->Count == 0) {
                MessageBox::Show(L"Please select a team to delete.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            System::Windows::Forms::DialogResult result = MessageBox::Show(
                L"Are you sure you want to delete the selected team?",
                L"Confirm Deletion",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                this->teamGridView->Rows->Remove(this->teamGridView->SelectedRows[0]);
                MessageBox::Show(L"Team deleted successfully.", L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void OnClearAllClick(Object^ sender, EventArgs^ e) {
            // Confirm before clearing all data
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                L"Are you sure you want to delete all teams?",
                L"Confirm Deletion",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                this->teamGridView->Rows->Clear();
                MessageBox::Show(L"All teams have been deleted successfully.", L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void OnFinishClick(Object^ sender, EventArgs^ e) {
            if (this->teamGridView->Rows->Count == 16) {
                MessageBox::Show(L"All teams added successfully!", L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                ManageRounds^ manageRoundsForm = gcnew ManageRounds(scheduler, this); // Pass the current form
                manageRoundsForm->Show();
                this->Hide();
            }
            else {
                MessageBox::Show(L"Please add exactly 16 teams before proceeding.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        ///////////////////////////////////////
		//Actual code for the AddTeams.h file//
		///////////////////////////////////////


        void OnAddClick(Object^ sender, EventArgs^ e) {
            // Check if the maximum number of teams has been reached
            if (this->teamGridView->Rows->Count >= 16) {
                MessageBox::Show(L"Cannot add more than 16 teams!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Validate inputs
            String^ teamName = this->teamNameTextBox->Text;
            String^ rankText = this->rankTextBox->Text;

            if (String::IsNullOrWhiteSpace(teamName)) {
                this->teamNameTextBox->BackColor = Color::LightCoral; // Highlight error
                MessageBox::Show(L"Team name cannot be empty!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Check if team name is unique
            for (int i = 0; i < this->teamGridView->Rows->Count; ++i) {
                if (this->teamGridView->Rows[i]->Cells[0]->Value->ToString() == teamName) {
                    MessageBox::Show(L"Team name must be unique!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            // Check if rank is a positive integer between 1 and 16
            int rankValue;
            if (!Int32::TryParse(rankText, rankValue) || rankValue <= 0 || rankValue > 16) {
                this->rankTextBox->BackColor = Color::LightCoral; // Highlight error
                MessageBox::Show(L"Rank must be a positive integer between 1 and 16!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Check if rank is unique
            for (int i = 0; i < this->teamGridView->Rows->Count; ++i) {
                if (this->teamGridView->Rows[i]->Cells[1]->Value->ToString() == rankText) {
                    MessageBox::Show(L"Rank must be unique!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            // Check if at least one member is provided
            if (String::IsNullOrWhiteSpace(this->member1TextBox->Text)) {
                this->member1TextBox->BackColor = Color::LightCoral; // Highlight error
                MessageBox::Show(L"At least one member is required!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Reset validation styles
            this->teamNameTextBox->BackColor = Color::White;
            this->rankTextBox->BackColor = Color::White;
            this->member1TextBox->BackColor = Color::White;

            // Combine members into a single string
            String^ members = this->member1TextBox->Text;
            if (!String::IsNullOrWhiteSpace(this->member2TextBox->Text)) {
                members += L", " + this->member2TextBox->Text;
            }
            if (!String::IsNullOrWhiteSpace(this->member3TextBox->Text)) {
                members += L", " + this->member3TextBox->Text;
            }
            if (!String::IsNullOrWhiteSpace(this->member4TextBox->Text)) {
                members += L", " + this->member4TextBox->Text;
            }

            // Add to DataGridView
            this->teamGridView->Rows->Add(teamName, rankText, members);

            // Clear input fields
            this->teamNameTextBox->Clear();
            this->member1TextBox->Clear();
            this->member2TextBox->Clear();
            this->member3TextBox->Clear();
            this->member4TextBox->Clear();
            this->rankTextBox->Clear();
        }

        void OnBrowseClick(Object^ sender, EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string filename = msclr::interop::marshal_as<std::string>(openFileDialog->FileName);
                scheduler->loadTeamsFromFile(filename.c_str());

                for (int i = 0; i < scheduler->teamCount; ++i) {
                    if (this->teamGridView->Rows->Count >= 16) {
                        MessageBox::Show(L"Cannot add more than 16 teams!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        break;
                    }

                    Team team = scheduler->teams[i];
                    String^ rankText = team.rank.ToString();

                    bool rankUnique = true;
                    for (int j = 0; j < this->teamGridView->Rows->Count; ++j) {
                        if (this->teamGridView->Rows[j]->Cells[1]->Value->ToString() == rankText) {
                            rankUnique = false;
                            break;
                        }
                    }
                    if (!rankUnique || team.rank <= 0 || team.rank > 16) {
                        MessageBox::Show(L"Rank must be unique and between 1 and 16!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        continue;
                    }

                    String^ members = gcnew String(team.members[0]);
                    for (int j = 1; j < team.memberCount; ++j) {
                        members += L", " + gcnew String(team.members[j]);
                    }

                    this->teamGridView->Rows->Add(gcnew String(team.teamName), rankText, members);
                }
            }
        }
    };
}
