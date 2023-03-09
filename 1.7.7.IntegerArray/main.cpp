#include <iostream>
#include <exception>
#include "IntegerArray.h"

int main()
{
    try{
        IntegerArray arr(2100000000);  // throws std::bad_alloc
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
    
    
    try{
        IntegerArray arr(4100000000); // throws std::invalid_argument()
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
    
    
    try{
        IntegerArray arr {1, 3, 5, 7, 9, 11, 13, 15, 17, 18};
        arr.Show();
        
        std::cout << arr[2] << std::endl;

        arr.insertBefore(50, 10);
        arr.Show();
        
        arr.Remove(0);
        arr.Show();
        
        arr.resize(15);
        arr.Show();
        
        arr.PushFront(1);
        arr.PushBack(51);
        arr.Show();
        
        size_t result = 0;
        if(arr.Find(18, result)){
            std::cout << "Element found под индексом " << result << std::endl;
        }else{
            std::cout << "Element Not found " << std::endl;
        }
        
        if(arr.Find(55, result)){
            std::cout << "Element found под индексом " << result << std::endl;
        }else{
            std::cout << "Element Not found " << std::endl;
        }
        
        
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    
    }
    
    
    

    return 0;
}
