#ifndef LISTONE_H
#define LISTONE_H

#include <iostream>

class Nodeone {
public:
    int data;
    Nodeone* next; // следующий элемент

    Nodeone(int value) { data = value; next = nullptr; } // конструктор
};

class SinglyLinkedList {
private:
    Nodeone* first;  // "голова"
    Nodeone* last;   // "хвост"
    int size;

public:
    SinglyLinkedList() { first = nullptr; last = nullptr; size = 0; }

    void push_back(int value) {
        Nodeone* newlist = new Nodeone(value);
        if (!first) {  
            first = last = newlist; // до этого момента не существовало ни "головы", ни "хвоста"
        } else {
            last->next = newlist; // следующий после хвоста - новый созданный элемент
            last = newlist; // теперь хвост - это новый элемент
        }
        size++;
    }

    void erase(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of range." << std::endl;
            return;
        }

        if (index == 0) { // если удаляем первый элемент
            Nodeone* temp = first;
            first = first->next;
            if (!first) last = nullptr; // если список стал пустым
            delete temp;
            size--;
            return;
        }

        Nodeone* current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next; 
        }

        Nodeone* temp = current->next; // temp - это указатель на удаляемый элемент
        current->next = temp->next; // current теперь указывает не на удаляемый, а на следующий после удаляемого
        if (!current->next) last = current; // если удаляем последний элемент
        delete temp;
        size--;
    }

    void erase(std::vector<int>& indexes) {
        std::sort(indexes.begin(), indexes.end(), [](std::size_t first, std::size_t second) { //сортируем по убыванию, чтобы удалять элементы с конца к началу
            return first > second; 
        });
        for(auto curr_index : indexes){
            if (curr_index < 0 || curr_index >= size) {
                std::cout << "Index out of range." << std::endl;
                return;
            }

            if (curr_index == 0) { // если удаляем первый элемент
                Nodeone* temp = first;
                first = first->next;
                if (!first) last = nullptr; // если список стал пустым
                delete temp;
                size--;
            } else {
                Nodeone* current = first;
                for (int i = 0; i < curr_index - 1; i++) {
                    current = current->next; 
                }

                Nodeone* temp = current->next;
                current->next = temp->next;
                if (!current->next) last = current; // если удаляем последний элемент
                delete temp;
                size--;
            }
        }
        
    }

    int getsize() {
        return size;
    }

    void print() {
        Nodeone* current = first;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << ", ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void insertAtBeginning(int value) {
        Nodeone* newlist = new Nodeone(value);
        if (!first) { // если лист пустой
            first = last = newlist;
        } else {
            newlist->next = first;
            first = newlist;
        }
        size++;
    }

    void insertAt(int index, int value) {
        if (index < 0 || index > size) { 
            std::cout << "Index out of range." << std::endl;
            return;
        }
        
        if (index == 0) {
            insertAtBeginning(value);
            return;
        }

        Nodeone* newlist = new Nodeone(value);
        Nodeone* current = first;

        for (int i = 0; i < index - 1; i++) { 
            current = current->next;
        }

        newlist->next = current->next; 
        current->next = newlist; 

        if (!newlist->next) last = newlist; // если вставляем в конец списка
        size++;
    }

    ~SinglyLinkedList() { 
        while (first) {
            Nodeone* temp = first;
            first = first->next;
            delete temp;
        }
    }

    class Iterator {
    public:
        Iterator(Nodeone* node) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            (*this)++;
            return temp;
        }

        int operator*() const {
            if (current) {
                return current->data;
            } else {
                throw std::out_of_range("Iterator out of range");
            }
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return!(*this == other);
        }

    private:
        Nodeone* current;
    };

    Iterator begin() const {
        return Iterator(first);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};


#endif