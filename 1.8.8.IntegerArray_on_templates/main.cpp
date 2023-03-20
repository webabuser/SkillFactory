#include <iostream>
#include <exception>
#include "IntegerArray.h"

using namespace std;
using namespace std::string_literals;
int main()
{  
    std::cout <<"1.---------------------------------\n";    
    try{
        IntegerArray arr(2100000000);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    
    std::cout <<"2.---------------------------------\n";  
    try{
        IntegerArray arr(4100000000);
    }
    catch(const std::exception& e){
        std::cerr  << e.what() << std::endl;
    }
    
    std::cout <<"3.---------------------------------\n";  
    try{
        
        IntegerArray arr {1, 3, 5, 7, 9, 11, 13, 15, 17, 18};
        std::cout << arr[11] << std::endl;

    }
    catch(const std::exception& e){
        std::cerr  << e.what() << std::endl;
    
    }
    
    try{
        IntegerArray<> ar(10);
        ar.Show();
        
        IntegerArray<int> ar1(10);
        ar1.Show();
        
        IntegerArray<int> ar2{1, 2, 3, 4, 5, 6};
        ar2.Show();
        
        IntegerArray<std::string> ar3{"Hello"s, "Rad"s, "Dudo"s, "Dump"s, "Gat"s};
        ar3.Show();
        
        //Копирование конструктора
        IntegerArray<int> ar_tocopy(5);
        IntegerArray<int> ar_(2);
        
        ar_ = ar_tocopy;
        ar_.Show();
        
        ar3.insertBefore("Dandy", 2);
        ar3.Show();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    
    

    return 0;
}
