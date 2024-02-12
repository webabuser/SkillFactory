#include "hashtable.h"
#include <iostream>

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    arr_pairs = new Pair [mem_size];
}
HashTable::~HashTable() {
    delete[] arr_pairs;
}

/* 
int HashTable::hash_func(const LoginName lg_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for(; i < strlen(lg_name); i++) {
        sum += lg_name[i];
    }
    // линейные пробы
    
    const int step = 1;
    return (sum % mem_size + step * offset) % mem_size; 
} 
*/

int HashTable::hash_func_kvadr(const LoginName lg_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for(; i < strlen(lg_name); i++) {
        sum += lg_name[i];
    }
    
    return (sum % mem_size + offset*offset) % mem_size; 
} 

/*
int HashTable::hash_func_double(const LoginName lg_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for(; i < strlen(lg_name); i++) {
        sum += lg_name[i];
    }
    
    const int step = sum % (mem_size * 2);
    
    return (sum % mem_size + step * offset) % mem_size; 
} 
*/


void HashTable::add(const LoginName lg_name, uint* pass_sha)
{
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(;i < mem_size; i++) {
        index = hash_func_kvadr(lg_name, i);

     //   std::cerr <<"Added login " << lg_name << " into array with index(hash) " << index << " and on " << i <<" probe." << " (" << __FILE__ << "- line-" << __LINE__<<")" << std::endl;

        if(arr_pairs[index].status != enPairStatus::engaged) { 
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    if(i >= mem_size)
     {// все перебрали, нет места
        resize();
        add(lg_name, pass_sha);
    } else {
        arr_pairs[index] = Pair(lg_name, pass_sha);
        count++;        
    }
}


void HashTable::del(const LoginName lg_name) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(;i < mem_size; i++) {
        index = hash_func_kvadr(lg_name, i);
        if( arr_pairs[index].status == enPairStatus::engaged && 
            !strcmp(arr_pairs[index].login_name, lg_name))
        {
            arr_pairs[index].status = enPairStatus::deleted;
            count--;
            return;

        } else if(arr_pairs[index].status == enPairStatus::free)
        {
            return;
        }
    }
}

uint* HashTable::find(const LoginName lg_name) {

    for(int i =0;i < mem_size; i++) // Используется для пробирования
    {
        int index = hash_func_kvadr(lg_name, i);

        if( arr_pairs[index].status == enPairStatus::engaged && 
            !strcmp(arr_pairs[index].login_name, lg_name))
        {
            return arr_pairs[index].pwd_sha;

        } else if(arr_pairs[index].status == enPairStatus::free) 
        {
            return nullptr;
        }
    }   
    return nullptr;   
}

const std::vector<std::string> HashTable::FindAllLogins() const
{
    std::vector<std::string> logins;

    for (int i = 0, j = 0; i < mem_size || j < count; i++, j++)
    {
        if (arr_pairs[i].status != free && arr_pairs[i].status != deleted) 
        {
            logins.push_back(arr_pairs[i].login_name);
        }
    }

    return logins;
}


void HashTable::resize()
 {
    Pair* save = arr_pairs;
    int save_ms = mem_size;
    
    mem_size *= 2;
    arr_pairs = new Pair[mem_size];
    count = 0;
    
    for(int i=0; i<save_ms; i++) {
        Pair& old_pair = save[i];
        
        if(old_pair.status == enPairStatus::engaged) {
            add(old_pair.login_name, old_pair.pwd_sha);
        }
    }
    
    delete[] save;
}

void HashTable::print(){
    for(int i = 0; i <= mem_size; i++)
    {
        std::cout << i <<". " << arr_pairs[i].login_name <<" " << arr_pairs[i].pwd_sha << std::endl;
    }
}