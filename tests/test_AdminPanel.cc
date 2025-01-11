// Jakub Rozkosz

#define BOOST_TEST_MODULE AdminPanelAppTests
#include <boost/test/included/unit_test.hpp>
#include <Wt/Test/WTestEnvironment.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include "../webapp/AdminPanel.h"
#include "../db/Database.h"

std::unique_ptr<Wt::WApplication> createAdminPanelAppTest(const Wt::WEnvironment& env) {
    return std::make_unique<AdminPanelApp>(env);
}

BOOST_AUTO_TEST_SUITE(AdminPanelAppTests)

BOOST_AUTO_TEST_CASE(TestValidBudgetChange) {
    Wt::Test::WTestEnvironment env;
    auto app = createAdminPanelAppTest(env);
    auto adminApp = dynamic_cast<AdminPanelApp*>(app.get());

    adminApp->handleBudgetChange(1, "test@example.com", "500");

    BOOST_CHECK_EQUAL(adminApp->getMessageBoxText().get()->text().toUTF8(), "Budżet użytkownika: test@example.com został pomyślnie zmieniony.");
}

BOOST_AUTO_TEST_CASE(TestInvalidNegativeBudgetChange) {
    Wt::Test::WTestEnvironment env;
    auto app = createAdminPanelAppTest(env);
    auto adminApp = dynamic_cast<AdminPanelApp*>(app.get());

    adminApp->handleBudgetChange(1, "test@example.com", "-100");

    BOOST_CHECK_EQUAL(adminApp->getMessageBoxText().get()->text().toUTF8(), "Wprowadzany budżet nie może być liczbą ujemną.");
}

BOOST_AUTO_TEST_CASE(TestInvalidNonNumericBudgetChange) {
    Wt::Test::WTestEnvironment env;
    auto app = createAdminPanelAppTest(env);
    auto adminApp = dynamic_cast<AdminPanelApp*>(app.get());

    adminApp->handleBudgetChange(1, "test@example.com", "abc");

    BOOST_CHECK_EQUAL(adminApp->getMessageBoxText().get()->text().toUTF8(), "Wprowadzany budżet musi być liczbą całkowitą.");
}

BOOST_AUTO_TEST_CASE(TestInvalidMaxIntBudgetChange) {
    Wt::Test::WTestEnvironment env;
    auto app = createAdminPanelAppTest(env);
    auto adminApp = dynamic_cast<AdminPanelApp*>(app.get());

    adminApp->handleBudgetChange(1, "test@example.com", "2147483648");

    BOOST_CHECK_EQUAL(adminApp->getMessageBoxText().get()->text().toUTF8(), "Wprowadzany budżet musi być mniejszy niż 2147483647 (maksymalna wartość dla integera).");
}

BOOST_AUTO_TEST_CASE(TestSuccessfulLogOut) {
    Wt::Test::WTestEnvironment env;
    auto app = createAdminPanelAppTest(env);
    auto adminApp = dynamic_cast<AdminPanelApp*>(app.get());

    adminApp->handleLogOut();

    BOOST_CHECK(!Wt::WApplication::instance()->environment().cookies().count("session"));
}

BOOST_AUTO_TEST_SUITE_END()
