#include <iostream>
#include <cstring>

#include "db.h"

//инициализируем статическое поле 
Database* Database::db_ = nullptr;


Database::Database()
{
    {
        Config cf{"config.ini"};
        
        std::string s_host = cf.Getconf()["host"s];
        std::string s_user = cf.Getconf()["user"s];
        std::string s_db_name = cf.Getconf()["db"s];
        std::string s_password = cf.Getconf()["password"s];

        host_ = s_host.c_str();
        user_ = s_user.c_str();
        db_name_ = s_db_name.c_str();
        password_ = s_password.c_str();
   
        //Закрываем файл конфига.
    }

    dbInit();

    /*
    std::string query = "INSERT INTO users (login,name,email) VALUES ('Nina6', 'Нина6','nina6@mail.ru')";
    if (DbQuery(query) == false) exit(1);
    
    GetResult();

*/
}

Database::~Database()
{ 
    mysql_close(&mysql_);
    delete db_;
    db_ = nullptr;
    std::cout << "Деструктор DB" << std::endl;
}    


Database* Database::GetSinglton(/*const std::string& value*/)
{
    if(db_ == nullptr){
        db_ = new Database();
    }
    return db_;
}

void Database::dbInit()
{
    mysql_init(&mysql_);
    
    // Если дескриптор не получен — выводим сообщение об ошибке
	if (&mysql_ == NULL)
    {
		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql_, host_, user_, password_, db_name_, 0, NULL, 0))
    {
		std::cout << "Error: can't connect to database " << mysql_error(&mysql_) << std::endl;
    } else
    {
		std::cout << "Mysql connect Success!" << std::endl;
	}

    //Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
    mysql_set_character_set(&mysql_, "utf8");
    std::cout << "connection characterset: " << mysql_character_set_name(&mysql_) << std::endl;
}


bool Database::DbQuery(const std::string& str)
{
    if (mysql_query(&mysql_, str.c_str()) == 0)
       return  true ;
    else 
        std::cerr << "DbQuery error " << mysql_error(&mysql_) << std::endl;
            
    return false;  
}


std::map<size_t, std::vector<std::string>> Database::GetResult()
{
    result.clear(); 
    //Выводим все что есть в таблице через цикл
	if ((res_ = mysql_store_result(&mysql_)) != nullptr)
    {
        // __asm__ __volatile__("int3"); // break for gdb
        std::size_t j = 0; 
        while ((row_ = mysql_fetch_row(res_)) != NULL)
        {
           std::vector<std::string> vrow;
           std::size_t count_fields = mysql_num_fields(res_);
           vrow.reserve(count_fields);

           for (std::size_t i = 0; i < count_fields; ++i)
           {
               vrow.emplace(vrow.end(),row_[i]);     
		   }
        
           result[j] = vrow;
           ++j;
		}
	}
	else
	    std::cerr << "GetResult: 0" << std::endl;
    
    return result;

}    

