// Jakub Rozkosz

#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <Wt/WApplication.h>
#include "WebappPage.h"

class AdminPanelApp : public WebappPage {
private:
    Wt::WLineEdit *searchEdit_;
    Wt::WTable *userList_;
    std::unique_ptr<Wt::WMessageBox> messageBox_;
    std::vector<std::tuple<int, std::string, int>> users_; 

public:
    AdminPanelApp(const Wt::WEnvironment& env);
    virtual void displayContent();
    void checkSession();
    void updateUserList(const std::string& filter);
    void handleLogOut();
    void handleDeletingAccount(const int row, const std::string& email);
    void handleBudgetChange(const int row, const std::string& email, const std::string& budget);
    Wt::WTable* getUserList();
    void setSqlDatabase(const std::string& db_name);

};

#endif