#include <iostream>
#include <exception>
#include "IntegerArray.h"

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
    
    
    

    return 0;
}
