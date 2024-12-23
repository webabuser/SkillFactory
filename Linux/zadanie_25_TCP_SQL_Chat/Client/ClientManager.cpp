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
*
*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h> //htonl....
#include <sys/socket.h>
#include "ClientManager.h"
#define DEB_CMCl false

using namespace std;
 
ConnectManager::ConnectManager(){
        SockIni();  
        Connection();
//        while(1){
//            SendMessage();
 //           Receive();
 //       }
}

ConnectManager::~ConnectManager(){
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
   if(DEB_CMCl) std::cout << "DEB_CMCl: Connection closed" << std::endl;
};


void ConnectManager::SockIni(){
   servaddr.sin_family = AF_INET; // Используем IPv4
   servaddr.sin_port = htons(7777); // Зададим порт для соединения
   servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
   // Создадим UDP сокет 
   socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

   if(socket_file_descriptor  >= 0){
      if(DEB_CMCl) std::cout << "DEB_CMCl: Socket created" << std::endl;
   }
}

void ConnectManager::Connection(){
    // Установим соединение с сервером
    if(connect(socket_file_descriptor, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        if(DEB_CMCl) std::cout << "DEB_CMCl: Something went wrong Connection Failed" << endl;
        exit(1);
    }
} 
    
    
void ConnectManager::Receive(){   
   
    if(DEB_CMCl) cout << "DEB_CMCL: Message Received From Server: " << endl;
    
    recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
   
   // cout <<  buffer << endl;
} 
    

void ConnectManager::SendMessage(const std::string& msg){
//    cout << "Enter a message you want to send to the server: " << endl;
   
   // cin.getline(message, MESSAGE_BUFFER, '\n');
    const char* msg_c = msg.c_str();      
   
    ssize_t message_length = sendto(socket_file_descriptor, msg_c, msg.size(), 0, nullptr, sizeof(servaddr));
    if(message_length < 0){
       if(DEB_CMCl) std::cout << "DEB_CMCL: Hе удалось послать сообщение." << std::endl;
    }else{
       if(DEB_CMCl) std::cout << "DEB_CMCL: Cообщение успешно послано " << message_length <<" байт." << std::endl;
    }

    
    /*
    if (strcmp(message, "end") == 0)
    {
        cout << "Client work is done.!" << endl;
        close(socket_file_descriptor);
        exit(0);
    } else  {
//       sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(servaddr));
         cout << "Message sent successfully to the server: " <<  message << endl;
    }
*/    
}   


std::string ConnectManager::getBuffer(){
    return std::string(buffer);
}

