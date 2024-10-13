#ifndef LIST_H
#define LIST_H

#include <iostream>

#include <iostream>

class list {
public:
    int data;
    list* next;
    list* prev;

    list(int value){  data = value; next = nullptr; prev = nullptr; }
};

class DoublyLinkedList {
private:
    list* first;
    list* last;
    int size;

public:
    DoublyLinkedList() { first = nullptr; last = nullptr; size = 0; }

    void push_back(int value) {
        list* newlist = new list(value);
        if (!first) {  
            first = last = newlist;
        } else {
            last->next = newlist;
            newlist->prev = last;
            last = newlist;
        }
        size++;
    }

    void erase(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of range." << std::endl;
            return;
        }

        list* current = first;
        for (int i = 0; i < index; i++) {
            current = current->next; 
        }

        if (current->prev) {
            current->prev->next = current->next; 
        } else {
            first = current->next; 
        }

        if (current->next) {
            current->next->prev = current->prev; 
        } else {
            last = current->prev; 
        }

        delete current; 
        size--;
    }

    void erase(std::vector<int>& indexes) {
        std::sort(indexes.begin(), indexes.end(), [](std::size_t first, std::size_t second) { //сортируем по убыванию, чтобы удалять элементы с конка к началу
            return first > second; 
        });
        for(auto curr_insex : indexes){
            if (curr_insex < 0 || curr_insex >= size) {
                std::cout << "Index out of range." << std::endl;
                return;
            }

            list* current = first;
            for (int i = 0; i < curr_insex; i++) {
                current = current->next; 
            }

            if (current->prev) {
                current->prev->next = current->next; 
            } else {
                first = current->next; 
            }

            if (current->next) {
                current->next->prev = current->prev; 
            } else {
                last = current->prev; 
            }

            delete current; 
            size--;
        }
        
    }

    int getsize() const {
        return size;
    }

    void print() const {
        list* current = first;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << ", ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void insertAtBeginning(int value) {
        list* newlist = new list(value);
        if (!first) { // If the list is empty
            first = last = newlist;
        } else {
            newlist->next = first;
            first->prev = newlist;
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

        list* newlist = new list(value);
        list* current = first;

        for (int i = 0; i < index - 1; i++) { 
            current = current->next;
        }

        newlist->next = current->next; 
        newlist->prev = current; 

        if (current->next) { 
            current->next->prev = newlist; 
        } else {
            last = newlist; 
        }

        current->next = newlist; 
        size++;
    }

    ~DoublyLinkedList() { 
        while (first) {
            list* temp = first;
            first = first->next;
            delete temp;
        }
    }
};


#endif