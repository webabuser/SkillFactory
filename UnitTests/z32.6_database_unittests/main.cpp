#include "user_manager.h"
#include "mock_database.h"
#include <gtest/gtest.h>
#include "mysql_database.h"

TEST(UserManagerTest, MockUsage) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

//    EXPECT_CALL(mockDb, connect(testing::_))
//        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(mockDb, connect("test_connection"))
        .WillOnce(testing::Return(true));

    // Запрещаем все остальные вызовы connect
//    EXPECT_CALL(mockDb, connect(testing::_))
  //      .Times(0);

    EXPECT_CALL(mockDb, getData("SELECT * FROM users"))
        .WillOnce(testing::Return("1,Alex;2,Bob"));

    ASSERT_TRUE(manager.initialize("test_connection"));
    ASSERT_EQ(manager.getUsers(), "1,Alex;2,Bob");
}

//Тест успешного подключения к БД
TEST(UserManagerTest, SuccessfulConnection) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

    // Ожидаем вызов connect с любым аргументом и возвращаем true
    EXPECT_CALL(mockDb, connect(testing::_))
        .WillOnce(testing::Return(true));

    ASSERT_TRUE(manager.initialize("any_connection_string"));
}

//Тест ошибки подключения
TEST(UserManagerTest, ConnectionFailure) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

    // Ожидаем вызов connect и возвращаем false (имитация ошибки)
    EXPECT_CALL(mockDb, connect("invalid_conn_str"))
        .WillOnce(testing::Return(false));

    ASSERT_FALSE(manager.initialize("invalid_conn_str"));
}

// Тест получения данных
TEST(UserManagerTest, GetUsersReturnsData) {
    MockDatabase mockDb;
    UserManager manager(mockDb);
    const std::string mockData = "1,Alex;2,Bob";

    // Ожидаем вызов getData с точным запросом
    EXPECT_CALL(mockDb, getData("SELECT * FROM users"))
        .WillOnce(testing::Return(mockData));

    ASSERT_EQ(manager.getUsers(), mockData);
}

//Тест пустого результата
TEST(UserManagerTest, GetUsersReturnsEmpty) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

    // Ожидаем вызов getData и возвращаем пустую строку
    EXPECT_CALL(mockDb, getData(testing::_))
        .WillOnce(testing::Return(""));

    ASSERT_TRUE(manager.getUsers().empty());
}

//Тест обновления данных с проверкой аргументов
TEST(UserManagerTest, UpdateUserNameWithCorrectQuery) {
    MockDatabase mockDb;
    UserManager manager(mockDb);
    const std::string expectedQuery = 
        "UPDATE users SET name='Alex' WHERE id=42";

    // Ожидаем ТОЧНО этот запрос
    EXPECT_CALL(mockDb, updateData(expectedQuery))
        .WillOnce(testing::Return(true));

    ASSERT_TRUE(manager.updateUserName(42, "Alex"));
}

//Тест обработки ошибки обновления
TEST(UserManagerTest, UpdateUserNameFails) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

    // Ожидаем любой запрос, но возвращаем false
    EXPECT_CALL(mockDb, updateData(testing::_))
        .WillOnce(testing::Return(false));

    ASSERT_FALSE(manager.updateUserName(1, "InvalidName"));
}

//Тест последовательных вызовов
TEST(UserManagerTest, MultipleCalls) {
    MockDatabase mockDb;
    UserManager manager(mockDb);

    // Ожидаем строгий порядок вызовов:
    testing::InSequence seq;
    EXPECT_CALL(mockDb, connect("conn_str"))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(mockDb, getData("SELECT * FROM users"))
        .WillOnce(testing::Return("data"));
//    EXPECT_CALL(mockDb, disconnect())
//        .WillOnce(testing::Return(true));

    manager.initialize("conn_str");
    manager.getUsers();
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
