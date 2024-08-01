#pragma once
#include <string>
#include <fstream>

using namespace std;

class Message {
 public:
    Message()=default;
	 
    Message(std::string sender, std::string receiver, std::string text)
        : _sender(sender), _receiver(receiver), _text(text) {}
    
    friend std::fstream & operator>>(std::fstream& out, Message& obj);
    friend std::fstream & operator<<(std::fstream& in, const Message& obj); //for input to file
    friend std::ostream & operator <<(std::ostream& os, const Message& obj); //for cout

 private:	
    std::string _text;
    std::string _sender;
    std::string _receiver;
};

std::fstream & operator>>(std::fstream & out, Message& obj)
{
    out >> obj._sender;
    out >> obj._receiver;
    out.ignore(1);
 
    getline(out, obj._text );
    //  out.ignore(2, '\r');
    return out;	
}

// input into file
std::fstream & operator << (std::fstream & in, const Message & obj)
{
    in << obj._sender;
    in <<'\t';    
    in << obj._receiver;
    in <<'\t';
    in << obj._text;
  
    return in;    
}

std::ostream& operator <<(std::ostream& os, const Message& obj)
{
	os << "Sender: " <<  obj._sender << " | " ;
	os << "Receiver: " <<  obj._receiver << " | ";
	os << "Message: " <<  obj._text ;

	return os;
}

