#include "IntegerArray.h"
using namespace std::string_literals;

IntegerArray::IntegerArray() {std::cout << "Worked Default Constructor - "<< this << std::endl;}

IntegerArray::IntegerArray(int length) 
    : _length(length){
        
        if(length <= 0 || length > std::numeric_limits<int>::max()) {
            throw std::invalid_argument(std::to_string(length) + " не верный аргумент в конструкторе"s);
        }

        _data = new int[length]{0};
        
        std::cout << "Worked Constructor - " << this << std::endl;
}

IntegerArray::IntegerArray(const IntegerArray& other){
    // Set the size of the new array appropriately
    // Сначала уничтожаем полностью существующий контейнер, реаллоцируем новый нулевой, с нужной длиной и далее совершаем глубокое копирование.
    reallocate(other.getLength());
    
    // Then copy the elements, здесь _length уже новая
    for (int i = 0; i < _length; ++ i){
        _data[i] = other._data[i];
    } 
}

IntegerArray::IntegerArray(const std::initializer_list<int>& l){
    _length = l.size();
    _data = new int[_length]{0};

    int i = 0;
    for(const int* ptr = l.begin(); ptr != l.end() && i < _length; ++ptr, ++i){
        _data[i] = *ptr;
    }
    
    std::cout << "Worked initializer_list Constructor - " << this << std::endl;
 }


IntegerArray& IntegerArray::operator=(const IntegerArray& other){
    //Проверка не ссылается ли другой объект на этот же, т.е. на самоприсваивание
    if(&other == this) return *this;
    
    //Уничтожаем старый контейнер и делаем глубокое копирование
    reallocate(other.getLength());
    
    // здесь _length уже имеет новую длину другого объекта назначенную в функции reallocate
    for(int i = 0; i < _length; ++i){
        _data[i] = other._data[i];
    }
    
    return *this;
}



IntegerArray::~IntegerArray(){
    delete[] _data;
     // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
    std::cout << '\n'; 
    std::cout << "Worked DeStructor - " << this << std::endl; 
}


void IntegerArray::erase(){
    delete[] _data;
    
    // We need to make sure we set m_data to nullptr here, otherwise it will
    // be left pointing at deallocated memory!
    _data = nullptr;
    _length = 0;
}

int& IntegerArray::operator[](int index){
    if(index < 0 || index > _length) throw std::invalid_argument(std::to_string(index) + " не верный аргумент в operator[]"s);
    return _data[index];
}

int IntegerArray::getLength() const {
    return _length;
}

// reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
void IntegerArray::reallocate(int newLength){
    // First we delete any existing elements
    erase(); 
    
    // If our array is going to be empty now, return here
    if (newLength <= 0)
        return; 
    
    _data = new int[newLength]{0};
    _length = newLength;
}     

// resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
void IntegerArray::resize(int newLength){
    // if the array is already the right length, we're done
    if (newLength == _length)
        return;
    
    // If we are resizing to an empty array, do that and return  
    if(newLength <= 0){
        erase();
        return;
    }
    
    // Now we can assume newLength is at least 1 element.  This algorithm
    // works as follows: First we are going to allocate a new array.  Then we
    // are going to copy elements from the existing array to the new array.
    // Once that is done, we can destroy the old array, and make m_data
    // point to the new array.
    
    // First we have to allocate a new array
    int* newdata = new int[newLength]{0};  // int* data{ new int[newLength] }; - universal initialisation  
    
    // Then we have to figure out how many elements to copy from the existing
    // array to the new array.  We want to copy as many elements as there are
    // in the smaller of the two arrays.
    
    if(_length > 0){
        
        int countNewElems = (newLength > _length) ? _length : newLength;
        
        // Now copy the elements one by one
        for(int i = 0; i < countNewElems; ++i){
            newdata[i] = _data[i];
        }
    }
    
    // Now we can delete the old array because we don't need it any more
    delete[] _data;
    
    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    
    _data = newdata;
    _length = newLength;
}

void IntegerArray::insertBefore(int value, int index){
    //Проверка на допустимость индекса
    if(index < 0 || index > _length) throw std::invalid_argument(std::to_string(index) + " не верный аргумент в insertBefore"s);
    
    // First create a new array one element larger than the old array
    
    int* newdata = new int[_length + 1]{0};
    
    // Copy all of the elements up to the index
    for (int i = 0; i < index; ++ i){
        newdata[i] = _data[i];
    }
    
    // Insert our new element into the new array
    newdata[index] = value;
    
    // Copy all of the values after the inserted element
    for(int i = index; i < _length; ++i){
        
        newdata[i+1] = _data[i];
    }
    
    //Finally, delete the old array, and use the new array instead
    
    delete[] _data;
    _data = newdata;
    ++_length;
}

void IntegerArray::PushFront(int value){
    insertBefore(value, 0);
}

void IntegerArray::PushBack(int value){
    insertBefore(value, _length);
}

//Удаляет элемент из массива
void IntegerArray::Remove(int index){
    // Проверяем входил ли индекс в имеющиеся
    if(index < 0 || index > _length) throw std::invalid_argument(std::to_string(index) + " не верный index в remove"s);
    
    // If this is the last remaining element in the array, set the array to empty and bail out
    if(_length == 1){
        erase();
        return;
    }
    
    // First create a new array one element smaller than the old array
    int* newdata = new int[_length - 1]{0};
    
    // Copy all of the elements up to the index
    for (int i = 0; i < index; ++i){
        newdata[i] = _data[i];
    }
    
    // Copy all of the values after the removed element
    for(int i = index+1; i < _length; ++ i){
        newdata[i - 1] = _data[i];
    }
    
    // Finally, delete the old array, and use the new array instead
    delete[] _data;
    _data = newdata;
    --_length;
}

void IntegerArray::Show() const {
    for(int i = 0; i < _length; ++i){
        std::cout << _data[i];
        
        if(i != _length-1) std::cout << ", ";
    }
    
    std::cout << std::endl;
}


bool IntegerArray::Find(int value, size_t & index_result){
    for(int i = 0; i < _length; ++i){
        if(_data[i] == value){
            index_result = i;
            return true;
        }    
        
    }
    return false;
}













