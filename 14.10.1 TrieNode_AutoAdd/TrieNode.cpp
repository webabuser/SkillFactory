#include <string>
#include <iostream>
#include <vector>
#include "TrieNode.h"
using namespace std;

// ���������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
   // �������� ������ ��� ����� ����
   struct TrieNode *pNode =  new TrieNode;

   // ������������� ���� ����� ����� � false
   pNode->isEndOfWord = false;

   // �������������� ����� ������� ����������
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
�������
������� ����� � ���������� ������ �������� ���������� ������� �������.
������ ������ ����������� ��� ��������� ���� Trie.
�������� ��������, ��� �������� �������� � ��� ������ ���������� (��� ������) �� ���� ������ ���������� ������.
������ ����� ��������� � �������� ������� � ������� �������� ���������. 
���� ������� ���� ����� ��� �������� ����������� ������������� �����, ��� ����� ��������� �������������� ���� ����� � �������� ����� ����� ��� ���������� ����.
���� ���� ����� � ��� ������� ������������� ����� � Trie, �� ������ �������� ��������� ���� ����� ��� ����� �����.
����� ����� ���������� ������� Trie.

��������:
����� ������ �� ������������ �����.
���������, ��� ��� ��������� ���� � ����� ��������.
��������� ���� �� ������� ������� ������� ����� ����.
��������� �������� ���� ������ ��������� ��������.
��������� � �. 1, ���� � ����� ���� �������.
���������� ���� ����� ����� ��� ���������� ����.
*/

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key) 
{
    TrieNode* node = root; 

    for (size_t i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'A'; 

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        
        node = node->children[index];
        node->count++;
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}


// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, string key, int depth)
{
   // ���� ������ ������
   if (!root)
       return nullptr;
    // ���� ����� �� ����� �����
   if (depth == key.size()) {
        // ���� ���� ������ �� ����� �����
        // ������� ������� �����
       if (root->isEndOfWord)
           root->isEndOfWord = false;
        // ���� ���� �� �������� ���������, ������� ���
       if (isEmpty(root)) {
           delete (root);
           root = nullptr;
       }

       return root;
   }

   // ���� �� ����� �� ����� ����� ��� ����������, 
   // ��� ��� ��� � ������, ���������� �������� ��� �������
   // ���������������� �������
   int index = key[depth] - 'A';
   root->children[index] = remove(root->children[index], key, depth + 1);
   // ���� � ����� ��� ��������� �����
   // (������ ������ ���� ��� �������� �������),
   // � �� �� ������������� ������ ������.
   if (isEmpty(root) && root->isEndOfWord == false) {
       delete (root);
       root = nullptr;
   }
    // ���������� ����� ������
   return root;
}

// ���������� true ���� ���� ���� � ������, ����� false
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
            char ch = 'A' + i;  // ����� ��, �������������� ��������� �������

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


/**************************������� ��������������****************************/

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
       // ���� �� ������� ����� � �������, �� �������
       if  (!node->children[index]) return;

       node = node->children[index];
   }

   GetWords(node, word, result);
}

/***********************************************************************************/


