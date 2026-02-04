#include "usermanager.h"
#include "config.cpp"
#include <QDebug>
#include <string>

UserManager::UserManager(QObject *parent) : QObject(parent)
{
    /*
    //Registering MySQL driver
    if(!QSqlDatabase::driver().contains("QMYSQL")){
        lastErrorString = "MySQL driver not found!";
        qDebug() << "Установите: sudo apt install libqt5sql5-mysql";
    }
    */
}

UserManager::~UserManager()
{
    if(db.isOpen()){
        db.close();
    }
}

bool UserManager::connectToDatabase()
{
    using namespace std::string_literals;

    Config cf{"config.ini"};

    const std::string s_basetype = cf.getValue("basetype", "mysql");
    const std::string s_host = cf.getValue("host", "localhost");
    const std::string s_user = cf.getValue("user");
    const std::string s_db_name = cf.getValue("db");
    const std::string s_password = cf.getValue("password");
    //закрываем файл конфига

    QString sql_driver;
    if(s_basetype == "mysql"s) sql_driver = "QMYSQL";
    else if(s_basetype == "postgresql"s) sql_driver = "QPSQL";
    else {
        qDebug() << "Wrong basetype.";
        return false;
    }

    db = QSqlDatabase::addDatabase(sql_driver, "chat_connection");

    QString host = QString::fromStdString(s_host);
    QString user = QString::fromStdString(s_user);
    QString db_name = QString::fromStdString(s_db_name);
    QString pass = QString::fromStdString(s_password);

    qDebug() << host << user << db_name << pass;

    db.setHostName(host);
    db.setDatabaseName(db_name);
    db.setUserName(user);
    db.setPassword(pass);

    if(!db.open()){
        lastErrorString = db.lastError().text();
        //emit databaseError(lastErrorString);
        return false;
    }
    return true;
}

QList<User> UserManager::getAllUsers()
{
    QList<User> users;

    if(!db.isOpen()){
        lastErrorString = "Database not connected";
        return users;
    }

    QSqlQuery query("SELECT * FROM users", db);

    while(query.next()){
        User user;
        user.id_ = query.value("id").toUInt();
        user.login_ = query.value("login").toString();
        user.name_ = query.value("name").toString();
        user.surname_ = query.value("surname").toString();
        user.status_ = query.value("status").toString();

        users.append(user);
    }

    if(query.lastError().isValid()){
        lastErrorString = query.lastError().text();
       // emit databaseError(lastErrorString);
        qDebug() <<"getallusers query error " << lastErrorString;
    }

    return users;
}

QList<Message> UserManager::getUserMessages(quint8 user_id)
{
    QList<Message> messages;
    if(!db.isOpen()) return messages;

    QSqlQuery query(db);
//   query.prepare("SELECT * FROM messages WHERE sender_id = :user_id");


    query.prepare("SELECT \
                      m.*, \
                      DATE_FORMAT(m.created, '%Y-%m-%d %H:%i') AS created_formatted,\
                      (SELECT login FROM users WHERE id = m.sender_id) AS sender_login, \
                      (SELECT login FROM users WHERE id = m.receiver_id) AS receiver_login \
                   FROM messages AS m \
                   WHERE m.sender_id = :user_id");


    query.bindValue(":user_id", user_id);


    if(query.exec()){
        while(query.next()){
            Message msg;
            msg.id_ = query.value("id").toUInt();
            msg.sender_id_ = query.value("sender_id").toUInt();
            msg.receiver_id_ = query.value("receiver_id").toUInt();
            msg.text_ = query.value("text").toString();
            msg.created_ = query.value("created_formatted").toString();
            msg.status_ =  query.value("status").toString();
            msg.sender_login_ = query.value("sender_login").toString();
            msg.receiver_login_ = query.value("receiver_login").toString();

            messages.append(msg);
        }
    }else{
        qDebug() << "Sqlerror of messages " << query.lastError().text();
    }

    return messages;
}

bool UserManager::blockUser(quint8 user_id, const QString &reason)
{
    if(!db.isOpen()) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE users SET status = 'blocked', "
                  "blocked_at = NOW(), block_reason = :reason "
                  "WHERE id = :user_id AND status != 'deleted'");
    query.bindValue(":user_id", user_id);
    query.bindValue(":reason", reason);

    return query.exec();
}

bool UserManager::unblockUser(quint8 user_id, const QString &reason)
{
    if(!db.isOpen()) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE users SET status = 'active', "
                  "block_reason = :reason "
                  "WHERE id = :user_id AND status != 'deleted' AND status = 'blocked'");
    query.bindValue(":user_id", user_id);
    query.bindValue(":reason", reason);

    return query.exec();
}

bool UserManager::deleteUser(quint8 user_id, const QString &reason)
{
    if(!db.isOpen()) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE users SET status = 'deleted', "
                  "blocked_at = NOW(), block_reason = :reason "
                  "WHERE id = :user_id AND status != 'deleted'");
    query.bindValue(":user_id", user_id);
    query.bindValue(":reason", reason);

    return query.exec();
}













