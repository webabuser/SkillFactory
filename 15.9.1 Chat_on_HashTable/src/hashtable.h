#pragma once
#include <string.h>
#include <vector>
#include <string>
#include "sha1.h"

#define NAMELENGTH 10  // Зафиксируем длину имени

typedef char LoginName[NAMELENGTH]; // тип имя фрукта

class HashTable { // хеш-таблица
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
        free, // свободен
        engaged, //занят
        deleted //удален
    };


    struct Pair { // пара ключ-значение
        
        Pair(): // конструктор по умолчанию
            login_name(""), 
            pwd_sha(),
            status(enPairStatus::free) {
        }
        
        Pair(const LoginName lg_name, uint* pass_sha): // конструктор копирования
            pwd_sha(pass_sha), status(enPairStatus::engaged) 
        {
            strcpy_s(login_name, lg_name); //memcpy(login_name, lg_name, NAMELENGTH);
        }
        
        Pair& operator = (const Pair& other) 
        { //  оператор присваивания
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
        
        
        LoginName login_name; // имя фрукта (ключ)
        uint* pwd_sha; // количество фрукта (значение)
        enPairStatus status; // состояние ячейки
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
