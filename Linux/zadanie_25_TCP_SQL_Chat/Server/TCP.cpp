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
#include "TCP.h"

using namespace std;
 
ConnectManager::ConnectManager(){
    SockIni();  

   

   while(true){
       Linstening();

    
    
       Accepting(); 


       int pid = fork();
       if(pid == 0) {
            std::cout << "дочерний процесс " << getpid() << std::endl;
            break;
       }else if(pid > 0){
           std::cout << "Родительский процес зацикливается" <<getpid() << std::endl;
           continue;
       }
    }

   std::cout << ">>>>>>>>> "<< std::endl;
}

ConnectManager::~ConnectManager(){
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    std::cout << "Connection closed" << std::endl;
};

void ConnectManager::SockIni(){
   servaddr.sin_family = AF_INET; // Используем IPv4
   servaddr.sin_port = htons(PORT); // Зададим порт для соединения
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    
   // Создадим TCP сокет 
   socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

   if(socket_file_descriptor  >= 0){
       std::cout << "Socket created" << std::endl;
   }else{
       std::cout << "Socket creation failed!" << std::endl;
       exit(1);
   }
   // Привяжем сокет 
   int bind_status = bind(socket_file_descriptor, (struct sockaddr*)&servaddr, sizeof(servaddr));
   if(bind_status >= 0){
       std::cout << "Socket binded \n"; 
   }else{
        std::cout << "Socket binding failed!" << std::endl;
        exit(1);
   }
}


void ConnectManager::Linstening(){
//Поставим сервер на прием данных
    connection_status = listen(socket_file_descriptor, 2);
    
    if(connection_status == -1) {
        std::cout << "Socket is unable to listen for new connections!" << std::endl;
        exit(1);
    } else {
        std::cout << "Server is listening for new connections." << std::endl;
    }

}

void ConnectManager::Accepting(){
   
    sockaddr_length = sizeof(clientaddr);
    connection = accept(socket_file_descriptor, (struct sockaddr *)&clientaddr, &sockaddr_length);
    
    if(connection == -1)  {
        cout << "Server is unable to accept the data from client.!" << endl;
    exit(1);
    } else {
        std::cout << "Server accepts connection: " << connection << endl;
    }
}

void ConnectManager::Receive (){

   // bzero(buffer, |FER);
    read(connection, buffer, MESSAGE_BUFFER);
    cout << "Data received from client: " <<  buffer << endl;
   // bzero(message, MESSAGE_LENGTH);


}    

void ConnectManager::Reply(const std::string & msg){
    // ответим клиенту
   // cout << "Reply to client: "<< msg << endl;
    strcpy(message, msg.c_str());
   // message_size = msg.size()+1;
        
    //cin.getline(message, MESSAGE_BUFFER, '\n');

  
    ssize_t bytes = write(connection, message, sizeof(message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0)  {
       cout << "Data successfully sent to the client.!" << endl;
    }
}    


std::string ConnectManager::getBuffer(){
    return std::string(buffer);
}
