#pragma once
#include <string>
#include <vector>
#include <map>

#include "mysql/mysql.h"
#include "config.cpp"

using namespace std::string_literals;

class Database { 
 public:
    //Запрещаем конструктор и оператор копирования
    Database(Database& other) = delete;
    void operator=(const Database& other) = delete;

    static Database* GetSinglton(/*const std::string&*/);
    bool DbQuery(const std::string&);   
    std::map<size_t, std::vector<std::string>> GetResult();

    void dbInit();

 protected: 
     Database();
     ~Database();
 
 private:

    static Database* db_;
    MYSQL mysql_; 
    MYSQL_RES* res_;
	MYSQL_ROW row_;
    
    const char* host_;
    const char* user_;
    const char* db_name_;
    const char* password_;

    std::map<size_t, std::vector<std::string>> result;
};

