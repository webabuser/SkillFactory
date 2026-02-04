#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QString>


struct User {

    User() = default;
    User(const QString& login, const QString& password)
        : login_(login), password_(password){
    }

    User(const User& us) = default;

   // const QString& getLogin() const {return login_;}
   // const QString& getPassword() const {return password_;}
   // void setUserPassword(const QString& password) {password_ = password;}
   // friend std::ostream& operator<<(std::ostream& out, const User& usr);

    quint8 id_;
    QString login_;
    QString password_;
    QString name_;
    QString surname_;
    QString email_;
    QString created_;
    QString status_;
};

struct Message {
    quint8 id_;
    quint8 sender_id_;
    quint8 receiver_id_;
    QString text_;
    QString created_;
    QString status_;
    QString sender_login_;
    QString receiver_login_;
};

class UserManager : public QObject
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);
    ~UserManager();

    //Connection to Database
    bool connectToDatabase();

    //User operations
    QList<User> getAllUsers();
    QList<Message> getUserMessages(quint8 user_id);
    bool blockUser(quint8 user_id, const QString &reason);
    bool unblockUser(quint8 user_id, const QString &reason);
    bool deleteUser(quint8 user_id, const QString &reason);
 private:
    QSqlDatabase db;
    QString lastErrorString;
};

#endif // USERMANAGER_H
