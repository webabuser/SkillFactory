#pragma once
#include <vector>
#include <unordered_map>
#include "user.h"
#include "message.h"
#include "TCP.h"
#include "db.h"
#include "logger.h"

//#define LOGINLENGTH 10
#define DEB_Svr false 


class Chat {
 public:    
    Chat();  
    ~Chat();
    void Start();    
      
 private:
    void LoginProcedure(std::stringstream & ss);
    void SignUpProcedure(std::stringstream & ss);

    void Logout(std::stringstream & ss);
    bool IsLogged(std::stringstream & ss);
    void ShowAllMessages();
    void ShowPersonMessages(std::stringstream & ss);
    void ShowAllUsers();
    void ShowLoggedUsers();
    void SendMessageToAll(std::stringstream & ss);
    void SendPersonalMessage(std::stringstream & ss);  
    void ParseMessage(const std::string& msg);

 private:
    bool chat_work_ = true; 
    std::vector<std::string> logged_users_;    
    ConnectManager* CM_ = nullptr;
    Database* db_conn_ = nullptr;
    std::string reply_msg_;
    Logger logfile_;
};
    
