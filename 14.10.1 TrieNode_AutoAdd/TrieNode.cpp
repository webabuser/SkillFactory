#include <string>
#include <iostream>
#include <vector>
#include "TrieNode.h"
using namespace std;

// Возвращает новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
   // Выделяем память под новый узел
   struct TrieNode *pNode =  new TrieNode;

   // устанавливаем флаг конца слова в false
   pNode->isEndOfWord = false;

   // инициализируем детей нулевым указателем
   for (int i = 0; i < ALPHABET_SIZE; i++)
       pNode->children[i] = nullptr;

   return pNode;
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if(root->children[i]) return false;
    }
    
    return true;
}

/*
Вставка
Вставка ключа в префиксное дерево является достаточно простой задачей.
Каждый символ вставляется как отдельный узел Trie.
Обратите внимание, что дочерние элементы — это массив указателей (или ссылок) на узлы дерева следующего уровня.
Символ ключа выступает в качестве индекса в массиве дочерних элементов. 
Если входной ключ новый или является расширением существующего ключа, нам нужно построить несуществующие узлы ключа и отметить конец слова для последнего узла.
Если ключ ввода — это префикс существующего ключа в Trie, мы просто помечаем последний узел ключа как конец слова.
Длина ключа определяет глубину Trie.

Алгоритм:
Взять символ от вставляемого ключа.
Проверить, что нет дочернего узла с таким символом.
Присвоить узлу по индексу взятого символа новый узел.
Присвоить текущему узлу только созданный дочерний.
Повторять с п. 1, пока в ключе есть символы.
Установить флаг конца слова для последнего узла.
*/

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key) 
{
    TrieNode* node = root; 

    for (size_t i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'A'; 

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        
        node = node->children[index];
        node->count++;
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}


// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, string key, int depth)
{
   // Если дерево пустое
   if (!root)
       return nullptr;
    // Если дошли до конца ключа
   if (depth == key.size()) {
        // Этот узел больше не конец слова
        // поэтому снимаем метку
       if (root->isEndOfWord)
           root->isEndOfWord = false;
        // Если ключ не является префиксом, удаляем его
       if (isEmpty(root)) {
           delete (root);
           root = nullptr;
       }

       return root;
   }

   // Пока не дошли до конца ключа или определили, 
   // что его нет в дереве, рекурсивно вызываем для ребенка
   // соответствующего символа
   int index = key[depth] - 'A';
   root->children[index] = remove(root->children[index], key, depth + 1);
   // Если у корня нет дочернего слова
   // (удален только один его дочерний элемент),
   // и он не заканчивается другим словом.
   if (isEmpty(root) && root->isEndOfWord == false) {
       delete (root);
       root = nullptr;
   }
    // возвращаем новый корень
   return root;
}

// Возвращает true если ключ есть в дереве, иначе false
bool search(struct TrieNode *root, std::string key)
{
   TrieNode *node = root;
   for (size_t i = 0; i < key.length(); i++)
   {
       int index = key[i] - 'A';
       if (!node->children[index])
           return false;

       node = node->children[index];
   }

   return (node != nullptr && node->isEndOfWord);
}


void PrintAllTree(TrieNode* root)
{
    PrintAllTree(root, "");
}

void PrintAllTree(TrieNode* node, std::string prefix)
{
    if (node->isEndOfWord)
    {
        cout << prefix << endl;
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            char ch = 'A' + i;  // опять же, предполагается маленький регистр

            PrintAllTree(node->children[i], prefix + ch);
        }
    }
}


/***********************************************************************************/


void findMinPrefixes(TrieNode* root)
{
    std::string result;
    
    char buf[100]{};
    FindMinPrefixes(root, buf, 0, result);

    cout << result << endl;
}


void FindMinPrefixes(TrieNode* root, char prefix[], int level, string& result)
{
    if (root == nullptr)
        return;
    
    if (root->count == 1)
    {
        prefix[level] = '\0';
        result += string(prefix) + " ";
        return;
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            prefix[level] = 'A' + i;
            FindMinPrefixes(root->children[i], prefix, level + 1, result);
        }
    }
}


/**************************Функции Автодополнения****************************/

void GetWords(TrieNode* node, std::string prefix, std::vector<std::string> &result)
{
    if(!node) return;

    if (node->isEndOfWord)
    {
       // cout << prefix << endl;        
        result.push_back(prefix);
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            char ch = 'A' + i;  
            GetWords(node->children[i], prefix + ch, result);
        }
    }   
}

void SearchWords(TrieNode* root, const string& word, std::vector<std::string> &result)
{
    if(!root) return;

   TrieNode *node = root;
   for (size_t i = 0; i < word.length(); i++)
   {
       int index = word[i] - 'A';
       // Если не найдено буквы в словаре, то выходим
       if  (!node->children[index]) return;

       node = node->children[index];
   }

   GetWords(node, word, result);
}

/***********************************************************************************/


