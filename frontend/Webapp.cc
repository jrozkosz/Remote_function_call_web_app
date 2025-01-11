#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <Wt/WEnvironment.h>
#include "AdminLogin.h"
#include "AdminPanel.h"
#include "UserRegister.h"
#include "../db/Database.h"

using namespace std;

unique_ptr<Wt::WApplication> createLoginApp(const Wt::WEnvironment& env) {
    return make_unique<LoginApp>(env);
}

unique_ptr<Wt::WApplication> createAdminPanelApp(const Wt::WEnvironment& env) {
    return make_unique<AdminPanelApp>(env);
}

unique_ptr<Wt::WApplication> createUserRegisterApp(const Wt::WEnvironment& env) {
    return make_unique<UserRegisterApp>(env);
}

int main(int argc, char **argv) {
    try {
        SqlDatabase& db = SqlDatabase::instance("zpr_db.db");
        db.createUserTable();

        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::EntryPointType::Application, createUserRegisterApp, "/");
        server.addEntryPoint(Wt::EntryPointType::Application, createLoginApp, "/login");
        server.addEntryPoint(Wt::EntryPointType::Application, createAdminPanelApp, "/admin");

        server.run();
    } catch (const Wt::WServer::Exception& e) {
        cerr << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "exception: " << e.what() << endl;
        return 1;
    }
}
