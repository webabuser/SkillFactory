#pragma once
#include <vector>
#include <unordered_map>
#include "ClientManager.h"

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
   std::string current_user_;
   bool chat_work_ = true; 
   ConnectManager CM;
};
