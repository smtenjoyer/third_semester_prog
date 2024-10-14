#ifndef LIST_H
#define LIST_H

#include <iostream>

#include <iostream>

class Node {
public:
    int data;
    Node* next; //предыдущий
    Node* prev; //следующий

    Node(int value){  data = value; next = nullptr; prev = nullptr; } //конструктор
};

class DoublyLinkedList {
private:
    Node* first;  // "голова"
    Node* last;   // "хвост"
    int size;

public:
    DoublyLinkedList() { first = nullptr; last = nullptr; size = 0; }

    void push_back(int value) {
        Node* newlist = new Node(value);
        if (!first) {  
            first = last = newlist; // до этого момента не существовало ни "головы", ни "хвоста"
        } else {
            last->next = newlist; //сделующий после хвоста - новый созданный элемент
            newlist->prev = last; //перед созданным элементом - хвост
            last = newlist; //теперь хвост - это новый элемент
        }
        size++;
    }

    void erase(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of range." << std::endl;
            return;
        }

        Node* current = first;
        for (int i = 0; i < index; i++) {
            current = current->next; 
        }

        if (current->prev) {
            current->prev->next = current->next; 
        } else { //если удаляем первый элемент
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

            Node* current = first;
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

    int getsize() {
        return size;
    }

    void print() {
        Node* current = first;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << ", ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void insertAtBeginning(int value) {
        Node* newlist = new Node(value);
        if (!first) { // если лист пустой
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

        Node* newlist = new Node(value);
        Node* current = first;

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
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }
};


#endif