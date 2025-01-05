#include <string>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include "chat.h"

Chat::Chat()
{
//    t = new TrieNode::TrieNode();
//    std::cout << "Конструктор чата" << std::endl;  
    
    db_conn_ = Database::GetSinglton();
    
    CM_ = new ConnectManager;
}


Chat::~Chat(){
    delete db_conn_;
    delete CM_;
    std::cout << "Chat destructor" <<std::endl;
}    

void Chat::Start()
{
    std::cout << "Ceрвер чата запущен и ждет сообщений от клиента!" << std::endl;

    while(chat_work_){
        CM_->Receive();
        ParseMessage(CM_->getBuffer());
        CM_->Reply(reply_msg_);
    }    
}


void Chat::LoginProcedure(std::stringstream & ss)
{   
    std::string login;
    std::string password;
                     
    ss >> login >> password;
    // __asm__ __volatile__("int3");
    reply_msg_ = "";

    std::string query = "SELECT id, login  FROM users WHERE login = '" + login + "'";
   
    if (db_conn_->DbQuery(query) == false) {
       if(DEB_Svr) std::cerr << "DEB_Svr: line "<<__LINE__<<" "<<__FILE__<<", query false." << std::endl;
       reply_msg_ = "Login 0, не верный SQL запрос.";
       return;
    }

    std::map<std::size_t, std::vector<std::string>> result = db_conn_->GetResult();
    if(result.empty())
    {    
        logged_users_.push_back(login);
        reply_msg_ = "Login 0 Пользователя с таким логином не существует. Попытайтесь снова." ;
        return;
    }
        
    std::string query2 = "SELECT hash FROM hashes WHERE user_id = '" + result[0][0] + "'";
    if (db_conn_->DbQuery(query2) == false) {
       if(DEB_Svr) std::cerr << "DEB_Svr: line "<<__LINE__<<" "<<__FILE__<<", query false." << std::endl;
       reply_msg_ = "Login 0, не верный SQL запрос.";
       return;
    }

    std::map<std::size_t, std::vector<std::string>> result2 = db_conn_->GetResult();
    
    if(result2[0][0] != password){
        reply_msg_  = "Login 0 Не верный пароль. Попытайтесь снова.";
        return;
    } 

    logged_users_.push_back(login);
    reply_msg_ = "Login 1 Вы успешно залогинились - " + login;
}


void Chat::SignUpProcedure(std::stringstream& ss)
{
    std::string login;
    std::string password;
                     
    ss >> login >> password;
    // __asm__ __volatile__("int3");
    std::string query = "SELECT id, login  FROM users WHERE login = '" + login + "'";
   
    if (db_conn_->DbQuery(query) == false) {
       if(DEB_Svr) std::cerr << "DEB_Svr: line "<<__LINE__<<" "<<__FILE__<<", query false." << std::endl;
        reply_msg_ = "SignUp 0 Регистрация не успешна, не верный SQL запрос.";
        return;
    }    

    if(db_conn_->CheckSelResult()){    
        reply_msg_ = "SignUp 0 Такой пользователь уже зарегистрирован, попытайтесь снова." ;
        return;
    }



    std::string query2 = "INSERT INTO users (login) VALUES ('" + login + "');";
    std::string query3 = "UPDATE hashes SET hash ='" + password + "' WHERE user_id = LAST_INSERT_ID();";

    if (db_conn_->DbQuery(query2) == false) {
       if(DEB_Svr) std::cerr << "DEB_Svr: line "<<__LINE__<< " "<<__FILE__<<" query2 false." << std::endl;
    }    
    if (db_conn_->DbQuery(query3) == false) {
       if(DEB_Svr) std::cerr << "DEB_Svr: line "<<__LINE__<<" " <<__FILE__ <<"  query3 false." << std::endl;
    }

    if(db_conn_->UDIresult()){
       if(DEB_Svr) std::cout << "Пользователь успешно зарегистрирован" << std::endl;    
       reply_msg_ = "SignUp 1 Пользователь успешно зарегистрирован";
    } else {
        if(DEB_Svr)  std::cout << "Пользователь не зарегистрирован" << std::endl;
        reply_msg_ = "SignUp 0 Пользователь Не зарегистрирова"; 
    }    
   return;
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

    Message_manager MM{};

    /*
    Message messagetoall{from_user, to_user, msg};
    messages_.push_back(messagetoall);
    
    reply_msg_= "PersonalMessage 1 Персональное сообщение "+ from_user +" "+ to_user +" было послано"; 
*/
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

bool Chat::IsLogged(std::stringstream & ss){
    
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


void Chat::ParseMessage(const std::string& msg){
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

/*
void Chat::Print_sha1(uint* sh)
{ 
    for (int i = 0; i < 5; ++i) std::cout << std::hex <<  sh[i] <<" ";
    std::cout << std::endl;
}
*/
/*
void Chat::PrintVector(const std::vector<std::string>& arr) const 
{
    int i = 0;

    auto iter = arr.begin();

	for (auto value : arr)
    {   

		std::cout << i++ << "." << value;

        if (++iter != arr.cend())
        {
            std::cout <<", ";
        }
        else
        {
            std::cout <<".";
        }
	}

    std::cout << std::endl;
}
*/


