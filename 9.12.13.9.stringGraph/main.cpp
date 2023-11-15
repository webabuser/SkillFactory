/******************************************************************************
https://onlinegdb.com/DCHl68mL4
Алгоритм проходит по всем заданным вершинам и по принципу "по ширине" и 
проверяет каждую вершину относительно базовой на минимальное расстояние.
Если минимальное расстояние не превышает количества рукопожатий, то выводим пары вершин знакомых базовому.
И так для каждой вершины в графе.

*******************************************************************************/
#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
    {
        Graph g;
        
        g.addPerson("Alex");
        g.addPerson("Sasha");
        g.addPerson("Grigor");
        g.addPerson("Lena");
        g.addPerson("Ira");
        g.addPerson("Luda");
        g.addPerson("Misha");
        g.addPerson("Tanya");
        g.addPerson("Boris");
        g.addPerson("Zina");
        g.addPerson("Piter");
        g.addPerson("Valera");
        g.addPerson("Ben");
        g.addPerson("John");
        g.addPerson("Milena");
        g.addPerson("Jim");
        
        g.addLink("Alex", "Sasha");
        g.addLink("Sasha", "Grigor");
        g.addLink("Grigor", "Lena");
        g.addLink("Lena", "Ira");
        g.addLink("Ira", "Valera");
        g.addLink("Alex", "Misha");
        g.addLink("Misha", "Boris");
        g.addLink("Boris", "Zina");
        g.addLink("Boris", "Tanya");
        g.addLink("Tanya", "Piter");
        g.addLink("Boris", "Luda");
        g.addLink("Luda", "Valera");
        g.addLink("Alex", "Ben");
        g.addLink("John", "Milena");
        g.addLink("Ben", "John");
        g.addLink("Milena", "Jim");
       
        const size_t kHandshake = 3;
        g.FindPairs(kHandshake);
      
    }

    cout<<"Program has worked!";

    return 0;
}