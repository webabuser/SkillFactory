#include <iostream>
#include "chat.h"	
//#include <locale.h>


int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
//    setlocale(LC_ALL, "russian");

    Chat chat;
    chat.Start();
    
    
    std::cout<<"Server чат завершен!" << std::endl;

    return 0;
}
