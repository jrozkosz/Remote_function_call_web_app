#include <iostream>
#include "Database.h"

using namespace std;

SqlDatabase::SqlDatabase(const string& db_name) {
    int rc = sqlite3_open(db_name.c_str(), &db_);
    if (rc) {
        throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db_)));
    } else {
        cout << "Opened database successfully" << endl;
    }
}

int SqlDatabase::getUserId(const string& email) {
    const char* sqlGetUserId = "SELECT id FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sqlGetUserId, -1, &stmt, 0) != SQLITE_OK) {
        throw runtime_error("Failed to prepare statement: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int userId = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return userId;
    } else {
        return -1;
    }
}

void SqlDatabase::createUserTable() {
    const char* sqlCreateTable = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "email TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL,"
        "budget INTEGER NOT NULL);";

    auto rc = sqlite3_exec(db_, sqlCreateTable, 0, 0, &zErrMsg_);

    if (rc != SQLITE_OK) {
        throw runtime_error("SQL error: " + string(zErrMsg_));
    } else {
        cout << "Table created successfully" << endl;
    }
}

void SqlDatabase::insertUser(const string& email, const string& password, const int budget) {
    const char* sqlInsertUser = "INSERT INTO users (email, password, budget) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sqlInsertUser, -1, &stmt, 0) != SQLITE_OK) {
        throw runtime_error("Failed to prepare statement: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, budget);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw runtime_error("Failed to execute statement: " + string(sqlite3_errmsg(db_)));
    } else {
        cout << "User inserted successfully" << endl;
    }

    sqlite3_finalize(stmt);
}

void SqlDatabase::changeUserBudget(const string& email, const int budget) {
    int userId = getUserId(email);

    const char* sqlUpdateUserBudget = "UPDATE users SET budget = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sqlUpdateUserBudget, -1, &stmt, 0) != SQLITE_OK) {
        throw runtime_error("Failed to prepare statement: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_int(stmt, 1, budget);
    sqlite3_bind_int(stmt, 2, userId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw runtime_error("Failed to execute statement: " + string(sqlite3_errmsg(db_)));
    } else {
        cout << "User budget changed successfully" << endl;
    }

    sqlite3_finalize(stmt);
}

vector<tuple<int, string, int>> SqlDatabase::getAllUsers() {
    const char* sqlGetAllUsers = "SELECT id, email, budget FROM users;";
    sqlite3_stmt* stmt;
    vector<tuple<int, string, int>> users;

    int rc = sqlite3_prepare_v2(db_, sqlGetAllUsers, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        throw runtime_error("SQL error: " + string(sqlite3_errmsg(db_)));
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int userId = sqlite3_column_int(stmt, 0);
        const unsigned char *userEmail  = sqlite3_column_text(stmt, 1);
        int userBudget = sqlite3_column_int(stmt, 2);
        users.emplace_back(userId, reinterpret_cast<const char*>(userEmail), userBudget);
    }

    if (rc != SQLITE_DONE) {
        throw runtime_error("SQL error: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_finalize(stmt);

    return users;
}

int SqlDatabase::getUserBudget(const string& email) {
    const char* sqlGetUserBudget = "SELECT budget FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sqlGetUserBudget, -1, &stmt, 0) != SQLITE_OK) {
        throw runtime_error("Failed to prepare statement: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int userBudget = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return userBudget;
    } else {
        throw runtime_error("No user found with the given email.");
    }
}

void SqlDatabase::deleteUser(const string& email) {
    const char* sqlDeleteUser = "DELETE FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db_, sqlDeleteUser, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        throw runtime_error("SQL error: " + string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw runtime_error("Failed to execute statement: " + string(sqlite3_errmsg(db_)));
    } else {
        cout << "User deleted successfully" << endl;
    }

    sqlite3_finalize(stmt);
}

void SqlDatabase::deleteUserTable() {
    const char* sqlDropTable = "DROP TABLE IF EXISTS users;";
    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(db_, sqlDropTable, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        throw runtime_error("SQL error: " + string(zErrMsg));
    } else {
        cout << "Table deleted successfully" << endl;
    }
}

SqlDatabase::~SqlDatabase() {
    sqlite3_close(db_);
}