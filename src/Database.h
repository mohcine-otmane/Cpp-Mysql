#pragma once
#include <mariadb/mysql.h>
#include <string>

class Database {
private:
    MYSQL mysql;
    MYSQL* connection;
    std::string lastError;

public:
    Database();
    ~Database();
    bool connect(const std::string& host, const std::string& user, 
                const std::string& password, const std::string& database);
    bool validateLogin(const std::string& username, const std::string& password);
    void disconnect();
    std::string getLastError() const { return lastError; }
};