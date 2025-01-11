// Jakub Rozkosz

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <Wt/WEnvironment.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WLink.h>
#include "UserRegister.h"
#include "../db/Database.h"

using namespace std;

UserRegisterApp::UserRegisterApp(const Wt::WEnvironment& env)
    : WebappPage(env)
{
    setTitle("User Registration");

    useStyleSheet(Wt::WLink("webapp_style.css"));

    displayContent();
}

void UserRegisterApp::displayContent() {
    auto container = root()->addNew<Wt::WContainerWidget>();
    container->setStyleClass("register-container");

    container->addNew<Wt::WText>("<h1>Witamy w 'Remote Optimization Function Call App'</h1>");
    container->addNew<Wt::WText>("<h2>Proszę zarejestruj się w systemie</h2>");
    container->addNew<Wt::WText>("Email: ");
    emailEdit_ = container->addNew<Wt::WLineEdit>();
    emailEdit_->setPlaceholderText("Wprowadź email...");
    emailEdit_->setStyleClass("Wt-WLineEdit");

    container->addNew<Wt::WBreak>();

    container->addNew<Wt::WText>("Hasło: ");
    passwordEdit_ = container->addNew<Wt::WLineEdit>();
    passwordEdit_->setEchoMode(Wt::EchoMode::Password);
    passwordEdit_->setPlaceholderText("Wprowadź hasło...");
    passwordEdit_->setStyleClass("Wt-WLineEdit");

    container->addNew<Wt::WBreak>();

    Wt::WPushButton *loginButton = container->addNew<Wt::WPushButton>("Zarejestruj się");
    loginButton->setStyleClass("Wt-WPushButton");
    loginButton->clicked().connect(this, &UserRegisterApp::handleRegistration);

    container->addNew<Wt::WBreak>();

    statusText_ = container->addNew<Wt::WText>();

    container->addNew<Wt::WBreak>();

    demoClientInfoText_ = container->addNew<Wt::WText>(
        string("Przykład pokazujący w jaki sposób wywołać funkcje CEC z serwera.\n") +
        "Populacja to jedno wymiarowa tablica, która zawiera połączone ze sobą\n" +
        "osobniki. W tym przykładzie pierwszy osobnik to [1,2] drugi [3,4] itd.\n" +
        "Pełen kod kliencki znajduje się pod tym linkiem: (link do repozytorium).\n"
    );
    demoClientInfoText_->setStyleClass("Info-Wt-WText");

    container->addNew<Wt::WBreak>();

    addImageToContainer(container);

    container->addNew<Wt::WBreak>();

    Wt::WPushButton *adminRedirectionButton = container->addNew<Wt::WPushButton>("Przekieruj do panelu administratora");
    adminRedirectionButton->setStyleClass("Wt-WPushButton");
    adminRedirectionButton->clicked().connect(this, &UserRegisterApp::handleRedirectionToAdmin);

    container->addNew<Wt::WBreak>();
}

void UserRegisterApp::addImageToContainer(Wt::WContainerWidget *container) {
    auto imageContainer = container->addNew<Wt::WContainerWidget>();
    imageContainer->setStyleClass("image-container");

    auto image = imageContainer->addNew<Wt::WImage>("demo_client.png");
    image->setStyleClass("centered-image");
}

void UserRegisterApp::handleRegistration() {
    try {
        SqlDatabase& db = SqlDatabase::instance();

        if (emailEdit_->text().toUTF8() == "" || passwordEdit_->text().toUTF8() == "") {
            statusText_->setText("Email lub hasło nie może być puste.");
            statusText_->setStyleClass("NotOkStatus-Wt-WText");
        } else if (db.getUserId(emailEdit_->text().toUTF8()) != -1) {
            statusText_->setText("Taki użytkownik już istnieje.");
            statusText_->setStyleClass("NotOkStatus-Wt-WText");
        } else {
            db.insertUser(emailEdit_->text().toUTF8(), passwordEdit_->text().toUTF8(),
                            1000);
            statusText_->setText("Zostałeś pomyślnie zarejestrowany!");
            statusText_->setStyleClass("OkStatus-Wt-WText");
        }
    } catch(const runtime_error& e) {
        cerr << "Caught exception: " << e.what() << endl;
        showMessageDialog("Info", "Wystąpił problem z komunikacją z bazą danych...");
    }
}

void UserRegisterApp::setEmail(const string& email) { emailEdit_->setText(email); }
void UserRegisterApp::setPassword(const string& password) { passwordEdit_->setText(password); }
Wt::WText* UserRegisterApp::getStatusText() { return statusText_; }

void UserRegisterApp::handleRedirectionToAdmin() {
    WApplication::instance()->redirect("/login");
}
