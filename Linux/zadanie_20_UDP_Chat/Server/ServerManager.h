//https://www.opennet.ru/docs/RUS/socket/node3.html
/*
   struct sockaddr_in {
   sa_family_t    sin_family;
   in_port_t      sin_port;
   struct in_addr sin_addr;
   unsigned char  sin_zero[8];
   };

   struct in_addr {
   in_addr_t  s_addr; //где in_addr_t это целый беззнаковый тип длиной 32 бита
   };
*/

#pragma once
#include <arpa/inet.h> //htonl....
#include <sys/socket.h>//struct sockaddr_in
 
#define MESSAGE_BUFFER 4096 // Максимальный размер буфера для приема и передачи
#define PORT 7777 // Номер порта, который будем использовать для приема и передачи 

class ConnectManager 
{
 public:
    ConnectManager();
    ~ConnectManager();

    void Receive();
    void Reply(const std::string & msg);
    std::string getBuffer(); 

 private:
    void SockIni();
 
 private:   
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    int socket_file_descriptor;
    // socklen_t sockaddr_length; //Describes the length of a socket address. This is an integer type of at least 32 bits.
    char buffer[MESSAGE_BUFFER]; 
    char message[MESSAGE_BUFFER];
};


/* 
int main() {
   // processRequest();
     ConnectManager CM;
    
    return 0;
}
*/
