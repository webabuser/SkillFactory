#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h> //htonl....
#include <sys/socket.h>
#include "ServerManager.h"

using namespace std;


ConnectManager::ConnectManager(){
        SockIni();  
}


ConnectManager::~ConnectManager(){
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    std::cout << "Connection closed" << std::endl;
};


void ConnectManager::SockIni()
{
   servaddr.sin_family = AF_INET; // Используем IPv4
   servaddr.sin_port = htons(7777); // Зададим порт для соединения
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    
   // Создадим UDP сокет 
   socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

   if(socket_file_descriptor  >= 0){
       std::cout << "Socket created" << std::endl;
   }

   // Привяжем сокет 
   int bind_result = bind(socket_file_descriptor, (struct sockaddr*)&servaddr, sizeof(servaddr));
   if(bind_result >= 0) std::cout << "Socket binded \n"; 
} 


void ConnectManager::Receive ()
{
    std::cout << "Ждем сообщения от клиента" << std::endl;
    
    // Длина сообщения от клиента
    socklen_t clientaddr_length = sizeof(clientaddr);
    // std::cout << "clientaddr_length-" << clientaddr_length << std::endl;

    int message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer),/* MSG_DONTWAIT || MSG_ERRQUEUE*/ 0, (struct sockaddr*)&clientaddr, &clientaddr_length);

    buffer[message_size] = '\0';
   
    cout << "Message Received from Client: " << ntohl(clientaddr.sin_addr.s_addr) << " - "<< buffer << endl;
}    


void ConnectManager::Reply(const std::string & msg)
{
    // ответим клиенту
    strcpy(message, msg.c_str());
        
    sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    cout << "Mes-ge Sent Success-y to client (sendto): " << message << endl;
 }    


std::string ConnectManager::getBuffer()
{
    return std::string(buffer);
}
