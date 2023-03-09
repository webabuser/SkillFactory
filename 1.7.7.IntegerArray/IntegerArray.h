#pragma once
#include <limits>
#include <initializer_list>
#include <iostream>
#include <string>
#include <cmath>



class IntegerArray {
 public:
    IntegerArray();
    IntegerArray(int length);
    IntegerArray(const IntegerArray& other);
    IntegerArray(const std::initializer_list<int>& l);
    
    
    ~IntegerArray();
    
    void erase();
    
    int& operator[](int index);
    
    // оператор присваивания, который присваивает один объект IntegerArray другому возвращает ссылку на самого себя
    IntegerArray& operator=(const IntegerArray& other);

    int getLength() const;
    
    // reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
    void reallocate(int newLenght);
    void resize(int newLength);
    
    void insertBefore(int value, int index);
    void PushFront(int value);
    void PushBack(int value);
    
    void Remove(int index);
    
    bool Find(int value, size_t & index_result);
    
    void Show() const;
    
 private:
    int _length;
    int* _data;
};