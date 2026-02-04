#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#define DEB_conf true

class Config
{
 public:   
    explicit Config(const std::string& filename):filename_(filename){
        ParseFile();
    }
    ~Config(){
        if(file_.is_open()) {
            std::cout << "Closed config file in destructor\n";
            file_.close();
        }
        
        if(DEB_conf) std::cout << "Отработал деструктор fstream config \n";
    }
    

    std::string getValue(const std::string& key,
                         const std::string& defaultValue = "")const {

        auto it = words_.find(key);
        return it != words_.end() ? it->second : defaultValue;

    }

    //для технических нужд
    const std::map<std::string, std::string>& Getconf()const{
        return words_;
    }


 private:
     void ParseFile()
    {
        file_.open(filename_, std::ios::in);
	    if (!file_.is_open()) 
		    std::cerr << "Файл не удалось открыть" << std::endl;
		else
		{


            std::string line;
            while(std::getline(file_,line)){
                //Пропускаем пустые строки и комментарии
                line.erase(0, line.find_first_not_of(" \t"));
                if(line.empty() || line[0] == '#') continue;

                std::istringstream iss(line);
                std::string key, delim, value;

                if(iss >> key >> delim >>value){

                    std::cout << "DEBUG: Read - key='" << key
                               << "', delim='" << delim
                               << "', value='" << value << "'" << std::endl;

                    words_[key] = value;
                }
            }

                                  
            if (file_.bad() && DEB_conf)
                std::cout << "I/O error while reading\n";
            else if (file_.eof() && DEB_conf)
                std::cout << "End of file reached successfully\n";
            else if (file_.fail() && DEB_conf)
                std::cout << "Non-integer data encountered\n";

            if(file_.is_open()){
                std::cout << "Closed config file\n";
                file_.close();
            }
  		}
    }

 private:    
    std::ifstream file_;
    std::string filename_;
    std::map<std::string, std::string> words_;           
};           
           
