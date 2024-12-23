#pragma once
#include <vector>
#include <unordered_map>
//#  include "user.h"
//#include "message.h"
//#include "TrieNode.h"
//#include "sha1.h"
#include "ClientManagerTCP.h"
//#define LOGINLENGTH 10
#define DEB_Cl false  
#define CEAN "\033[0;36m"
#define CEANend "\033[0m"
#define PURPLE "\033[0;35m"
#define PURPLEend "\033[0m"

class Chat {
 public:    
    Chat();  
    ~Chat();
    void Start();    
      
    void ShowMenu();  

    void LoginProcedure();
    void SignUpProcedure();
    void Logout();

    void ShowUserMenu();
    void ShowAllMessages();
    void ShowPersonMessages();
    void SendMessageToAll();
    void SendPersonalMessage();  
    std::vector<std::string> ShowLoggedUsers();
    void KillServer();
 private:
//   void PrintVector(const std::vector<std::string>& arr) const;
//   void Print_sha1(uint*); //debug 

 private:
   std::string current_user_;
   bool chat_work_ = true; 
//   TrieNode::TrieNode* t = nullptr; // Тринода для автоопределения
//   std::vector<Message> messages_;
     ConnectManager CM;
};
