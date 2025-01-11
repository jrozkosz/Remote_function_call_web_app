// Jakub Rozkosz

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <Wt/WEnvironment.h>
#include <Wt/Http/Cookie.h>
#include "AdminLogin.h"

using namespace std;

LoginApp::LoginApp(const Wt::WEnvironment& env)
    : WebappPage(env) 
{
    setTitle("Admin Panel Login");
    useStyleSheet(Wt::WLink("webapp_style.css"));
    checkSession();
    displayContent();
}

void LoginApp::displayContent() {
    auto container = root()->addNew<Wt::WContainerWidget>();
    container->setStyleClass("login-container");

    container->addNew<Wt::WText>("<h2>Logowanie do panelu administratora</h2>");

    container->addNew<Wt::WText>("Nazwa użytkownika: ");
    usernameEdit_ = container->addNew<Wt::WLineEdit>();
    usernameEdit_->setStyleClass("Wt-WLineEdit");
    usernameEdit_->setPlaceholderText("Wprowadź nazwę...");

    container->addNew<Wt::WBreak>();

    container->addNew<Wt::WText>("Hasło: ");
    passwordEdit_ = container->addNew<Wt::WLineEdit>();
    passwordEdit_->setStyleClass("Wt-WLineEdit");
    passwordEdit_->setEchoMode(Wt::EchoMode::Password);
    passwordEdit_->setPlaceholderText("Wprowadź hasło...");

    container->addNew<Wt::WBreak>();

    Wt::WPushButton *loginButton = container->addNew<Wt::WPushButton>("Zaloguj się");
    loginButton->setStyleClass("Wt-WPushButton");
    loginButton->clicked().connect(this, &LoginApp::handleLogin);

    container->addNew<Wt::WBreak>();

    statusText_ = container->addNew<Wt::WText>();

    Wt::WPushButton *adminRedirectionButton = container->addNew<Wt::WPushButton>("Przekieruj do panelu użytkownika");
    adminRedirectionButton->setStyleClass("Wt-WPushButton");
    adminRedirectionButton->clicked().connect(this, &LoginApp::handleRedirectionToUser);
}

void LoginApp::handleLogin() {
    const string correctUsername = "admin";
    const string correctPassword = "admin";

    if (usernameEdit_->text() == correctUsername && passwordEdit_->text() == correctPassword) {
        statusText_->setText("Pomyślne logowanie.");
        // Set a session cookie
        Wt::Http::Cookie cookie("session", "loggedIn");
        cookie.setMaxAge(chrono::seconds(1800)); // 0.5 hour duration
        cookie.setPath("/");
        WApplication::instance()->setCookie(cookie);
        // Redirect to admin panel
        WApplication::instance()->redirect("/admin");
    } else {
        statusText_->setText("Niepoprawna nazwa użytkownika lub hasło.");
        statusText_->setStyleClass("NotOkStatus-Wt-WText");
    }
}

void LoginApp::checkSession() {
    if (environment().cookies().find("session") != environment().cookies().end() && 
        environment().cookies().at("session") == "loggedIn") {
        WApplication::instance()->redirect("/admin");  // Redirect to admin panel if already logged in
    }
}

void LoginApp::setUsername(const string& username) { usernameEdit_->setText(username); }
void LoginApp::setPassword(const string& password) { passwordEdit_->setText(password); }
Wt::WText* LoginApp::getStatusText() { return statusText_; }

void LoginApp::handleRedirectionToUser() {
    WApplication::instance()->redirect("/");
}