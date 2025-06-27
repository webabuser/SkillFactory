#pragma once

#include <future>
#include <vector>

#include "bq.h"

using namespace std;


using task_type = function<void()>;
using FuncType = void(*)(std::vector<int>&, int, int, std::shared_ptr<std::promise<void>>, std::shared_ptr<std::promise<void>>);

// пул потоков
class ThreadPool {
   public:
       ThreadPool();
       // запуск
       void start();
       // остановка
       void stop();
       // проброс задач
       void push_task(FuncType f, std::vector<int>& vec, int left, int right, 
                        std::shared_ptr<std::promise<void>> pr_left, std::shared_ptr<std::promise<void>> pr_right);
       // функция входа для потока
       void threadFunc(int);
       
   private:
       // количество потоков
       int m_thread_count;
       // потоки
       vector<thread> m_threads;
       // поддержка синхронизации очереди
       vector<BlockedQueue<task_type>> m_thread_queues;
       // для равномерного распределения задач
       int m_index {0};
       
};


ThreadPool::ThreadPool():
   m_thread_count(thread::hardware_concurrency() != 0 ? thread::hardware_concurrency() : 4),
   m_thread_queues(m_thread_count) {
       //Мои: перезагрузим кол-во очередей 
      // if(m_thread_count > 4) m_thread_count = 2;
       std::cout <<"Конструктор ThreadPool m_thread_count = " << m_thread_count << std::endl;
}


void ThreadPool::start() {
    //std::cout << "ThreadPool::start() "<< std::endl;
   for(int i=0;i<m_thread_count; i++) {
       //Эту же строку можно записать через лямбду:
       m_threads.push_back(std::thread([this, i]() { this->threadFunc(i); }));
       //m_threads.push_back(std::thread(&ThreadPool::threadFunc, this, i)); 
       //std::cout << "m_threads (" << &ThreadPool::threadFunc <<" " << this << " " << i << std::endl;
   }  
   std::cout << std::endl;
}

void ThreadPool::stop() {
   for(int i=0;i<m_thread_count; i++) {
       // кладем задачу-пустышку в каждую очередь
       // для завершения потока
       task_type empty_task;
       m_thread_queues[i].push(empty_task);
   }
   for(auto& t: m_threads) {
       t.join();
   }
}

void ThreadPool::push_task(FuncType f, std::vector<int>&vec, int arg1, int arg2,
                            std::shared_ptr<std::promise<void>> pr_left, std::shared_ptr<std::promise<void>> pr_right) {
// вычисляем индекс очереди, куда положим задачу
   // std::cout << "ThreadPool::push_task: m_index: " << m_index << std::endl;
   int queue_to_push = m_index++ % m_thread_count;
    //std::cout << "ThreadPool::push_task: queue_to_push: " << queue_to_push << std::endl;
   
   // формируем функтор
   task_type task = [f, &vec, arg1, arg2, pr_left, pr_right](){ f(vec, arg1, arg2, pr_left, pr_right); };
   // кладем в очередь4
   m_thread_queues[queue_to_push].push(task);
}   

void ThreadPool::threadFunc(int qindex) {
    while(true) {
       // обработка очередной задачи
       task_type task_to_do;
       bool res;
       int i = 0;
       for(; i<m_thread_count; i++) {
           // попытка быстро забрать задачу из любой очереди, начиная со своей
           if((res = m_thread_queues[(qindex + i) % m_thread_count].fast_pop(task_to_do)))
               break;
       }

       if (!res) {
           // вызываем блокирующее получение очереди
           m_thread_queues[qindex].pop(task_to_do);
       } else if (!task_to_do) {
           // чтобы не допустить зависания потока
           // кладем обратно задачу-пустышку
           m_thread_queues[(qindex + i) % m_thread_count].push(task_to_do);
       }
       if (!task_to_do) {
           return;
       }
       // выполняем задачу
       task_to_do();
   }
}