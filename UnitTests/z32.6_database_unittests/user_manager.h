#pragma once
#include "idatabase.h"

class UserManager {
public:
    UserManager(IDatabase& db) : db_(db) {}  // Принимает любой IDatabase
    
    bool initialize(const std::string& connStr) {
        return db_.connect(connStr);
    }

    std::string getUsers() {
        return db_.getData("SELECT * FROM users");
    }

    bool updateUserName(int id, const std::string& name) {
        std::string query = "UPDATE users SET name='" + name + 
                          "' WHERE id=" + std::to_string(id);
        return db_.updateData(query);
    }

private:
    IDatabase& db_;
};
