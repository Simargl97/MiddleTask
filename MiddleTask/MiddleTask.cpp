#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <iterator>

// Структура с динамическими данными
struct Data
{
    int* value;
    Data(int v) { value = new int(v); }
    Data(const Data& other) { value = new int(*other.value); }
    ~Data() { delete value; }
};

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    // 1. Глубокое копирование с copy
    std::vector<Data> source = { Data(10), Data(20), Data(30) };
    std::vector<Data> destination;
    destination.reserve(source.size());
    std::copy(source.begin(), source.end(), std::back_inserter(destination));
    std::cout << "Глубокое копирование: " << *destination[0].value << std::endl;

    // 2. Поверхностное копирование с copy
    std::vector<int*> shallow_source = { new int(1), new int(2), new int(3) };
    std::vector<int*> shallow_copy;
    shallow_copy.reserve(shallow_source.size());
    std::copy(shallow_source.begin(), shallow_source.end(), std::back_inserter(shallow_copy));
    std::cout << "Поверхностное копирование: " << *shallow_copy[0] << std::endl;

    // Освобождение памяти
    for (int* ptr : shallow_source) delete ptr;

    // 3. Использование copy для std::unordered_map
    std::unordered_map<int, std::string> original_map = { {1, "One"}, {2, "Two"}, {3, "Three"} };
    std::unordered_map<int, std::string> copied_map;
    std::copy(original_map.begin(), original_map.end(), std::inserter(copied_map, copied_map.begin()));
    std::cout << "Копирование unordered_map: " << copied_map[2] << std::endl;

    // 4. Использование fill для заполнения массива
    int arr[5];
    std::fill(std::begin(arr), std::end(arr), 42);
    std::cout << "Заполненный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    // 5. Использование find
    std::vector<int> numbers = { 1, 2, 3, 4, 5 };
    auto it = std::find(numbers.begin(), numbers.end(), 3);
    if (it != numbers.end()) {
        std::cout << "Элемент найден: " << *it << std::endl;
    } else {
        std::cout << "Элемент не найден" << std::endl;
    }
    return 0;
}







