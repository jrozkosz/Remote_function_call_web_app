// Jakub Rozkosz

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WDialog.h>
#include <Wt/WServer.h>
#include <Wt/WEnvironment.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMessageBox.h>
#include <Wt/WTable.h>
#include <Wt/Http/Cookie.h>
#include "AdminPanel.h"
#include "../db/Database.h"

using namespace std;

AdminPanelApp::AdminPanelApp(const Wt::WEnvironment& env)
    : WebappPage(env)
{
    setTitle("Admin Panel");
    useStyleSheet(Wt::WLink("webapp_style.css"));
    checkSession();
    displayContent();
}

void AdminPanelApp::displayContent() {
    auto container = root()->addNew<Wt::WContainerWidget>();
    container->setStyleClass("admin-panel");

    container->addNew<Wt::WText>("<h1>Panel administratora</h1>");
    container->addNew<Wt::WText>("<h3>Lista użytkowników:</h3>");

    searchEdit_ = container->addNew<Wt::WLineEdit>();
    searchEdit_->setStyleClass("Wt-WLineEdit");
    searchEdit_->setPlaceholderText("Wyszukaj po email'u... ");
    searchEdit_->textInput().connect([this] {
        updateUserList(searchEdit_->text().toUTF8());
    });

    container->addNew<Wt::WBreak>();

    userList_ = container->addNew<Wt::WTable>();
    userList_->setStyleClass("admin-table");
    userList_->setHeaderCount(1);

    updateUserList("");

    container->addNew<Wt::WBreak>();

    Wt::WPushButton *logOutButton = container->addNew<Wt::WPushButton>("Wyloguj się");
    logOutButton->setStyleClass("Wt-WPushButton");
    logOutButton->clicked().connect(this, &AdminPanelApp::handleLogOut);
}


void AdminPanelApp::updateUserList(const string& filter) {
    try {
        SqlDatabase& db = SqlDatabase::instance();
        users_ = db.getAllUsers();
    } catch (const std::runtime_error& e) {
        cerr << "Caught exception: " << e.what() << endl;
        showMessageDialog("Info", "Wystąpił problem z komunikacją z bazą danych...");
        return;
    }

    userList_->clear();

    userList_->elementAt(0, 0)->addNew<Wt::WText>("Id");
    userList_->elementAt(0, 1)->addNew<Wt::WText>("Email");
    userList_->elementAt(0, 2)->addNew<Wt::WText>("Budżet");

    int row = 1;
    for (const auto& user : users_) {
        if (filter.empty() || get<1>(user).find(filter) != string::npos) {
            userList_->elementAt(row, 0)->addNew<Wt::WText>(" "+to_string(get<0>(user))+" ");
            userList_->elementAt(row, 1)->addNew<Wt::WText>(" "+get<1>(user)+" ");
            userList_->elementAt(row, 2)->addNew<Wt::WText>(" "+to_string(get<2>(user))+" ");
            Wt::WPushButton* deleteButton = userList_->elementAt(row, 3)->addNew<Wt::WPushButton>("Usuń");
            deleteButton->setStyleClass("Wt-WPushButton");
            deleteButton->clicked().connect([this, user, row] {
                handleDeletingAccount(row, get<1>(user));
            });

            Wt::WLineEdit* budgetEdit = userList_->elementAt(row, 4)->addNew<Wt::WLineEdit>();
            budgetEdit->setStyleClass("Wt-WLineEdit");
            budgetEdit->setPlaceholderText("Wprowadź nowy budżet i kliknij Enter...");
            budgetEdit->setWidth(250);
            budgetEdit->enterPressed().connect([this, user, row, budgetEdit] {
                handleBudgetChange(row, get<1>(user), budgetEdit->text().toUTF8());
            });
            ++row;
        }
    }
}

void AdminPanelApp::checkSession() {
    if (!(environment().cookies().find("session") != environment().cookies().end() && 
        environment().cookies().at("session") == "loggedIn")) {
        WApplication::instance()->redirect("/login");  // Redirect to admin login if not logged in
    }
}

void AdminPanelApp::handleBudgetChange(const int row, const string& email, const string& budget) {
    
    try {
        int new_budget = stoi(budget);
        if (new_budget < 0) {
            showMessageDialog("Błąd", "Wprowadzany budżet nie może być liczbą ujemną.");
            return;
        }
        SqlDatabase& db = SqlDatabase::instance();
        db.changeUserBudget(email, new_budget);
        updateUserList("");
        showMessageDialog("Info", "Budżet użytkownika: " + email + " został pomyślnie zmieniony.");
    } catch(const invalid_argument&) {
        showMessageDialog("Błąd", "Wprowadzany budżet musi być liczbą całkowitą.");
    } catch(const out_of_range&) {
        showMessageDialog("Błąd", 
            "Wprowadzany budżet musi być mniejszy niż 2147483647 (maksymalna wartość dla integera).");
    } catch(const std::runtime_error& e) {
        cerr << "Caught exception: " << e.what() << endl;
        showMessageDialog("Info", "Wystąpił problem z komunikacją z bazą danych...");
    }
}

void AdminPanelApp::handleLogOut() {
    Wt::Http::Cookie cookie("session", "loggedIn");
    cookie.setMaxAge(chrono::seconds(0));
    cookie.setPath("/");
    WApplication::instance()->setCookie(cookie);

    WApplication::instance()->redirect("/login");
}

void AdminPanelApp::handleDeletingAccount(const int row, const string& email) {
    try {
        SqlDatabase& db = SqlDatabase::instance();
        db.deleteUser(email);
    } catch (const std::runtime_error& e) {
        cerr << "Caught exception: " << e.what() << endl;
        showMessageDialog("Info", "Wystąpił problem z komunikacją z bazą danych...");
        return;
    }

    userList_->removeRow(row);
    updateUserList("");
}

void AdminPanelApp::setSqlDatabase(const string& db_name) {
    SqlDatabase& db = SqlDatabase::instance(db_name);
}

Wt::WTable* AdminPanelApp::getUserList() {
    return userList_;
}