#include "user.h"


User::User(){
   // std::cout << "Конструктор по умолчанию User" << std::endl;
   db_ptr_ = Database:GetSinglton();

}


std::ostream& operator<<(std::ostream& out, const User& usr)
{
    return out << usr.login_ <<" - " << usr.password_ << std::endl;
}

