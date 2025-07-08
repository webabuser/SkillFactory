#pragma once
#include "idatabase.h"
#include <mysql/mysql.h> 

class MySQLDatabase : public IDatabase {
public:
    MySQLDatabase() : conn_(nullptr) {}
    ~MySQLDatabase() { disconnect(); }

    bool connect(const std::string& connectionStr) override {
        conn_ = mysql_init(nullptr);
        if (!conn_) return false;

        std::string host;
        std::string user;
        std::string pass;
        std::string db;

        if (!mysql_real_connect(
                conn_, 
                host.empty() ? nullptr : host.c_str(),
                user.empty() ? nullptr : user.c_str(),
                pass.empty() ? nullptr : pass.c_str(),
                db.empty() ? nullptr : db.c_str(),
                0, nullptr, 0)) {
            disconnect();
            return false;
        }
        return true;
    }

    bool disconnect() override {
        if (conn_) {
            mysql_close(conn_);
            conn_ = nullptr;
            return true;
        }
        return false;
    }

    std::string getData(const std::string& query) override {
        if (mysql_query(conn_, query.c_str())) {
            return "Error: " + std::string(mysql_error(conn_));
        }

        MYSQL_RES* res = mysql_store_result(conn_);
        if (!res) return "";

        std::string data;
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            data += row[0]; // Упрощённо берём первый столбец
            data += ";";
        }
        mysql_free_result(res);
        return data;
    }

    bool updateData(const std::string& query) override {
        return mysql_query(conn_, query.c_str()) == 0;
    }

private:
    MYSQL* conn_;
};
