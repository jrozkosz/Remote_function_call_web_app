#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <vector>
#include <tuple>

class SqlDatabase {
private:
    SqlDatabase(const std::string& db_name);
    sqlite3* db_;
    char* zErrMsg_ = 0;

public:
    static SqlDatabase& instance(const std::string& db_name = "zpr_db.db") {
        static SqlDatabase db_singleton(db_name);
        return db_singleton;
    }
    ~SqlDatabase();
    SqlDatabase(const SqlDatabase&) = delete;
    SqlDatabase& operator=(const SqlDatabase&) = delete;

    int getUserId(const std::string& email);
    int getUserBudget(const std::string& email);
    std::vector<std::tuple<int, std::string, int>> getAllUsers();
    void createUserTable();
    void insertUser(const std::string& email, const std::string& password, const int budget);
    void changeUserBudget(const std::string& email, const int budget);
    void deleteUser(const std::string& email);
    void deleteUserTable();
};

#endif
