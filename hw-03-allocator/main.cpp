#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <chrono>

#include "allocator.h"
#include "container.h"

using namespace std::chrono;

template <typename Map>
void FillMap(Map& map) {
    for (int i = 0, f = 1; i <= 9; ++i, f *= i) {
        map[i] = f;
    }
}

template <typename Map>
void PrintMap(const Map& map) {
    for (const auto & [k, v] : map) {
        std::cout << k << " " << v << std::endl;
    }
}

template <typename Container>
void FillContainer(Container & container) {
    for (int i = 0; i < 10; ++i)
        container.PushBack(i);
}

template <typename Container>
void PrintContainer(const Container & container) {
    for (const auto & el : container)
        std::cout << el << " ";
}

int main() {

    // default map
    std::map<int, int> default_map;
    std::cout << "Default map" << std::endl;
    FillMap(default_map);
    PrintMap(default_map);

    std::cout << std::endl;

    // map with custom allocator
    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>, 11>> custom_allocator_map;
    std::cout << "Map with custom allocator" << std::endl;
    FillMap(custom_allocator_map);
    PrintMap(custom_allocator_map);
    
    std::cout << std::endl;

    // MyVector with std::allocator
    MyVector<int> my_vector_with_std_allocator;
    std::cout << "MyVector with std::allocator" << std::endl;
    FillContainer(my_vector_with_std_allocator);
    PrintContainer(my_vector_with_std_allocator);
    
    std::cout << std::endl;

    //MyVector with custom allocator
    MyVector<int, PoolAllocator<int, 10>> my_vector_with_custom_allocator;
    std::cout << "MyVector with custom allocator" << std::endl;
    FillContainer(my_vector_with_custom_allocator);
    PrintContainer(my_vector_with_custom_allocator);

    return 0;
}   