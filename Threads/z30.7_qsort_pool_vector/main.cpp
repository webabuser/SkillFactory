/* https://onlinegdb.com/YaRCbX3bF   --  можно здесь смотреть */

#include <iostream>
#include <utility>
#include <future>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include "pool.h"
ThreadPool pool;

constexpr bool kMakeThread = true;
constexpr int  kMassivSize = 200;
constexpr int  kParallelLimit = 0;

constexpr bool kPrintMarkers = true;
constexpr bool kPrintOriginalMassiv = false;
constexpr bool kPrintResultMassiv = true;

#include "qsort.h"
std::pair<bool, size_t> is_sorted_with_pos(const std::vector<int>&);



int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100); // диапазон от 1 до 100
    std::vector<int> numbers(kMassivSize); 
    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
 
    if(kPrintOriginalMassiv){
        std::cout << "Массив До сортировки: ";
        for (int num : numbers) std::cout << num << " ";
        std::cout << std::endl;
    }
 
        
    // Засекаем время перед вызовом
    auto start = std::chrono::high_resolution_clock::now();

    { 
        pool.start();
        
        std::shared_ptr<std::promise<void>> prom_left = std::make_shared<std::promise<void>>();
        std::shared_ptr<std::promise<void>> prom_right = std::make_shared<std::promise<void>>();
        
        std::future<void> f_left = prom_left->get_future();
        std::future<void> f_right = prom_right->get_future();

        quick_sort(numbers, 0, numbers.size()-1, prom_left, prom_right);
        
        f_left.wait();
        f_right.wait();
        
        f_left.get();
        f_right.get();
        
        pool.stop();
    }
    
    // Засекаем время после выполнения
    auto end = std::chrono::high_resolution_clock::now();
    // Вычисляем продолжительность
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Затрачено " << duration.count() << " микросекунд" << std::endl;
    
    
    


                    
    std::pair<bool, size_t> sort_res = is_sorted_with_pos(numbers);
    if(sort_res.first) std::cout << "Массив отсортирован" << std::endl;
    else std::cout << "Массив Неотсортирован на значении " << sort_res.second << std::endl;

    
    
    if(!sort_res.first && kPrintResultMassiv)
    {
        std::cout << "После сортировки: ";
        for (int num : numbers) std::cout << num << " ";
        std::cout << std::endl;
    }

    return 0;
}



std::pair<bool, size_t> is_sorted_with_pos(const std::vector<int>& vec) {
    for (size_t i = 1; i < vec.size()/10; ++i) {
        if (vec[i] < vec[i-1]) {
            return {false, vec[i]};
        }
    }
    return {true, 0};
}
