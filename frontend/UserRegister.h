// Jakub Rozkosz

#ifndef USERREGISTER_H
#define USERREGISTER_H

#include <Wt/WApplication.h>
#include "WebappPage.h"

class UserRegisterApp : public WebappPage {
private:
    Wt::WLineEdit *emailEdit_;
    Wt::WLineEdit *passwordEdit_;
    Wt::WText *statusText_;
    Wt::WText *demoClientInfoText_;

public:
    UserRegisterApp(const Wt::WEnvironment& env);
    void handleRegistration();
    void handleRedirectionToAdmin();
    virtual void displayContent();
    void addImageToContainer(Wt::WContainerWidget *container);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    Wt::WText* getStatusText();
};

#endif