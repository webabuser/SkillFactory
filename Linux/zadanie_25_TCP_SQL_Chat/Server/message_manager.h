#pragma once
#include <iostream>
#include <string>
#include "db.h"
#include "message.h"
#include <vector>

class Message_manager
{
 public:    
    Message_manager();
   ~Message_manager();






 private:
    Database * db_ptr_ = nullptr;
    std::vector<Message> messages_;

};    
