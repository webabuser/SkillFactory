/**
* https://onlinegdb.com/xtzuySFz5
* Прошу прощения, задание решено не верно, буду искать решение.
*/

#include <iostream>
#include <string>
using namespace std;

bool IsKPeriodic(const std::string& str, int& period){
     
    std::string pat;

    int i = 0;
    do
    {
       pat.push_back(str[i]);
       ++i;
    }
    while(pat[0] != str[i] && i < (str.length()/2 + 1) ); 
    
    // Если строка дошла до середины и не нашла повторяющегося первого символа, то return
    if (pat.length() > str.length() / 2)
    {   
        std::cout << "Строка не периодическая" << std::endl;
        return false;
    }

    period = pat.length();
    
    for(int i = period; i < str.length(); i += period)
    {   
        if(str.compare(i, period, pat) != 0)
        {
            std::cout << "Строка не периодическая " << i << std::endl;
            return false;   
        }
    }
    
    std::cout << "Строка периодическая, состоит из подстроки - " << pat << " кратность = " << period << std::endl;
    return true;
}


int main()
{
    
    std::string str = "Yello Yello Yello Yello Yello Yello Yello Yello ";
    int period = 0;
    
    IsKPeriodic(str, period);
    
    
    cout<<"Hello World";

    return 0;
}
