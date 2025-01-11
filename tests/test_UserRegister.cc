// Jakub Rozkosz

#define BOOST_TEST_MODULE UserRegisterAppTests
#include <boost/test/included/unit_test.hpp>
#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <Wt/Test/WTestEnvironment.h>
#include "../webapp/UserRegister.h"
#include "../db/Database.h"

std::unique_ptr<Wt::WApplication> createUserRegisterAppTest(const Wt::WEnvironment& env) {
    return std::make_unique<UserRegisterApp>(env);
}

BOOST_AUTO_TEST_SUITE(UserRegisterAppTests)

BOOST_AUTO_TEST_CASE(TestSuccessfulRegistration) {
    Wt::Test::WTestEnvironment env;
    auto app = createUserRegisterAppTest(env);
    auto userApp = dynamic_cast<UserRegisterApp*>(app.get());

    userApp->setEmail("test99999@example.com");
    userApp->setPassword("password123");
    userApp->handleRegistration();

    BOOST_CHECK_EQUAL(userApp->getStatusText()->text().toUTF8(), "Zostałeś pomyślnie zarejestrowany!");
    BOOST_CHECK_EQUAL(userApp->getStatusText()->styleClass(), "OkStatus-Wt-WText");

    SqlDatabase& db = SqlDatabase::instance();
    db.deleteUser("test99999@example.com");
}

BOOST_AUTO_TEST_CASE(TestEmptyEmailOrPassword) {
    Wt::Test::WTestEnvironment env;
    auto app = createUserRegisterAppTest(env);
    auto userApp = dynamic_cast<UserRegisterApp*>(app.get());

    userApp->setEmail("");
    userApp->setPassword("password123");
    userApp->handleRegistration();

    BOOST_CHECK_EQUAL(userApp->getStatusText()->text().toUTF8(), "Email lub hasło nie może być puste.");
    BOOST_CHECK_EQUAL(userApp->getStatusText()->styleClass(), "NotOkStatus-Wt-WText");

    userApp->setEmail("test@example.com");
    userApp->setPassword("");
    userApp->handleRegistration();

    BOOST_CHECK_EQUAL(userApp->getStatusText()->text().toUTF8(), "Email lub hasło nie może być puste.");
    BOOST_CHECK_EQUAL(userApp->getStatusText()->styleClass(), "NotOkStatus-Wt-WText");
}

BOOST_AUTO_TEST_CASE(TestExistingUserRegistration) {
    Wt::Test::WTestEnvironment env;
    auto app = createUserRegisterAppTest(env);
    auto userApp = dynamic_cast<UserRegisterApp*>(app.get());

    userApp->setEmail("existing99999@example.com");
    userApp->setPassword("password123");
    userApp->handleRegistration();
    userApp->handleRegistration();

    BOOST_CHECK_EQUAL(userApp->getStatusText()->text().toUTF8(), "Taki użytkownik już istnieje.");
    BOOST_CHECK_EQUAL(userApp->getStatusText()->styleClass(), "NotOkStatus-Wt-WText");

    SqlDatabase& db = SqlDatabase::instance();
    db.deleteUser("existing99999@example.com");
}

BOOST_AUTO_TEST_CASE(TestRedirectionToAdminPanel) {
    Wt::Test::WTestEnvironment env;
    auto app = createUserRegisterAppTest(env);
    auto userApp = dynamic_cast<UserRegisterApp*>(app.get());

    userApp->handleRedirectionToAdmin();

    BOOST_CHECK_EQUAL(Wt::WApplication::instance()->internalPath(), "/");
}

BOOST_AUTO_TEST_SUITE_END()
