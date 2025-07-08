#pragma once
#include "idatabase.h"
#include <gmock/gmock.h>

class MockDatabase : public IDatabase {
public:
    MOCK_METHOD(bool, connect, (const std::string&), (override));
    MOCK_METHOD(bool, disconnect, (), (override));
    MOCK_METHOD(std::string, getData, (const std::string&), (override));
    MOCK_METHOD(bool, updateData, (const std::string&), (override));
};
