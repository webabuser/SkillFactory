#include "message_manager.h"


Message_manager::Message_manager(){

    db_ptr_ = Database::GetSinglton();

    std::cout << "Конструтор MM" << std::endl;

    std::cout << db_ptr_ << std::endl;

}


Message_manager::~Message_manager(){
    std::cout << "Деструтор Message_manager" << std::endl;

}    
