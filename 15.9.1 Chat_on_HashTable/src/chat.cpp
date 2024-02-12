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
    //users_ = new HashTable();
   
}

void Chat::Start()
{
    std::cout << "����� ���������� � ���!" << std::endl;
    std::cout << "��������� ��� �� �������� ��������� ����� ������, ������������ ���-�� �������� ����� 9." << std::endl;

    while (chat_work_) 
    { 
        ShowMenu();
        while(current_user_[0] != '\0')
        {
            ShowUserMenu(); 
        }
    }    
}

void Chat::SignUp(char login[LOGINLENGTH], char pass[], int pass_length)
{
    users_.add(login, sha1(pass, pass_length));

    std::cout << "����������� '" << login << "' �������." << std::endl;
}

bool Chat::Login(char login[LOGINLENGTH], char pass[], int pass_length)
{
    uint* sh = sha1(pass, pass_length);

    //Print_sha1(sh);

    if (users_.find(login) != nullptr) {

        //Print_sha1(users_.find(login));

        if (memcmp(users_.find(login), sh, SHA1HASHLENGTHBYTES) == 0) // 0 if equal
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
    std::cout << "�������� �����: ����������� ����� (1), ���� �� ������ � ������ (2), Quit (0): ";

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
            std::cout << "�� �� ����� ������� �����, ���������� �����." << std::endl;
            std::cin.ignore(32000,'\n');
            break;
    }
}


void Chat::LoginProcedure()
{
    if(current_user_[0] != '\0') {
        std::cout << "�� ����� ��� " << current_user_<< std::endl;
        return;
    } 
    
    std::string login;
    std::string password;
    
    std::cout << "������� ��� �����: ";
   
     // ���� ���� ������������ Trienode ��� ������������ ������� �� ��������� ��������
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

            std::cout << "������ ������� �� ������������ ���������, ����� �����, ���� ������� (" << found_words.size() <<") ���������� ������� �������: ";

            std::cin.clear();
            std::cin.ignore(32000, '\n'); // ������� ���� ��� �� ����

            size_t var;
            std::cin >> var;
            if (var < found_words.size())
            {
                std::cout << ((var < found_words.size()) ? "��������� �����: " + found_words[var] : "�� ������� �� �����") << std::endl;
                selected_word = found_words[var];
                if(!selected_word.empty()) break;
            }
            else if(var == found_words.size())
            {
                std::cout << "������ ���������� ������� �������: ";
                continue;
            }
            else {
                std::cout << "�� ������ ����� �� �����. " << std::endl;
            }

        }
        else {
            std::cout << "���������� ������ �� �������. " << std::endl;
            
            break;
        }
    }


    if (!selected_word.empty()) {
        login = selected_word;
        std::cout << "������: ";

        std::cin.clear();
        std::cin.ignore(32000, '\n'); // ������� ���� ��� �� ����
        std::cin >> password;

    }
    else {
        std::cout << "�� �� ������� ����� ������� ���� � �������. ����!" << std::endl;
        return;
    }

    
    const char* c_login = login.c_str();
    const char* c_password = password.c_str();

    assert(login.size() == std::strlen(c_login));
    assert(std::equal(login.begin(), login.end(), c_login));
    assert(std::equal(c_login, c_login + login.size(), login.begin()));
    assert('\0' == *(c_login + login.size()));

    if (Login((char*)c_login, (char*)c_password, std::strlen(c_password)))
    {
        strcpy_s(current_user_, LOGINLENGTH, c_login);

        std::cout << current_user_ << " �� ������� ������������." << std::endl;
        return;
    }

    std::cout << "�� �� ����� ������� ���� �����, ���� ������."<< std::endl;
}


void Chat::SignUpProcedure()
{
    std::string login;
    std::string password;
    
    std::cout << "������� ��� �����: ";
    std::cin >> login;
    std::cout << "������: ";
    std::cin >> password;
    
    const char* c_login = login.c_str();

    assert(login.size() == std::strlen(c_login));
    assert(std::equal(login.begin(), login.end(), c_login));
    assert(std::equal(c_login, c_login + login.size(), login.begin()));
    assert('\0' == *(c_login + login.size()));

    if(users_.find(login.c_str()))
    {
        std::cout << "������ ����� ��� ����������, �������� ����� ��� �������������."<< std::endl;
        return;
    }

    //��������� ����� ������������� � �������, ��� ������������ ���������������
    insert(t, login);

    const char* c_password = password.c_str();

    // ��������� ����������� � ������ � ����������
    SignUp((char*)c_login, (char*)c_password, password.size());

    std::cout << std::endl;
}


void Chat::Logout(){
    for (int i = 0; i < LOGINLENGTH; ++i)
    {
        current_user_[i] = '\0';
    }
}


void Chat::ShowUserMenu() {
    if(current_user_[0] == '\0') {
        return;
    }
    
    std::cout << "�������� ��� ��������� (1), �������� ������ ���������(2), " 
                 "������� ��������� � ���(3), ������� ������ ���������(4), �����(0): ";
     
    std::cin.clear();
    std::cin.ignore(32000, '\n'); // ������� ���� ��� �� ����

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
            std::cout << "�� �� ����� ������� �����, ��������� > ";
            break;
    }                 
}


void Chat::ShowAllUsers()
{    
    PrintVector(users_.FindAllLogins());
}


void Chat::SendMessageToAll()
{
    std::cout << "�������� ��������� ��� ����:";
    std::string message;
    std::cin.ignore(32000, '\n'); //������� ������ ����� ��������� ������.
    std::getline(std::cin, message);
    
    Message messagetoall(std::move(std::string(current_user_)), "all", message );
    messages_.PushBack(messagetoall);
}

void Chat::SendPersonalMessage()
{
    std::cout << "�������� ������������: ";
    ShowAllUsers();
    
    int login_index;
    std::cin >> login_index;

    std::string login = users_.FindAllLogins()[login_index];
    
    std::cout << "�������� ��������� ����� ������������: ";

    std::string message;
    std::cin.ignore(); //������� ������ ����� ��������� ������.
    std::getline(std::cin, message);
    
    Message messagetoall(std::move(std::string(current_user_)), login, message );
    messages_.PushBack(messagetoall);    
}

void Chat::ShowAllMessages()
{
    for(size_t i = 0; i < messages_.getLength(); ++i){
        std::cout << messages_[i].getText() << ", ";
    }
    std::cout << std::endl;
}

void Chat::ShowPersonMessages()
{
    for(size_t i = 0; i < messages_.getLength(); ++i){
        if(messages_[i].getTo() == std::move(std::string(current_user_)))
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
