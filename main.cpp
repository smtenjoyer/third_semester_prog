#include <iostream>
#include <stdexcept>
#include "consistent.h"
#include "list.h"
#include "listone.h"
int main() {

    my_array<int> my_arr;
    for (int i = 0; i < 10; i++){
        my_arr.push_back(i);
    }
    std::cout << "1) В контейнере: ";
    my_arr.print();

    std::cout << "Размер контейнера: " << my_arr.size() << std::endl;
    std::vector<std::size_t> indexes = {3,5,7}; //удаляем несколько элементов разом
    my_arr.erase(indexes);
    std::cout << "В контейнере после удаления элементов: ";
    my_arr.print();

    my_arr.insert(0,10);
    std::cout << "В контейнере после вставки 10 в начало контейнера: ";
    my_arr.print();

    auto middle = my_arr.size() / 2;
    my_arr.insert(middle, 20);
    std::cout << "В контейнере после вставки 20 в середину контейнера: ";
    my_arr.print();

    my_arr.push_back(30);
    std::cout << "В контейнере после вставки 30 в конец контейнера: ";
    my_arr.print();

    

    
    DoublyLinkedList list;

    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    std::cout << "2) В контейнере: ";
    list.print(); 

    std::cout << "Размер контейнера: " << list.getsize() << std::endl; // Expected: 10

    std::vector<int> list_indexes = {2,4,6};
    list.erase(list_indexes); 

    std::cout << "В контейнере после удаления элементов: ";
    list.print(); 
    list.insertAtBeginning(10);

    std::cout << "В контейнере после вставки 10 в начало контейнера: ";
    list.print(); 
    middle = list.getsize() / 2;
    list.insertAt(middle, 20);

    std::cout << "В контейнере после вставки 20 в середину контейнера: ";
    list.print(); 

    list.push_back(30);

    std::cout << "В контейнере после вставки 30 в конец контейнера: ";
    list.print(); 

    list.erase(0); 
    std::cout << "В контейнере после удаления одного элемента: ";
    list.print(); 



    SinglyLinkedList listone;

    for (int i = 0; i < 10; ++i) {
        listone.push_back(i);
    }

    std::cout << "2) В контейнере: ";
    listone.print(); 

    std::cout << "Размер контейнера: " << listone.getsize() << std::endl; // Expected: 10

    listone.erase(list_indexes); 

    std::cout << "В контейнере после удаления элементов: ";
    listone.print(); 
    listone.insertAtBeginning(10);

    std::cout << "В контейнере после вставки 10 в начало контейнера: ";
    listone.print(); 
    middle = listone.getsize() / 2;
    listone.insertAt(middle, 20);

    std::cout << "В контейнере после вставки 20 в середину контейнера: ";
    listone.print(); 

    listone.push_back(30);

    std::cout << "В контейнере после вставки 30 в конец контейнера: ";
    listone.print(); 

    listone.erase(3); 
    std::cout << "В контейнере после удаления одного элемента: ";
    listone.print(); 

    for (SinglyLinkedList::Iterator it = listone.begin(); it!= listone.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}