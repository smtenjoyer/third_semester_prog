#ifndef CONSISTENT_H
#define CONSISTENT_H

#include <iostream>
#include <initializer_list>
#include <stdexcept> 
#include <vector>
#include <algorithm>

template <typename Type> class my_array{
private:
    Type* arr;
    std::size_t capasity; //"вместимость" данного конкретного массива
    std::size_t currentsize; //текущее количество элементов данного массива

    void resize(std::size_t newcapasity){ 
        Type* newarr = new Type[newcapasity];
        for (std::size_t i = 0; i < currentsize; i++)
        {
            newarr[i] = arr[i];
        }
        delete[] arr;
        arr = newarr;
        capasity = newcapasity;
    }
public:
    my_array(): capasity(10), currentsize(0){
        arr = new Type[capasity];
    }
    ~my_array(){
        delete[] arr;
    }

    void push_back(const Type& value){
        if (currentsize>= capasity){
            resize(capasity*2);
        }
        arr[currentsize++] = value;
    }
    void insert(std::size_t index, const Type& value){
        if (index > currentsize){
            throw std::out_of_range("Index out of Range");
        }
        if (currentsize >= capasity){
            resize(capasity * 2);
        }
        for (std::size_t i = currentsize; i > index; i--){
            arr[i] = arr[i-1];
        }
        arr[index] = value;
        currentsize++;
    }

    void erase(std::size_t index){
        if(index-1 >= currentsize){
            throw std::out_of_range("Index out of range");
        }
        for (std::size_t i = index-1; i < currentsize -1; i++){
            arr[i] = arr[i+1];
        }
        currentsize--;
    }
    void erase(std::vector<std::size_t>& indexes){
        std::sort(indexes.begin(), indexes.end(), [](std::size_t first, std::size_t second) { //сортируем по убыванию, чтобы удалять элементы с конка к началу
            return first > second; 
        });
        for(auto curr_insex : indexes){
            if(curr_insex-1 >= currentsize){
                throw std::out_of_range("Index out of range");
            }
            for (std::size_t i = curr_insex-1; i < currentsize -1; i++){
                arr[i] = arr[i+1];
            }
            currentsize--;
        }
    }
    
    std::size_t size(){
        return currentsize;
    }

    Type& operator[](std::size_t index){
        if(index >= currentsize){
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }
    void print(){
        for (size_t i = 0; i < currentsize; i++){
            std::cout << arr[i];
            if(i < currentsize - 1){
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    struct Iterator {
        int* ptr;

        // Конструктор
        Iterator(int* ptr) : ptr(ptr) {}

        // Оператор разыменования
        int& operator*() {
            if (ptr==nullptr) {
                throw std::out_of_range("Index out of range"); // Исключение для недопустимого индекса
            }
            return *ptr;
        }
        int& get() {
            if (ptr == nullptr) {
                throw std::out_of_range("Index out of range"); // Исключение для недопустимого индекса
            }
            return *ptr;
        }

        // Оператор сравнения (для проверки конца итерации)
        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }

        // Перемещение итератора на следующий элемент
        Iterator& operator++() {
            ptr++;
            return *this;
        }

    };
    // Возвращает итератор на начало контейнера
    Iterator begin() {
        return Iterator(arr);
    }

    // Возвращает итератор на конец контейнера
    Iterator end() {
        return Iterator(arr + currentsize);
    }

};


#endif