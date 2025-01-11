// Jakub Rozkosz

#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <Wt/WApplication.h>
#include "WebappPage.h"

class LoginApp : public WebappPage {
private:
    Wt::WLineEdit *usernameEdit_;
    Wt::WLineEdit *passwordEdit_;
    Wt::WText *statusText_;

public:
    LoginApp(const Wt::WEnvironment& env);
    void handleLogin();
    virtual void displayContent();
    void checkSession();
    void handleRedirectionToUser();
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    Wt::WText* getStatusText();
};

#endif