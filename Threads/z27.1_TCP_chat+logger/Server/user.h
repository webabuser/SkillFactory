#pragma once
#include <iostream>
#include <string>
#include "db.h"


class User {
 public:    
    User();
    User(const std::string& login, const std::string& password)
        : login_(login), password_(password){          
    }
    
    User(const User& us) = default;
    
    const std::string& getLogin() const {return login_;}
    const std::string& getPassword() const {return password_;}
    
    void setUserPassword(const std::string& password) {password_ = password;}
    
    friend std::ostream& operator<<(std::ostream& out, const User& usr);
    
 private:     
    Database* db_ptr_ = nullptr;

    size_t id_;
    std::string login_;
    std::string password_;
    std::string name_;
    std::string surname_;
    std::string email_;
    std::string created_;
};

