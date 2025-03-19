#include <iostream>
#include <string>

using namespace std;

int hashFunction(const std::string& key) {
    unsigned long long hash = 0;

    // использование простого числа для лучшего распределения
    const unsigned int multiplier = 31; 
    for (char c : key) {
        hash = hash * multiplier + static_cast<unsigned char>(c);
    }

    // возвращаем индекс в диапазоне от 0 до 99
    return hash % 100; 
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string input;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);
    
    int index = hashFunction(input);
    std::cout << "Хеш-индекс: " << index << std::endl;
    
    return 0;
}




