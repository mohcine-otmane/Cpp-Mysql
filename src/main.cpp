#include <wx/wx.h>
#include "LoginFrame.h"
#include <iostream>

class LoginApp : public wxApp {
public:
    virtual bool OnInit() {
        try {
            if (!wxApp::OnInit())
                return false;

            LoginFrame* frame = new LoginFrame();
            frame->Show();
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
        catch (...) {
            std::cerr << "Unknown error occurred" << std::endl;
            return false;
        }
    }
};

wxIMPLEMENT_APP(LoginApp);