#pragma once
#include <vector>
#include <unordered_map>
#include "message.h"
#include "sha1.h"
#include "ServerManager.h"
//#define LOGINLENGTH 10
#define DEB_Svr false

class Chat {
 public:    
    Chat();  
    ~Chat();
    void Start();    
      
    void LoginProcedure(std::stringstream & ss);
    void SignUpProcedure(std::stringstream & ss);

    bool Login(std::string login, char pass[], int pass_length);
    bool SignUp(std::string login, char pass[], int pass_length);
    void Logout(std::stringstream & ss);
    bool IsLogged(std::stringstream & ss);
    void ShowAllMessages();
    void ShowPersonMessages(std::stringstream & ss);
    void ShowAllUsers();
    void SendMessageToAll(std::stringstream & ss);
    void SendPersonalMessage(std::stringstream & ss);  

 private:
    void ParseMessage(const std::string& msg);

 private:
    bool chat_work_ = true; 
    std::unordered_map<std::string, uint*> users_;
    std::vector<Message> messages_;
    std::vector<std::string> logged_users_;    
    ConnectManager CM;
    std::string reply_msg_;
};
     
