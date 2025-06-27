#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


void quick_sort(std::vector<int>& vec, int left, int right,
                    std::shared_ptr<std::promise<void>> pr_left, std::shared_ptr<std::promise<void>> pr_right ) 
{
   // if (right == -1) right = vec.size() - 1; // Инициализация при первом вызове
    if (left >= right){
          if (pr_left) pr_left->set_value();
          if (pr_right) pr_right->set_value(); 
          return; // Базовый случай рекурсии
    } 

    // Выбор опорного элемента (медиана из первого, среднего и последнего)
    int mid = left + (right - left) / 2;
    int pivot = std::max(std::min(vec[left], vec[mid]), 
                std::min(std::max(vec[left], vec[mid]), vec[right]));

    int i = left, j = right;
    while (i <= j) {
        while (vec[i] < pivot) i++;
        while (vec[j] > pivot) j--;
        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }
    
    
    if(kMakeThread && ((right - left) > kParallelLimit)){
        if (kPrintMarkers) std::cout << '+';
        
        pool.push_task(quick_sort, std::ref(vec), left, j, pr_left, nullptr);
        pool.push_task(quick_sort, std::ref(vec), i, right, nullptr, pr_right);
 
    } else {
        if (kPrintMarkers) std::cout << '.';
        
        quick_sort(vec, left, j, pr_left, nullptr);
        quick_sort(vec, i, right, nullptr, pr_right);
        
    }
}

