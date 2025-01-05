#pragma once
#include <vector>
#include <unordered_map>
//#include "user.h"
#include "message_manager.h"
//#include "TrieNode.h"
#include "TCP.h"
#include "db.h"


//#define LOGINLENGTH 10
#define DEB_Svr true 


class Chat {
 public:    
    Chat();  
    ~Chat();
    void Start();    
      
    void LoginProcedure(std::stringstream & ss);
    void SignUpProcedure(std::stringstream & ss);

    //bool Login(std::string login, char pass[], int pass_length);
    //bool SignUp(std::string login, char pass[], int pass_length);
    void Logout(std::stringstream & ss);
    bool IsLogged(std::stringstream & ss);
    void ShowAllMessages();
    void ShowPersonMessages(std::stringstream & ss);
    void ShowAllUsers();
    void SendMessageToAll(std::stringstream & ss);
    void SendPersonalMessage(std::stringstream & ss);  

 private:
//   void PrintVector(const std::vector<std::string>& arr) const;
//   void Print_sha1(uint*); //debug 
    void ParseMessage(const std::string& msg);
 private:
    bool chat_work_ = true; 
   // TrieNode::TrieNode* t = nullptr; // Тринода для автоопределения
  //  std::unordered_map<std::string, uint*> users_;
    std::vector<Message> messages_;
    std::vector<std::string> logged_users_;    
    ConnectManager* CM_ = nullptr;
    Database* db_conn_ = nullptr;
    std::string reply_msg_;
};
    
