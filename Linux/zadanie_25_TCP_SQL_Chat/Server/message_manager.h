#pragma once
#include <iostream>
#include <string>
#include "db.h"
#include "message.h"


class Message_manager
{
 public:    
    Message_manager();
   ~Message_manager();






 private:
    Database * db_ptr_ = nullptr;


};    
