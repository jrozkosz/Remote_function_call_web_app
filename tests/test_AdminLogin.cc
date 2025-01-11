// Jakub Rozkosz

#define BOOST_TEST_MODULE LoginAppTests
#include <boost/test/included/unit_test.hpp>
#include <Wt/Test/WTestEnvironment.h>
#include <Wt/WText.h>
#include "../webapp/AdminLogin.h"

std::unique_ptr<Wt::WApplication> createLoginAppTest(const Wt::WEnvironment& env) {
    return std::make_unique<LoginApp>(env);
}

BOOST_AUTO_TEST_SUITE(LoginAppTests)

BOOST_AUTO_TEST_CASE(TestSuccessfulLogin) {
    Wt::Test::WTestEnvironment env;
    auto app = createLoginAppTest(env);
    auto loginApp = dynamic_cast<LoginApp*>(app.get());

    loginApp->setUsername("admin");
    loginApp->setPassword("admin");
    loginApp->handleLogin();

    BOOST_CHECK_EQUAL(loginApp->getStatusText()->text().toUTF8(), "Pomyślne logowanie.");
}

BOOST_AUTO_TEST_CASE(TestInvalidCredentials) {
    Wt::Test::WTestEnvironment env;
    auto app = createLoginAppTest(env);
    auto loginApp = dynamic_cast<LoginApp*>(app.get());

    loginApp->setUsername("incorrect_username");
    loginApp->setPassword("incorrect_password");
    loginApp->handleLogin();

    BOOST_CHECK_EQUAL(loginApp->getStatusText()->text().toUTF8(), "Niepoprawna nazwa użytkownika lub hasło.");
    BOOST_CHECK_EQUAL(loginApp->getStatusText()->styleClass(), "NotOkStatus-Wt-WText");
}

BOOST_AUTO_TEST_CASE(TestRedirectionToUserPanel) {
    Wt::Test::WTestEnvironment env;
    auto app = createLoginAppTest(env);
    auto loginApp = dynamic_cast<LoginApp*>(app.get());

    loginApp->handleRedirectionToUser();

    BOOST_CHECK_EQUAL(Wt::WApplication::instance()->internalPath(), "/");
}

BOOST_AUTO_TEST_SUITE_END()
