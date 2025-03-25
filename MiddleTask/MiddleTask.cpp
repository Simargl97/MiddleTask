#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Создаем упорядоченную map с ключами типа int и значениями типа string
    std::map<int, std::string> myMap = {
        {1, "один"},
        {2, "два"},
        {3, "три"}
    };

    int keyToFind = 2;
    // Поиск элемента по ключу
    auto it = myMap.find(keyToFind); 
    if (it != myMap.end()) {
        std::cout << "Найден элемент: ключ = " << it->first << ", значение = " << it->second << std::endl;
    } else {
        std::cout << "Элемент с ключом " << keyToFind << " не найден." << std::endl;
    }

    // Создаем неупорядоченную map
    std::unordered_map<int, std::string> myUnorderedMap = {
        {1, "один"},
        {2, "два"},
        {3, "три"},
        {4, "четыре"}
    };

    // Подсчет количества элементов, у которых длина строки больше 3 символов
    auto count = std::count_if(myUnorderedMap.begin(), myUnorderedMap.end(),
                               [](const std::pair<const int, std::string>& item) {
                                   return item.second.size() > 3;
                               });
    std::cout << "Количество элементов, где длина строки больше 3: " << count << std::endl;

    // Создаем множество и выводим его элементы в отсортированном порядке
    std::set<int> mySet = {5, 3, 8, 1, 9};

    std::for_each(mySet.begin(), mySet.end(), [](int value) {
        std::cout << value << " ";
    });
    std::cout << std::endl;

    return 0;
}






