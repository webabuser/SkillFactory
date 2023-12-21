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
            std::cout << "������� ��������� ������� �����, ��� 0 ��������� ���������: ";
            std::string word;

            std::cin >> word;

            if(word == "0") break; // ��������� ��������� ���� ������������ ����� 0

           
           std::vector<std::string> found_words;
           SearchWords(node, word, found_words);


           if(!found_words.empty())
           {
               std::cout << "�� ������ ������� ��������������� ����� �� ������������ ���������:\n";

               PrintVector(found_words);

               std::cout << "������� ���������� ����� ����� ��� �������������: ";
               size_t var;
               std::cin >> var;

               std::cout <<  ((var < found_words.size()) ? "��������� �����: " + found_words[var] : "�� ������� �� �����") << std::endl;
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