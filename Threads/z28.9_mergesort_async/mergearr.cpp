/*
all:
	g++ -o mergearr mergearr.cpp -pthread --std=c++17 -g2 -pedantic -Wall -Wextra -Werror
*/	

#include <iostream>
#include <future>
#include <thread>
#include "logduration.h"

#define COUNT  150
#define RANDOM_NUM_FROM -100
#define RANDOM_NUM_TILL 1000


bool asynchronous = true;
int difference = 0;


template<typename T>
void Print(const T *, const T);

template<typename T>
void merge(T* arr, T l, T m, T r)
{
   T nl = m - l + 1;
   T nr = r - m;

   // создаем временные массивы

   T* left = new T[nl]; 
   T* right = new T[nr];

   // копируем данные во временные массивы
   for (T i = 0; i < nl; i++)
       left[i] = arr[l + i];
   for (T j = 0; j < nr; j++)
       right[j] = arr[m + 1 + j];

   T i = 0, j = 0;
   T k = l;  // начало левой части

   while (i < nl && j < nr) {
       // записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           arr[k] = left[i];
           i++;
       }
       else {
           arr[k] = right[j];
           j++;
       }
       k++;
   }
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }

   delete[] left;
   delete[] right;
}

template<typename T>
void mergeSort(T* arr, T l, T r){
    
    if(l == r) return ;
    
    T m = (l + r - 1) / 2;
  
    if(asynchronous && (r - l) > difference){
        
        //std::cout << "asynchronous thread." << std::endl;
        std::future<void> f = std::async(std::launch::async, mergeSort<T>, std::ref(arr), l, m);
        f.get();
        mergeSort<T>(arr, m + 1, r);
       
    } else { 
         //std::cout << "One thread." <<std::endl;
         mergeSort(arr, l, m);
         mergeSort<T>(arr, m + 1, r);
    }
    
    
    merge<T>(arr, l, m, r);
}





int main()
{
    srand(time(NULL)); //Достаточно вызвать один раз в начале программы
    //Выделяем 2 одинаковых массивa в куче.
    int64_t * arr       =  new int64_t[COUNT]{0};  
    int64_t * same_arr  =  new int64_t[COUNT]{0};
    // Заполняем оба массив одинаковыми цифрами
    for(int64_t i = 0; i < COUNT; ++i)
    {
        arr[i] =  RANDOM_NUM_FROM + rand() % RANDOM_NUM_TILL ;
        same_arr[i] = arr[i];
    }
    
    Print<int64_t>(arr, COUNT); // можно посмотреть массив
    std::cout << std::endl;
    Print<int64_t>(same_arr, COUNT); // можно посмотреть массив
    
    
    
    
    
   
    std::cout << "\nАсинхронная сортировка." << std::endl;
    {    
        LOG_DURATION("Elapsed time"); 
        
        mergeSort<int64_t>(arr, 0, COUNT-1);
    }
    Print<int64_t>(arr, COUNT);
   
 
 
    asynchronous = false;
    std::cout << "\nВ одном потоке сортировка." << std::endl;
    { 
        LOG_DURATION("Elapsed time"); 
        
        mergeSort<int64_t>(same_arr, 0, COUNT-1);
    }
    Print<int64_t>(same_arr, COUNT);

    
 
    
    delete[] arr;
    delete[] same_arr;
  
    return 0;
}


template<typename T>
void Print(const T * arr, const T n){
    for(T i = 0; i < n; ++i){
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}
