#include <iostream>
#include <ctime>
#include <thread>
#include <vector>
#include <utility>
#include <functional>
#include <numeric>
#include "logduration.h"

#define COUNT  23'452'341
#define PART    2'333'123
#define RANDOM_NUM_FROM 0
#define RANDOM_NUM_TILL 100

void calc_massiv(const std::vector<int64_t>& v, int64_t begin, int64_t end, int64_t& res)
{   
    int64_t s = 0;
    for(int64_t i = begin; i < end; ++i){
        s += v[i];
    }
    
    res += s;

    std::cout << "Cумма частей массива от " <<begin << " до " << end << " элемента:"<< s << std::endl;
}


int main()
{
    srand(time(NULL)); //Достаточно вызвать один раз в начале программы
    
    std::vector<int64_t> massiv;
    massiv.reserve(COUNT + 1);

    for(int64_t i = 0; i < COUNT; ++i)
    {
        massiv.push_back( RANDOM_NUM_FROM + rand() % RANDOM_NUM_TILL );
   //     std::cout << massiv.back() << ", ";
    }


    std::cout << std::endl;
    {
        LOG_DURATION("Время вычисления алгоритмом");
        std::cout << "Сумма элементов вектора вычисленная стандартным алгоритмом: " << std::accumulate(massiv.begin(), massiv.end(), 0) << std::endl;
    }
    std::cout << std::endl;


    {    
        LOG_DURATION("Время вычисления потоками");
        
        std::vector<std::thread> threads;
        threads.reserve((COUNT / PART) + 1);

        int64_t result = 0;
        
        int64_t part = PART;

        for(int64_t i = 0; i < COUNT; i += PART)
        {
            if((COUNT - i) < PART) part = COUNT - i;

            std::thread t(calc_massiv, std::ref(massiv), i, (i+part), std::ref(result));
          
            threads.push_back(std::move(t));
        }
       
        
        const int64_t count_threads = threads.size();
        std::cout << "Количество потоков:" <<  count_threads << std::endl;
         
        for (int64_t i = 0; i < count_threads; ++i)
        {
            threads[i].join();
        }


         std::cout << "\nСумма элементов вектора вычисленная с помощью потоков: " << result << std::endl;
    }
    return 0;
}
