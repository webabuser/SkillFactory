#include <iostream>
#include <thread>
#include <mutex>
/*
Функция должна вставить узел с переданным значением value в позицию pos. Чтобы не переусложнять реализацию, предполагается следующее:
очередь не пустая,
вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать,
если pos больше длины списка, то нужно вставить элемент в конец списка.
*/


struct Node
{
  int value;
  Node* next;
  std::mutex* node_mutex;
};


class FineGrainedQueue
{
 private:    
    Node* head;
    std::mutex* queue_mutex;

 public:
    
    explicit FineGrainedQueue(Node* node)
        :head(node), queue_mutex(new std::mutex()){}

    void remove_first(int value)
      {
        Node *prev, *cur; // указатели на предыдущий и текущий элемент

        prev = this->head; // старт: предыдущий = начало списка
        cur = this->head->next; // старт: текущий = второй элемент списка

        prev->node_mutex->lock(); 
        cur->node_mutex->lock();

        while (cur) // пока указатель на текущий элемент не нулевой... 
        {
          if (cur->value == value) // если нашли элемент для удаления... 
          {
            // то удаляем его
            prev->next = cur->next;
            prev->node_mutex->unlock();
            cur->node_mutex->unlock();
            delete cur;
            return;
          }

          // если не нашли элемент для удаления, то двигаемся дальше по очереди
          Node* old_prev = prev;
          prev = cur;
          cur = cur->next;

          old_prev->node_mutex->unlock(); // обратите внимание, после сдвига что анлочится "старый" предыдущий элемент
          cur->node_mutex->lock(); // а потом лочится новый текущий элемент
        }
        prev->node_mutex->unlock();
      }

void remove_last(int value)
  {
    Node *prev, *cur;
    queue_mutex->lock();

    // здесь должна быть обработка случая пустого списка

    prev = this->head;
    cur = this->head->next;

    prev->node_mutex->lock();
    // здесь должна быть обработка случая удаления первого элемента
    queue_mutex->unlock();

    if (cur) // проверили и только потом залочили
      cur->node_mutex->lock();
    while (cur)
    {
      if (cur->value == value)
      {
        prev->next = cur->next;
        prev->node_mutex->unlock();
        cur->node_mutex->unlock();
        delete cur;
        return;
      }
      Node* old_prev = prev;
      prev = cur;
      cur = cur->next;
      old_prev->node_mutex->unlock();
      if (cur) // проверили и только потом залочили
        cur->node_mutex->lock();
    }
    prev->node_mutex->unlock();
  }


    void insertIntoMiddle(int value, int pos){
        Node * newnode = new Node{value, nullptr, new std::mutex()};
       
       
        int current_pos = 0;
      
        queue_mutex->lock();
       
        Node* prev = nullptr;
        Node* current = this->head;
       
        queue_mutex->unlock();


        if(pos == 0){
            newnode->node_mutex->lock();    
            newnode->next = current;
            newnode->node_mutex->unlock();
            
            
            queue_mutex->lock();
            this->head = newnode;
            queue_mutex->unlock();

            return;
        }

        while(current != nullptr && current_pos < pos){
           
            if(prev) prev->node_mutex->lock();
            prev = current;
            prev->node_mutex->unlock();

            current = current->next;
            ++current_pos;

        }
        
        //Вставляем узел перед current
        newnode->node_mutex->lock();
        newnode->next = current;
        newnode->node_mutex->unlock();
        
        prev->node_mutex->lock();    
        prev->next = newnode;
        prev->node_mutex->unlock();
    }


    void print(){
         
        Node* current = this->head;
       
        while(current){
            std::cout << current->value << ", ";
            current = current->next;
        }

        std::cout << std::endl;
    }

};


int main(){

    FineGrainedQueue fg(new Node(12, new Node(16, new Node(20, nullptr, new std::mutex()), new std::mutex()), new std::mutex()));

    fg.print();
    
    std::thread t1 ([&](){fg.insertIntoMiddle(0, 0);});
    std::thread t2 ([&](){fg.insertIntoMiddle(1, 6);});
    std::thread t3 ([&](){fg.insertIntoMiddle(2, 8);});
    std::thread t4 ([&](){fg.insertIntoMiddle(3, 11);});
    std::thread t5 ([&](){fg.insertIntoMiddle(4, 2);});
    std::thread t6 ([&](){fg.insertIntoMiddle(5, 0);});
    std::thread t7 ([&](){fg.insertIntoMiddle(6, 10);});
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();


    fg.print();



  return 0;
}
