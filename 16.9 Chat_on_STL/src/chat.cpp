#include <string>
#include <string.h>
#include <conio.h> //_getch()
#include <cassert>
#include <cstring>

#include "chat.h"

void Chat::Print_sha1(uint* sh)
{ 
    for (int i = 0; i < 5; ++i) std::cout << std::hex <<  sh[i] <<" ";
    std::cout << std::endl;
}

Chat::Chat()
{
    t = new TrieNode::TrieNode();  
}

void Chat::Start()
{
    std::cout << "Добро пожаловать в чат!" << std::endl;
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

void Chat::SignUp(std::string login, char pass[], int pass_length)
{
    users_.emplace(login, sha1(pass, pass_length));

    std::cout << "Регистрация '" << login << "' успешна." << std::endl;
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


void Chat::ShowMenu()
{
    std::cout << "Выберите опцию: Регистрация юзера (1), Вход по логину и паролю (2), Quit (0): ";

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
   
     // Блок кода использующий Trienode для автозагрузки логинов по введенным символам
    std::string search_word;
    std::string selected_word;
    char gh;

    while (true)
    {
        using namespace TrieNode;

        gh = _getch();
        std::cout << gh <<"  ";

        search_word.push_back((char)gh);

        std::vector<std::string> found_words;
        SearchWords(t, search_word, found_words);

        if (!found_words.empty())
        {
            PrintVector(found_words);

            std::cout << "Можете выбрать из предлагаемых вариантов, нажав номер, либо нажмите (" << found_words.size() <<") продолжить вводить символы: ";

            std::cin.clear();
            std::cin.ignore(32000, '\n'); // очистим если что то есть

            size_t var;
            std::cin >> var;
            if (var < found_words.size())
            {
                std::cout << ((var < found_words.size()) ? "Выбранное слово: " + found_words[var] : "Вы выбрали не верно") << std::endl;
                selected_word = found_words[var];
                if(!selected_word.empty()) break;
            }
            else if(var == found_words.size())
            {
                std::cout << "Можете продолжить вводить символы: ";
                continue;
            }
            else {
                std::cout << "Вы нажали какую то херню. " << std::endl;
            }

        }
        else {
            std::cout << "Совпадений логина не найдено. " << std::endl;
            
            break;
        }
    }


    if (!selected_word.empty()) {
        login = selected_word;
        std::cout << "Пароль: ";

        std::cin.clear();
        std::cin.ignore(32000, '\n'); // очистим если что то есть
        std::cin >> password;
    }
    else {
        std::cout << "Вы не выбрали логин который есть в системе. Пока!" << std::endl;
        return;
    }

    
    const char* c_login = login.c_str();
    const char* c_password = password.c_str();

    assert(login.size() == std::strlen(c_login));
    assert(std::equal(login.begin(), login.end(), c_login));
    assert(std::equal(c_login, c_login + login.size(), login.begin()));
    assert('\0' == *(c_login + login.size()));

    if (Login(login, (char*)c_password, std::strlen(c_password)))
    {
        current_user_ = login;

        std::cout << current_user_ << " Вы успешно залогинились." << std::endl;
        return;
    }

    std::cout << "Вы не верно набрали либо логин, либо пароль."<< std::endl;
}


void Chat::SignUpProcedure()
{
    std::string login;
    std::string password;
    
    std::cout << "Введите ваш логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;

    if(users_.find(login) != users_.end())
    {
        std::cout << "Данный логин уже существует, выберите новый или авторизуйтесь."<< std::endl;
        return;
    }

    //Добавляем имена пользователей в триноду, для последующего автоопределения
    insert(t, login);

    const char* c_password = password.c_str();

    // Добавляем пльзователя и пароль в unordered map
    SignUp(login, (char*)c_password, password.size());

    std::cout << std::endl;
}


void Chat::Logout()
{
    current_user_.clear();
}


void Chat::ShowUserMenu() 
{
    if(current_user_.empty()) return;

    std::cout << "Показать все сообщения (1), Показать личные сообщения(2), " 
                 "Послать сообщения в чат(3), Послать личное сообщение(4), Выйти(0): ";
     
    std::cin.clear();
    std::cin.ignore(32000, '\n'); // очистим если что то есть

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


void Chat::ShowAllUsers()
{    
    int i=0;
    for (auto& pair : users_)
    {
        std::cout << i  << ". " << pair.first << "  ";

        ++i;
    }
    std::cout << std::endl;
}


void Chat::SendMessageToAll()
{
    std::cout << "Напишите сообщение для всех:";
    std::string message;
    std::cin.ignore(32000, '\n'); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, message);
    
    Message messagetoall(std::move(current_user_), "all", message );
    messages_.push_back(messagetoall);
}

void Chat::SendPersonalMessage()
{
    std::cout << "Выберите пользователя: ";
    ShowAllUsers();
    
    std::string login;
    std::cin >> login;

    if (users_.find(login) == users_.end()) {
        std::cout <<"Вы не верно ввели имя пользователя" << std::endl;
        return; 
    }
    
    std::cout << "Напишите сообщение этому пользователю: ";

    std::string message;
    std::cin.ignore(); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, message);
    
    Message messagetoall(std::move(current_user_), login, message );
    messages_.push_back(messagetoall);    
}

void Chat::ShowAllMessages()
{
    for(size_t i = 0; i < messages_.size(); ++i){
        std::cout << messages_[i].getText() << ", ";
    }
    std::cout << std::endl;
}

void Chat::ShowPersonMessages()
{
    for(size_t i = 0; i < messages_.size(); ++i){
        if(messages_[i].getTo() == std::move(current_user_))
        std::cout << messages_[i].getText() << ", ";
    }
    std::cout << std::endl;
};


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
