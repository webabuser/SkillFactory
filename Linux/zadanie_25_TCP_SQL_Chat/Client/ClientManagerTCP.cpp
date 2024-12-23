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
#include "ClientManagerTCP.h"
#define DEB_CMCl true

using namespace std;
 
ConnectManager::ConnectManager(){
        SockIni();  
        Connection();
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
   socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

   if(socket_file_descriptor  >= 0){
      if(DEB_CMCl) std::cout << "DEB_CMCl: Socket created" << std::endl;
   } else {
        cout << "Creation of Socket failed!" << endl;
        exit(1);
   }
}


void ConnectManager::Connection(){
    // Установим соединение с сервером
    if(connect(socket_file_descriptor, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        if(DEB_CMCl) std::cout << "DEB_CMCl: Something went wrong Connection Failed" << std::endl;
        exit(1);
    }
    else
    {
        if(DEB_CMCl) std::cout << "DEB_CMCl: Connection has been established with server" << std::endl;
    }
} 
    
    
void ConnectManager::Receive(){   
    // Ждем ответа от сервера
    read(socket_file_descriptor, buffer, sizeof(buffer));
    cout << "Data received from server: " << message << endl;   

    if(DEB_CMCl) cout << "DEB_CMCL: Message Received From Server: " << endl;
    // cout <<  buffer << endl;
} 
    

void ConnectManager::SendMessage(const std::string& msg){
    strcpy(message, msg.c_str());

    ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes < 0){
        if(DEB_CMCl) std::cout << "DEB_CMCL: Hе удалось послать сообщение." << std::endl;
    }else{
       if(DEB_CMCl) std::cout << "DEB_CMCL: Cообщение успешно послано " << bytes <<" байт." << std::endl;
    }
}   


std::string ConnectManager::getBuffer(){
    return std::string(buffer);
}

