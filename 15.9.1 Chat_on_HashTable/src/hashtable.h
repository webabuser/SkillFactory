#pragma once
#include <string.h>
#include <vector>
#include <string>
#include "sha1.h"

#define NAMELENGTH 10  // ����������� ����� �����

typedef char LoginName[NAMELENGTH]; // ��� ��� ������

class HashTable { // ���-�������
 public:
    HashTable();
    ~HashTable();
    
    void add(const LoginName lg_name, uint* pass_sha);
    void del(const LoginName lg_name);
    uint* find(const LoginName lg_name);
    const std::vector<std::string> FindAllLogins() const;
   
    void print();
        
 private:
    enum enPairStatus {
        free, // ��������
        engaged, //�����
        deleted //������
    };


    struct Pair { // ���� ����-��������
        
        Pair(): // ����������� �� ���������
            login_name(""), 
            pwd_sha(),
            status(enPairStatus::free) {
        }
        
        Pair(const LoginName lg_name, uint* pass_sha): // ����������� �����������
            pwd_sha(pass_sha), status(enPairStatus::engaged) 
        {
            strcpy_s(login_name, lg_name); //memcpy(login_name, lg_name, NAMELENGTH);
        }
        
        Pair& operator = (const Pair& other) 
        { //  �������� ������������
            pwd_sha =  other.pwd_sha;
            strcpy_s(login_name, other.login_name); // memcpy(login_name, other.login_name, NAMELENGTH);
            status = other.status;
            
            return *this;
        }
        
        bool operator == (const Pair& other) 
        {
            return  status == other.status &&
                    (status != enPairStatus::engaged || (pwd_sha == other.pwd_sha && !strcmp(login_name, other.login_name)));
        }
        
        
        LoginName login_name; // ��� ������ (����)
        uint* pwd_sha; // ���������� ������ (��������)
        enPairStatus status; // ��������� ������
    };
        
 private: 
    //int hash_func(const LoginName lg_name, int offset);
    int hash_func_kvadr(const LoginName lg_name, int offset);
    //int hash_func_double(const LoginName lg_name, int offset);
    void resize();
        
 private:       
    Pair* arr_pairs;
    int mem_size;
    int count;
};
