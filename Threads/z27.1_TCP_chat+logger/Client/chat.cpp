#include <string>
#include <cassert>
#include <cstring>
#include <iostream>
#include "chat.h"
#include <sstream>
#include <algorithm>

using namespace std::string_literals;

Chat::Chat()
{
}

Chat::~Chat(){
    std::cout << "Chat destructor" <<std::endl;
}    

void Chat::Start()
{
    std::cout << "Добро пожаловать в чат!" <<std::endl;
    std::cout << "Программа Чат не наделена проверкой ввода данных, максимальное кол-во символов ввода 9." << std::endl;

    while (chat_work_) 
    { 
        ShowMenu();

        while(!current_user_.empty())
        {
            ShowUserMenu(); 
        }
    }    
}


void Chat::ShowMenu()
{
    std::cout << "\033[0;35mВыберите опцию: Регистрация юзера (1), Вход по логину и паролю (2), Выключить сервер (9), Завершить программу клиент (0):\033[0m ";

    char choise;
    std::cin >> choise;
    
    switch(choise)
    {
        case '1':
            SignUpProcedure();
            break;
        case '2':
            LoginProcedure();
            break;
        case '3':
            Logout();
            break;
        case '0':
            KillServer();
            chat_work_ = false;
            break;
        case '9':
            KillServer();
            chat_work_ = false;
            break;
        default:
            std::cout << "Вы не верно выбрали опцию, попробуйте снова." << std::endl;
            std::cin.ignore(32000,'\n');
            break;
    }
}


void Chat::LoginProcedure()
{
    if(!current_user_.empty())
    {
        std::cout << "Вы вошли как " << current_user_<< std::endl;
        return;
    } 
    
    std::string login;
    std::string password;
    
    std::cout << "Введите ваш логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    
    password = sha1_string(password);

    std::string message = "Login " + login + " " + password;

    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    
    if(DEB_Cl) std::cout << "DEB_Cl:" << server_reply << std::endl;
   
    std::istringstream ss(server_reply);
   
    std::string serv_command;
    int serv_res;
    std::string serv_msg;
     
    ss >> serv_command >> serv_res;
   
    if(serv_res) current_user_ = login;

    std::getline(ss,serv_msg);

    std::cout << serv_msg << std::endl;
}


void Chat::SignUpProcedure()
{
    std::string login;
    std::string password;
    
    std::cout << "Введите ваш логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;

    password = sha1_string(password);

    std::cout << password << std::endl;
  //  exit(0);

    std::string message = "SignUp " + login + " " + password;

    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
   
    std::string op;
    bool serv_res;
    std::string serv_msg;

    std::istringstream ss{server_reply};
    ss >> op >>serv_res;
    ss.get(); // считываем один пробел после bool serv_res;
    std::getline(ss, serv_msg);

    if(DEB_Cl) std::cout << "DEB_Cl: " << op <<"|"<< serv_res <<"|" << serv_msg << std::endl;
    std::cout << serv_msg << std::endl; 
}


void Chat::Logout()
{
    std::string message = "Logout " + current_user_;
    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    if(DEB_Cl) std::cout << "DEB_Cl:" << server_reply << std::endl;

    std::istringstream ss(server_reply);
    std::string serv_command;
    std::string last_logged_user;
    std::string serv_msg;
    int serv_res = 0;
    ss >>serv_command >> serv_res >> last_logged_user;
    
    std::getline(ss, serv_msg);

    if(serv_res){
        std::cout << last_logged_user << serv_msg  << std::endl;
        current_user_.clear();
    }
   
}


void Chat::ShowUserMenu() 
{
    if(current_user_.empty()) return;

    std::cout << PURPLE << "Показать все сообщения (1), Показать личные сообщения(2), " 
                 "Послать сообщения в чат(3), Послать личное сообщение(4), Выйти(0): " << PURPLEend;
     
//    std::cin.clear();
//    std::cin.ignore(32000, '\n'); // очистим если что то есть

    int choise;
    std::cin >> choise;
    
    switch(choise){
        case 1:
            ShowAllMessages();
            break;
        case 2:
            ShowPersonMessages();
            break;
        case 3:
            SendMessageToAll();
            break;
        case 4:
            SendPersonalMessage();
            break;
        case 0:
            Logout();
            break;
        default:
            std::cout << "Вы не верно сделали выбор, повторите > ";
            break;
    }                 
}


std::vector<std::string> Chat::ShowLoggedUsers()
{  
    std::string message = "LoggedUsers"s;

    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    
    std::istringstream ss(server_reply);

    std::vector<std::string>logged_users;
    while(true){
        std::string w;
        ss >> w;
        if(w != " ") logged_users.push_back(w);

        if(!ss.eof()){
            std::cout << w << ", ";
        } else {
            std::cout << w <<": ";
            break;
        }    
    }    
    return logged_users;    
}

void Chat::SendMessageToAll()
{
    std::cout << "Напишите сообщение для всех:";
    std::string msg;
    std::cin.ignore(32000, '\n'); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, msg);
    
    std::string message = "SendMessageToAll " + current_user_ + " " + msg;
    CM.SendMessage(message);
    CM.Receive();
    std::string serv_reply = CM.getBuffer();
    
    std::string serv_command;
    bool serv_res;
    std::string serv_msg;

    std::istringstream ss(serv_reply);
    ss >> serv_command >> serv_res;
    std::getline(ss, serv_msg);
    
    std::cout << serv_msg << std::endl;
}


void Chat::SendPersonalMessage()
{
    
    std::cout << "Выберите пользователя: ";
    
    std::vector<std::string> logged_users = ShowLoggedUsers();
    
    std::string to_user;
    std::cin.ignore(32000, '\n'); //Очистка буфера перед следующим вводом.
    std::cin >> to_user;

    if (std::find(logged_users.begin(), logged_users.end(), to_user) == logged_users.end()) {
        std::cout <<"Вы не верно ввели имя пользователя" << std::endl;
        return; 
    }
    
    std::cout << "Напишите сообщение этому пользователю: ";

    std::string msg;
    std::cin.ignore(); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, msg);
   
    std::string message = "PersonalMessage " + current_user_ + " "s + to_user + " "s + msg; 
    if(DEB_Cl) std::cout <<"DEB_Cl: " << message << std::endl;
    
    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    
    std::istringstream ss(server_reply);
//    std::string serv_command;
//    bool serv_res;
//    std::string serv_msg;

    std::cout << server_reply << std::endl;
}


void Chat::ShowAllMessages()
{  
    std::string message = "ShowAllMessages"s;

    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    
    //std::istringstream ss(server_reply);
    std::cout << server_reply << std::endl;
}


void Chat::ShowPersonMessages()
{
    std::string message = "ShowPersonMessages "s + current_user_;

    CM.SendMessage(message);
    CM.Receive();
    std::string server_reply = CM.getBuffer();
    
    //std::istringstream ss(server_reply);
    std::cout << server_reply << std::endl;
}


void Chat::KillServer(){
    std::string message = "killserver";
    CM.SendMessage(message);
}


