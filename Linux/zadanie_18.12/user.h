#pragma once
#include <string>
#include <fstream>

using namespace std;

class User {
 public:
    User()=default;
	 
    User(std::string name, std::string login, std::string pass)
        : _name(name), _login(login), _pass(pass){}
    
    friend std::fstream & operator>>(std::fstream& out, User& obj);
    friend std::fstream & operator<<(std::fstream& in, const User& obj); //for input to file
    friend std::ostream & operator <<(std::ostream& os, const User& obj); //for cout


 private:	
    std::string _name;
    std::string _login;
    std::string _pass;
};

std::fstream & operator>>(std::fstream & out, User& obj)
{
    out >> obj._name;
    out >> obj._login;
    out >> obj._pass;
    out.ignore(2, '\n');
    return out;	
}

std::fstream & operator << (std::fstream & in, const User & obj)
{
    in << obj._name;
    in <<' ';    
    in << obj._login;
    in <<' ';    
    in << obj._pass;
    in <<'\n';

    return in;    
}

std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << "Name: " <<  obj._name;
	os << ",  ";
	os << "Login: " <<  obj._login;
	os << ",  ";
	os << "Password: " <<  obj._pass;
	os << ".";
	return os;
}

