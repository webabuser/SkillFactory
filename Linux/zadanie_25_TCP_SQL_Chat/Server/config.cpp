#include <fstream>
#include <iostream>
#include <map>
#define DEB_conf false

class Config
{
 public:
    //Config() = default; 
    Config(const std::string& filename):filename_(filename){
        ParseFile();
    }
    ~Config(){
        file_.close();
        
        if(DEB_conf) std::cout << "Отработал деструктор fstream config \n";
    }
    
    std::map<std::string, std::string> Getconf(){
        return words_;
    }
           
 private:
     void ParseFile()
    {
        std::fstream file_ = std::fstream(filename_, std::ios::in);
	    if (!file_.is_open()) 
		    std::cerr << "Файл не удалось открыть" << std::endl;
		else
		{
		    for (std::string key, delim, value ;
		            file_ >> key >> delim >> value;
		                key.clear(), delim.clear(), value.clear())
		    {
		       if(key[0] == '#') {
                   file_.ignore(500, '\n');
                   continue;
               }
               words_[key] = value;
		    }   
            
            if (file_.bad() && DEB_conf)
                std::cout << "I/O error while reading\n";
            else if (file_.eof() && DEB_conf)
                std::cout << "End of file reached successfully\n";
            else if (file_.fail() && DEB_conf)
                std::cout << "Non-integer data encountered\n";    
  		}
    }
    
 private:    
    std::fstream file_;
    std::string filename_;
    std::map<std::string, std::string> words_;
           
};           
           
