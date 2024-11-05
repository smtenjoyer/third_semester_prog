#include "myalloc.h"

int factorial (int value)
{
    if (value == 0) return 1; 
    else return value*factorial(value - 1);
}

int main() {
    std::map<int, int> map1;
    for (int i = 0; i < 10; i++)
    {
        map1[i] = factorial(i);
    }

    std::map<int, int, std::less<int>, simple_allocator<std::pair<const int, int> > > map2;
    for (int i = 0; i < 10; i++)
    {
        map2[i] = factorial(i);
    }
    my_array<int, simple_allocator<int>> my_first_arr;

    // Вывод на экран всех значений map1
    std::cout << "Значения в map1:" << std::endl;
    for (const auto& pair : map1) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    // Вывод на экран всех значений map1
    std::cout << "Значения в map2:" << std::endl;
    for (const auto& pair : map2) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    my_array<int> arr1;
    for (int i = 0; i < 10; i++)
    {
        arr1.push_back(i);
    }

    simple_allocator<int> myArrayAllocator;
    my_array<int, simple_allocator<int>> myArrayWithAllocator(myArrayAllocator);

    for (int i = 0; i < 10; ++i) {
        myArrayWithAllocator.push_back(i);
    }

    myArrayWithAllocator.print();
    return 0;
}