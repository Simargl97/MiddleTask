#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
     // 1. Использование std::partial_sort_copy
    // Создаем вектор из 10 элементов, заполняем его числами от 1 до 10 с помощью generate.
    std::vector<int> vec(10);
    int n = 0;
    std::generate(vec.begin(), vec.end(), [&n]() { return ++n; });

    std::cout << "Исходный список: ";
    for (const auto& el : vec)
        std::cout << el << " ";
    std::cout << "\n";

    // Создаем контейнер для результата сортировки.
    std::vector<int> partialResult(5);
    std::partial_sort_copy(vec.begin(), vec.end(), partialResult.begin(), partialResult.end());

    std::cout << "Результат partial_sort_copy (5 наименьших элементов): ";
    for (const auto& el : partialResult)
        std::cout << el << " ";
    std::cout << "\n\n";


    // 2. Использование lower_bound и upper_bound для целочисленного массива из 10 элементов
    int arr[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    int key = 10;
    auto lb = std::lower_bound(std::begin(arr), std::end(arr), key);
    auto ub = std::upper_bound(std::begin(arr), std::end(arr), key);

    std::cout << "Массив: ";
    for (int i = 0; i < 10; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    if(lb != std::end(arr))
        std::cout << "lower_bound для " << key << ": " << *lb << "\n";
    else
        std::cout << "lower_bound для " << key << " не найден\n";

    if(ub != std::end(arr))
        std::cout << "upper_bound для " << key << ": " << *ub << "\n";
    else
        std::cout << "upper_bound для " << key << " не найден\n\n";

    // Для демонстрации методов set::lower_bound и set::upper_bound создадим set
    std::set<int> s = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    auto set_lb = s.lower_bound(key);
    auto set_ub = s.upper_bound(key);

    if(set_lb != s.end())
        std::cout << "set.lower_bound для " << key << ": " << *set_lb << "\n";
    else
        std::cout << "set.lower_bound для " << key << " не найден\n";

    if(set_ub != s.end())
        std::cout << "set.upper_bound для " << key << ": " << *set_ub << "\n";
    else
        std::cout << "set.upper_bound для " << key << " не найден\n\n";


    // 3. Использование includes и set_difference для сортированных множеств
    std::vector<int> setA = {1, 3, 5, 7, 9, 11, 13};
    std::vector<int> setB = {3, 7, 9};

    bool isIncluded = std::includes(setA.begin(), setA.end(), setB.begin(), setB.end());
    std::cout << "setB " << (isIncluded ? "является" : "не является") << " подмножеством setA\n";

    std::vector<int> diffResult;
    diffResult.resize(setA.size());

    // Вычисляем разность множеств: элементы из setA, которых нет в setB.
    auto it = std::set_difference(setA.begin(), setA.end(),
                                  setB.begin(), setB.end(),
                                  diffResult.begin());
    diffResult.resize(std::distance(diffResult.begin(), it));

    std::cout << "Разность setA и setB (элементы, присутствующие в setA, но отсутствующие в setB): ";
    for (const auto& el : diffResult)
        std::cout << el << " ";
    std::cout << "\n";

    return 0;
}







