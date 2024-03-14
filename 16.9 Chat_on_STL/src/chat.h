#pragma once
#include <vector>
#include <unordered_map>
#include "user.h"
#include "message.h"
#include "TrieNode.h"
#include "sha1.h"

//#define LOGINLENGTH 10

class Chat {
 public:    
    Chat();  
    void Start();    
      
    void ShowMenu();  

    void LoginProcedure();
    void SignUpProcedure();

    bool Login(std::string login, char pass[], int pass_length);
    void SignUp(std::string login, char pass[], int pass_length);
    void Logout();

    void ShowUserMenu();
    void ShowAllMessages();
    void ShowPersonMessages();
    void ShowAllUsers();
    
    void SendMessageToAll();
    void SendPersonalMessage();  
    
 private:
   void PrintVector(const std::vector<std::string>& arr) const;
   void Print_sha1(uint*); //debug 

 private:
   std::string current_user_;
   bool chat_work_ = true; 
   TrieNode::TrieNode* t = nullptr; // Тринода для автоопределения
   std::unordered_map<std::string, uint*> users_;
   std::vector<Message> messages_;
};
