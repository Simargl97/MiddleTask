#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::vector<int> vec(10);

    // 1. generate — заполняем вектор числами от 1 до 10.
    int n = 0;
    std::generate(vec.begin(), vec.end(), [&n]() { return ++n; });

    std::cout << "Исходный список: ";
    for (const auto& el : vec)
    {
        std::cout << el << " ";
    }
    std::cout << "\n";

    // 2. transform — преобразуем каждый элемент, например, умножая его на 2.
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return x * 2; });

    std::cout << "После transform (умножение на 2): ";
    for (const auto& el : vec)
    {
        std::cout << el << " ";
    }
    std::cout << "\n";

    // 3. remove — фильтруем числа больше 3.
    auto new_end = std::remove_if(vec.begin(), vec.end(), [](int x) { return x > 3; });

    std::cout << "После remove (удаление чисел > 3): ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (it < new_end)
            std::cout << *it << " ";
        else
            std::cout << "[" << *it << "] ";
    }
    std::cout << "\n";
    
    return 0;
}







