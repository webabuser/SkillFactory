#include "graph.h"
#include <iostream>
#define VERYBIGINT 100

Graph::Graph() {
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            matrix[i][j] = 0;
        }
    }
    persons_count = 0;
}

void Graph::addPerson(const std::string& person)
{
   persons[persons_count] = person;
   persons_count++;
}

// добавление ребра
void Graph::addLink(const std::string& p1, const std::string& p2, int weight)
{
   int index1 = find(p1);
   int index2 = find(p2);
    
   matrix[index1][index2] = weight;
   matrix[index2][index1] = weight;
}

int Graph::find(const std::string& person){
    for(int i = 0; i < SIZE; ++i){
        if(person == persons[i]){
            return i;
        }
    }
    std::cout << "Не найдена имя " << person << std::endl;
    return -1;
}



void Graph::depth(std::string& start_name)
{
    bool visited[SIZE]{false};
       
    depthInner(start_name, visited); // запуск алгоритма 
    
    std::cout << std::endl;
}


void Graph::depthInner(std::string& current, bool visited[])
{
    std::cout << " " << current << " -> "; // вывод текущей
    
    int index_of_current = find(current);
    
    visited[index_of_current]= true; // помечаем как посещенную
    
    for(int i=0; i<SIZE; i++)
    {
        if(edgeExists(index_of_current,i) && !visited[i]){
            
            current = persons[i];
            depthInner(current, visited); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину
        }


    }
}

// проверка существования ребра
bool Graph::edgeExists(int index1, int index2)
{
    return matrix[index1][index2] > 0;
}


void Graph::width(const std::string& start_name){
    std::string queue_to_visit[SIZE]; // очередь вершин для обхода
    int queueCount = 0;
    
    bool visited[SIZE]{false}; // список посещенных вершин

    queue_to_visit[queueCount++] = start_name; //Кладем в очередь начальную вершину
    
    while(queueCount > 0)
    {
        //берем из очереди вершину
        std::string current_name = queue_to_visit[0];
        
        queueCount--;
        
        for(int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i+1];
        }
        
        int current_index = find(current_name);
        visited[current_index] = true;
        
        std::cout << current_name << " -> ";
        
        //Поиск смежных вершин и добавление их в очередь 
        
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            
            for (int j = 0; j < queueCount; j++)
            {
            
                
                if(queue_to_visit[j] == persons[i]){
                    alreadyAdded = true;
                    break;
                }
            }
            
            if(!alreadyAdded && edgeExists(current_index, i) && !visited[i]){
                queue_to_visit[queueCount++] = persons[i];
            }
        }
    }
    std::cout << std::endl;
} 

void Graph::width(const std::string& start_name, int handshake){
    std::string queue_to_visit[SIZE]; // очередь вершин для обхода
    int queueCount = 0;
    
    bool visited[SIZE]{false}; // список посещенных вершин

    queue_to_visit[queueCount++] = start_name; //Кладем в очередь начальную вершину
    

    while(queueCount > 0 && handshake >= 0)
    {
        //берем из очереди вершину
        std::string current_name = queue_to_visit[0];
        
        queueCount--;
        
        
        
        for(int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i+1];
        }
        
        int current_index = find(current_name);
        visited[current_index] = true;
        

        //Поиск смежных вершин и добавление их в очередь 
        
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            
            for (int j = 0; j < queueCount; j++)
            {

                if(queue_to_visit[j] == persons[i]){
                    alreadyAdded = true;
                    break;
                }
            }
            
            if(!alreadyAdded && edgeExists(current_index, i) && !visited[i]){
                queue_to_visit[queueCount++] = persons[i];
            }
            
        }


        // Если минимальное расстояние от базовой вершины не превышает количество рукопожатий то выводим текущее имя
        // И оно этот человек будет знакомым базовому в пределах заданных рукопожатий.
        
        if(findMinWayDFS(find(start_name), current_index) <= handshake) {
            if (start_name != current_name){
                std::cout << start_name <<" - " << current_name <<"\n";
            }
        } else{
            break;
        }
        
    }
    
    std::cout << std::endl;
} 


void Graph::FindPairs(int handshake){
    for(int i = 0; i < persons_count; i++){
        width(persons[i], handshake);
    }
}

void Graph::PrintVertexex(){
    for(int i=0; i < SIZE; ++i){
        std::cout << persons[i] << ", ";
    }
}

int Graph::findMinWayDFS(int from, int to) {
    
    bool visited[SIZE]; // массив пройденных вершин
    for(int i = 0; i<SIZE; i++)
       visited[i] = false;
    int min = VERYBIGINT; // начальное минимальное расстояние
    int currentDistance = 0;
    
    inner(from,to,visited,min,currentDistance);
    return min;
}

void Graph::inner(int current,int to, bool visited[], int& min, int currentDistance)
{
    if(current == to) 
    {
       // если попали в целевую вершину, сравниваем текущий путь с минимальным
       if(min > currentDistance)
       {
           // если новое расстояние меньше, запоминаем
           min = currentDistance;
       }
       return;
    }
    visited[current] = true; // обозначем вершину посещенной
    for(int i=0; i<SIZE; i++)
    {
        if(edgeExists(current, i) && !visited[i])
        {
            // запускаем рекурсию для всех непосещенных смежных вершин
            int newDist = currentDistance + matrix[current][i];
            inner(i,to, visited, min, newDist);  
        }
    }    
    // отмечаем, что путь уже не содержит эту вершину
    visited[current] = false;            
}
