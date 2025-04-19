#include "Database.h"
#include <string>
#include <cstring>

Database::Database() : connection(nullptr) {
    mysql_init(&mysql);
    if (!&mysql) {
        lastError = "Failed to initialize MySQL object";
    }
}

Database::~Database() {
    disconnect();
}

bool Database::connect(const std::string& host, const std::string& user,
                      const std::string& password, const std::string& database) {
    connection = mysql_real_connect(&mysql, host.c_str(), user.c_str(),
                                  password.c_str(), database.c_str(), 0, nullptr, 0);
    if (!connection) {
        lastError = mysql_error(&mysql);
        return false;
    }
    return true;
}

bool Database::validateLogin(const std::string& username, const std::string& password) {
    if (!connection) {
        lastError = "Not connected to database";
        return false;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(connection);
    if (!stmt) {
        lastError = mysql_error(connection);
        return false;
    }

    const char* query = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)username.c_str();
    bind[0].buffer_length = username.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)password.c_str();
    bind[1].buffer_length = password.length();

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND result[1];
    long long count = 0;
    memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_LONGLONG;
    result[0].buffer = &count;

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_fetch(stmt) != 0) {
        lastError = mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    mysql_stmt_close(stmt);
    return count > 0;
}

void Database::disconnect() {
    if (connection) {
        mysql_close(connection);
        connection = nullptr;
    }
}