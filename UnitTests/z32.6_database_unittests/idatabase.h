#pragma once
#include <string>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual bool connect(const std::string& connectionStr) = 0;
    virtual bool disconnect() = 0;
    virtual std::string getData(const std::string& query) = 0;
    virtual bool updateData(const std::string& query) = 0;
};
