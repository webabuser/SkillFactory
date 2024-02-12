#pragma once
#include "dynamic_array.h"
#include "user.h"
#include "message.h"
#include "TrieNode.h"
#include "hashtable.h"

#define LOGINLENGTH 10

class Chat {
 public:    
    Chat();  
    void Start();    
      
    void ShowMenu();
  

    void LoginProcedure();
    void SignUpProcedure();

    bool Login(char login[LOGINLENGTH], char pass[], int pass_length);
    void SignUp(char login[LOGINLENGTH], char pass[], int pass_length);

    void Logout();

    void ShowUserMenu();
    void ShowAllMessages();
    void ShowPersonMessages();
    void ShowAllUsers();
    
    void SendMessageToAll();
    void SendPersonalMessage();  
    
 private:
   void PrintVector(const std::vector<std::string>& arr) const;
   void Print_sha1(uint*);

 private:
   DynamicArray<Message> messages_;
   char current_user_[LOGINLENGTH]{'\0'}; 
   bool chat_work_ = true; 
   TrieNode::TrieNode* t = nullptr; // Тринода для автоопределения
   HashTable users_{}; // хэштаблица для хранения логинов и паролей
};
