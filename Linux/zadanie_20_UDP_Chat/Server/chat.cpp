#include <string>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include "chat.h"


Chat::Chat(){
}

Chat::~Chat(){
    std::cout << "Chat destructor" <<std::endl;
}    

void Chat::Start()
{
    std::cout << "Ceрвер чата запущен и ждет сообщений от клиента!" << std::endl;

    while(chat_work_){
        CM.Receive();
        ParseMessage(CM.getBuffer());
        CM.Reply(reply_msg_);
    }    
}

bool Chat::SignUp(std::string login, char pass[], int pass_length)
{
    // std::pair<std::unordered_map<std::string, uint*>::iterator, bool>
    auto res =  users_.emplace(login, sha1(pass, pass_length));
    return res.second;
}


bool Chat::Login(std::string login, char pass[], int pass_length)
{
    uint* sh = sha1(pass, pass_length);

    if (users_.find(login) != users_.end())
    {
        if (memcmp(users_.find(login)->second, sh, SHA1HASHLENGTHBYTES) == 0) // 0 if equal
        {   
            delete[] sh;
            return true;
        }
    }

    delete[] sh;            
    return false;
}


void Chat::LoginProcedure(std::stringstream & ss)
{   
    std::string login;
    std::string password;
    ss >> login >> password; 
      
    const char* c_login = login.c_str();
    const char* c_password = password.c_str();

    assert(login.size() == std::strlen(c_login));
    assert(std::equal(login.begin(), login.end(), c_login));
    assert(std::equal(c_login, c_login + login.size(), login.begin()));
    assert('\0' == *(c_login + login.size()));

    if (Login(login, (char*)c_password, std::strlen(c_password)))
    {
        logged_users_.push_back(login);
        
        reply_msg_ = "Login 1 Вы успешно залогинились - " + login;
        return;
    }

    reply_msg_ = "Login 0 Вы не верно набрали либо логин, либо пароль.";
}


void Chat::SignUpProcedure(std::stringstream& ss)
{
      std::string login;
      std::string password;
                     
      ss >> login >> password;

    if(users_.find(login) != users_.end())
    {      reply_msg_= "SignUp 0 Данный логин уже существует, выберите новый или авторизуйтесь.";
    
      std::cout << reply_msg_ << std::endl;
      return;
    }

    const char* c_password = password.c_str();

    // Добавляем пльзователя и пароль в unordered map
   if(SignUp(login, (char*)c_password, password.size())){
   
       reply_msg_ = "SignUp 1 Пользователь успешно зарегистрирован";
   }else{
       reply_msg_ = "SignUp 0 Регистрация не успешна!";
   }
}


void Chat::Logout(std::stringstream & ss)
{
    std::string logged_user;
    ss >> logged_user;
    
    auto it = std::find(logged_users_.begin(), logged_users_.end(),logged_user);
    if(it != logged_users_.end()){
        logged_users_.erase(it);
        reply_msg_ = "Logout 1 "+logged_user+" разлогинился.";
    }else{
        reply_msg_ = "Logout 0 "+logged_user+" попытка выйти не успешна.";
    }
}


void Chat::ShowAllUsers()
{ 
    for(auto user : logged_users_){
        reply_msg_ += user + " ";
    }    
    reply_msg_.pop_back();    
}


void Chat::SendMessageToAll(std::stringstream & ss)
{   
    std::string from_user;
    std::string to_user = "all";
    std::string msg;
    ss >> from_user;
    std::getline(ss, msg);

    Message messagetoall{std::move(from_user), to_user, msg};
    messages_.push_back(messagetoall);
    reply_msg_ = "SendMessageToAll 1 От " + from_user + " Сообщение ВСЕМ послано.";
}


void Chat::SendPersonalMessage(std::stringstream & ss)
{
    std::string from_user;
    std::string to_user;
    std::string msg;
    ss >> from_user >> to_user;
    std::getline(ss, msg);

    Message messagetoall{from_user, to_user, msg};
    messages_.push_back(messagetoall);
    
    reply_msg_= "PersonalMessage 1 Персональное сообщение "+ from_user +" "+ to_user +" было послано"; 
}


void Chat::ShowAllMessages()
{
    for(size_t i = 0; i < messages_.size(); ++i){
        reply_msg_ +=  messages_[i].getText();
        reply_msg_ += "\n";
    }
}


void Chat::ShowPersonMessages(std::stringstream & ss)
{
    std::string user;
    ss >> user;

    for(size_t i = 0; i < messages_.size(); ++i){
        if(messages_[i].getTo() == std::move(user))
        reply_msg_ += (messages_[i].getText() + ",\n ");
    }
    reply_msg_ += "\n";
};


bool Chat::IsLogged(std::stringstream & ss)
{
    std::string login;
    ss >> login;

    const auto it = find(logged_users_.begin(), logged_users_.end(), login);
    if(*it == login){
        reply_msg_ = "IsLogged 1";
        return true;
    }
    else {
        reply_msg_ = "IsLogged 0";
        return false;
    }
}


void Chat::ParseMessage(const std::string& msg)
{
    using namespace std::string_literals;
    
    std::stringstream ss(msg, std::ios_base::in);

    std::string command;
    ss >> command;
    //Очищаем предыдущий ответ клиенту
    reply_msg_="";
   
    if(command == "SignUp"s){
         SignUpProcedure(ss);
    } else if(command == "Login"s){     
         LoginProcedure(ss);
    } else if(command == "IsLogged"s){
        IsLogged(ss);
    } else if(command == "LoggedUsers"s){
        ShowAllUsers();
    } else if(command == "PersonalMessage"s){
        SendPersonalMessage(ss);
    } else if(command == "ShowAllMessages"s){
        ShowAllMessages();
    } else if(command == "ShowPersonMessages"s){
        ShowPersonMessages(ss);
    } else if(command == "SendMessageToAll"s){
        SendMessageToAll(ss);
    } else if(command == "Logout"s){
        Logout(ss);
    } else if(command == "killserver"s){
        chat_work_ = false;
    }
}  

