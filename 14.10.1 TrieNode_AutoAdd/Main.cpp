#include <iostream>
#include <string>
#include <vector>
#include "TrieNode.h"
using namespace std;


void PrintVector(std::vector<std::string>& arr)
{
    int i = 0;
	for (auto value : arr)
	{
		std::cout << i++ << ". " << value << std::endl;
	}
}

void UserInput(TrieNode* node) {
    {
        while (true)
        {
            std::cout << "Введите начальные символы слова, или 0 завершить программу: ";
            std::string word;

            std::cin >> word;

            if(word == "0") break; // Завершаем программу если пользователь нажал 0

           
           std::vector<std::string> found_words;
           SearchWords(node, word, found_words);


           if(!found_words.empty())
           {
               std::cout << "Вы можете выбрать автодополненное слово из предлагаемых вариантов:\n";

               PrintVector(found_words);

               std::cout << "Введите порядковый номер слова для автопродления: ";
               size_t var;
               std::cin >> var;

               std::cout <<  ((var < found_words.size()) ? "Выбранное слово: " + found_words[var] : "Вы выбрали не верно") << std::endl;
           }       
        }        
    }
}

int main()
{
    setlocale(LC_ALL, "Ru");
    
    TrieNode* t = new TrieNode();
    
    insert(t, "Arena");
    insert(t, "Arduino");
    insert(t, "Batle");
    insert(t, "Bottle");
    insert(t, "Reddish");
    insert(t, "Red");
    insert(t, "Royalty");    
    
    UserInput(t);   

    cout<<"\nThe Program finished correctly!";

    return 0;
}