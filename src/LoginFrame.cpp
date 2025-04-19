#include "LoginFrame.h"
#include <wx/statline.h>
#include <iostream>
#include <windows.h>

wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
    EVT_BUTTON(wxID_ANY, LoginFrame::OnLoginClick)
wxEND_EVENT_TABLE()

LoginFrame::LoginFrame() : wxFrame(nullptr, wxID_ANY, "MySQL Login", wxDefaultPosition, wxSize(300, 250)) {
    // Create debug console
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::cout << "Starting MySQL Login application..." << std::endl;
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer* userSizer = new wxBoxSizer(wxHORIZONTAL);
    userSizer->Add(new wxStaticText(panel, wxID_ANY, "Username: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    usernameCtrl = new wxTextCtrl(panel, wxID_ANY);
    userSizer->Add(usernameCtrl, 1, wxALL, 5);
    
    wxBoxSizer* passSizer = new wxBoxSizer(wxHORIZONTAL);
    passSizer->Add(new wxStaticText(panel, wxID_ANY, "Password: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, 
                                wxDefaultSize, wxTE_PASSWORD);
    passSizer->Add(passwordCtrl, 1, wxALL, 5);
    
    loginButton = new wxButton(panel, wxID_ANY, "Login");
    statusText = new wxStaticText(panel, wxID_ANY, "");
    statusText->SetForegroundColour(*wxRED);
    
    mainSizer->Add(userSizer, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(passSizer, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(statusText, 0, wxEXPAND | wxALL, 5);
    
    panel->SetSizer(mainSizer);
    Center();
    
    if (!db.connect("localhost", "root", "", "testdb")) {
        std::cerr << "Database connection error: " << db.getLastError() << std::endl;
        statusText->SetLabel("Database Error: " + db.getLastError());
    } else {
        std::cout << "Successfully connected to database" << std::endl;
    }
}

LoginFrame::~LoginFrame() {
    db.disconnect();
}

void LoginFrame::OnLoginClick(wxCommandEvent& event) {
    wxString username = usernameCtrl->GetValue();
    wxString password = passwordCtrl->GetValue();
    
    if (username.empty() || password.empty()) {
        statusText->SetLabel("Please enter both username and password");
        return;
    }
    
    loginButton->Disable();
    wxBeginBusyCursor();
    
    std::cout << "Attempting login with username: " << username.ToStdString() << std::endl;
    
    bool success = db.validateLogin(username.ToStdString(), password.ToStdString());
    
    wxEndBusyCursor();
    loginButton->Enable();
    
    if (success) {
        std::cout << "Login successful for username: " << username.ToStdString() << std::endl;
        wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
        passwordCtrl->Clear();
    } else {
        std::cerr << "Login failed for username: " << username.ToStdString() << ". Error: " << db.getLastError() << std::endl;
        statusText->SetLabel("Login failed: " + db.getLastError());
        passwordCtrl->Clear();
        passwordCtrl->SetFocus();
    }
}