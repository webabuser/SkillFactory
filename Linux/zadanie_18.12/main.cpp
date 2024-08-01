/*
Напишите программу, которая сможет считывать из файла при своей загрузке и записывать в файл состояния объектов классов User и Message (для каждого класса свой файл):
Сделайте это таким образом, чтобы файлы были недоступны для других пользователей, то есть чтобы  прочитать или записать информацию в файлы мог бы только пользователь, который запускает программу. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "user.h"
#include "message.h"

namespace fs = std::filesystem;

void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        << '\n';
}

int main(){

	{ //Users
	
	    std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	    
	    if(!user_file)
	    {
		//for creation file use parametr ios::trunc
		user_file =std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
	    }
	
	    if(user_file)
	    {
		User u_obj("Alex", "noroot","111");
		User u_obj2("Victor", "vic","222");
	
		// write data to file
		user_file << u_obj << u_obj2;
	
	        std::cout << "Created file with permissions:\n";
	        demo_perms(fs::status("messages.txt").permissions());
	        
	        fs::permissions("users.txt", fs::perms::group_write | fs::perms::others_all, fs::perm_options::remove);
	        demo_perms(fs::status("users.txt").permissions());
	        
	        user_file.seekg(0, std::ios_base::beg);
	        
		while(user_file.peek() != std::char_traits<char>::eof())
		{
		  User empty;
		  user_file >> empty;
	          std::cout << empty << std::endl;	  	
		}	
	      }else{
	     	std::cout << "Could not open file users.txt." << '\n';
	    }
	    user_file.close();
  	}


	{  //Messages
	
		Message mobj("Alex", "Vasya","Hello Vasya, this is alex!");
	        Message mobj2("Виктор", "Нина", "Привет Нина, это Виктор!");
	
	     std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::app);
	
	     if(!message_file)
	     {
		//for creation file use parametr ios::trunc
		message_file =std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
	     }
	
	     if(fs::is_empty("messages.txt")){
	        message_file << mobj << std::endl;	
	        message_file << mobj2 << std::endl;	
	     } 
	
	     if(message_file)
	     { 
	        std::cout << "Created file with permissions:\n";
	        demo_perms(fs::status("messages.txt").permissions());
	        
	        fs::permissions("messages.txt", fs::perms::group_write | fs::perms::others_all, fs::perm_options::remove);
	        demo_perms(fs::status("messages.txt").permissions());

	        message_file.seekg(0, std::ios_base::beg);
	        
		while(message_file.peek() != std::char_traits<char>::eof())
		{
		  Message empty;
		 
		  message_file >> empty;
	          std::cout << empty << std::endl;	  	
		}	
	     }else{
	
	     	std::cout << "Could not open file messages.txt." << '\n';
	     }
	   	    
	       message_file.close();	
 	 }


return 0;
}	





