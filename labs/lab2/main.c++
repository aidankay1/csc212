#include <iostream>

#include "./DynamicArray.cpp"

int main() {
    DynamicArray test_array = DynamicArray(2., 4, 1);

    test_array.prepend(22);
    test_array.prepend(22);
    test_array.append(33);
    test_array.append(11);
    test_array.append(33);

    unsigned int index;

    test_array.findFirstOf(33, &index);
    test_array.findLastOf(22, &index);
    
    test_array.removeLast();
    test_array.removeFirst();

    std::cout << test_array.toString() << '\n';

    std::cout << test_array[2] << '\n';
    
    DynamicArray new_array = DynamicArray(3., 10, 8);

    test_array = new_array;

    std::cout << test_array.toString() << '\n';

    test_array.clear();

    return 0;
}
