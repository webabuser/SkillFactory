#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

const int ALPHABET_SIZE = 100; 
  
// Структура узела дерева 
struct TrieNode
{ 
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
    
    TrieNode()
    {
        isEndOfWord = false;
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = nullptr;
        }
    }
    
    int count = 0; // Сколько слов соответствует конкретной букве.
};

TrieNode *getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode *, string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
void FindMinPrefixes(TrieNode*, char[], int, string&);
void findMinPrefixes(TrieNode*);

void SearchWords(TrieNode*, const string& word,  std::vector<std::string>& result);
void GetWords(TrieNode* node, std::string prefix, std::vector<std::string>& result);

void PrintAllTree(TrieNode *root);
void PrintAllTree(TrieNode *root, std::string);
#endif



