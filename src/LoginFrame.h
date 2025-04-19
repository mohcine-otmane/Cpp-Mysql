#pragma once
#include <wx/wx.h>
#include "Database.h"

class LoginFrame : public wxFrame {
private:
    Database db;
    wxTextCtrl* usernameCtrl;
    wxTextCtrl* passwordCtrl;
    wxButton* loginButton;
    wxStaticText* statusText;
    void OnLoginClick(wxCommandEvent& event);

public:
    LoginFrame();
    ~LoginFrame();
    wxDECLARE_EVENT_TABLE();
};