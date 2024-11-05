#include "myalloc.h"

int main() {
    std::map<int, int> map1;
    for (int i = 0; i < 10; i++)
    {
        int n = 0;
        for (int j = 1; j <= i; j++){
            n+=j;
        }
        map1[i] = n;
    }

    std::map<int, int, std::less<int>, std_11_simple_allocator<std::pair<const int, int> > > map2;
    for (int i = 0; i < 10; i++)
    {
        int n = 0;
        for (int j = 1; j <= i; j++){
            n+=j;
        }
        map2[i] = n;
    }
    my_array<int, std_11_simple_allocator<int>> my_first_arr;

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

    std_11_simple_allocator<int> myArrayAllocator;
    my_array<int, std_11_simple_allocator<int>> myArrayWithAllocator(myArrayAllocator);

    for (int i = 0; i < 10; ++i) {
        myArrayWithAllocator.push_back(i);
    }

    myArrayWithAllocator.print();
    return 0;
}