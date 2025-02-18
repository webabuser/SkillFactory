#include "logger.h"
#include <chrono>

Logger::Logger()
{
	log_.open("log.txt", std::ios_base::in | std::ios_base::out |
                         std::ios_base::ate );

    if (!log_.is_open())
    {
       std::cerr << "Файл логов не открыт, создаем заново." << std::endl;
       log_.open("log.txt", std::ios_base::in | std::ios_base::out |
                         std::ios_base::trunc | std::ios_base::ate);
  
    }else{
        std::cerr << "Файл логов открыт." << std::endl;
    }    
}

Logger::~Logger()
{
   log_.close();
   std::cerr << "Файл логов закрыт" << std::endl; 
}
 

void Logger::inputToLog(const std::string& text)
{
     const auto now = std::chrono::system_clock::now();
     const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    m_.lock();
    
    log_.seekg(0, std::ios_base::end);
    log_ << std::ctime(&t_c);

    log_.seekg(-1, std::ios_base::end);
    log_ << "  " << text << std::endl;

    m_.unlock();
}


std::string Logger::getLastString()
{ 

    m_.lock_shared();

    if(!log_.is_open()) {
        m_.unlock_shared();   
        return "The log file is NOT opened";    
    }

    bool keep = true;

    log_.seekg(-2, std::ios_base::end); // Устанавливаем указатель в конец файла.
    while (keep)
    {
       char ch = log_.peek(); 
 
       if(static_cast<int>(log_.tellg()) <= 1){ //Если достигнуто начала файла
           log_.seekg(0); 
           keep = false;
       } else if(ch == '\n'){//Если достигли переноса
          keep = false;
          log_.seekg(1, std::ios_base::cur);
       } else {
         log_.seekg(-1, std::ios_base::cur);
       }
    }   

    std::string lastline;
    std::getline(log_, lastline);     

    m_.unlock_shared();

    return lastline;

}





