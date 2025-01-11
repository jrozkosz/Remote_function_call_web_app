// Jakub Rozkosz

#define BOOST_TEST_MODULE SqlDatabaseTest
#include <boost/test/included/unit_test.hpp>
#include "../db/Database.h"

BOOST_AUTO_TEST_CASE(TestSqlDatabaseInitialization) {
    BOOST_CHECK_NO_THROW(SqlDatabase& db = SqlDatabase::instance(":memory:"));
}

BOOST_AUTO_TEST_CASE(TestGetUserId) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.createUserTable();
    db.insertUser("test@example.com", "password123", 100);

    BOOST_CHECK_EQUAL(db.getUserId("test@example.com"), 1);

    BOOST_CHECK_EQUAL(db.getUserId("nonexistent@example.com"), -1);
}

BOOST_AUTO_TEST_CASE(TestCreateUserTable) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    BOOST_CHECK_NO_THROW(db.createUserTable());
}

BOOST_AUTO_TEST_CASE(TestInsertUser) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.createUserTable();

    BOOST_CHECK_NO_THROW(db.insertUser("test1@example.com", "password1234", 100));
}

BOOST_AUTO_TEST_CASE(TestChangeUserBudget) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.createUserTable();
    db.insertUser("test2@example.com", "password12345", 100);

    BOOST_CHECK_NO_THROW(db.changeUserBudget("test2@example.com", 200));
    BOOST_CHECK_EQUAL(db.getUserBudget("test2@example.com"), 200);
}

BOOST_AUTO_TEST_CASE(TestGetAllUsers) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.deleteUserTable();
    db.createUserTable();
    db.insertUser("test3@example.com", "password789", 100);
    db.insertUser("test4@example.com", "password456", 200);

    BOOST_CHECK_EQUAL(db.getAllUsers().size(), 2);
}

BOOST_AUTO_TEST_CASE(TestGetUserBudget) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.createUserTable();
    db.insertUser("test5@example.com", "password100", 100);

    BOOST_CHECK_EQUAL(db.getUserBudget("test5@example.com"), 100);
}

BOOST_AUTO_TEST_CASE(TestDeleteUser) {
    SqlDatabase& db = SqlDatabase::instance(":memory:");
    db.createUserTable();
    db.insertUser("test6@example.com", "password200", 100);
    int users_count = db.getAllUsers().size();

    BOOST_CHECK_NO_THROW(db.deleteUser("test6@example.com"));
    BOOST_CHECK_EQUAL(db.getAllUsers().size(), users_count-1);
}
