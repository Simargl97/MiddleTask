#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <unordered_map>

// Класс S для демонстрации "тяжёлой" инициализации
class S
{
public:
    std::string m{"Message string."};

    S()
    {
        std::cout << "Конструктор начался.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Объект создан.\n";
    }

    ~S()
    {
        std::cout << "Объект уничтожен.\n";
    }
};

// 1. Ленивый контейнер
template <typename T>
class LazyContainer
{
    std::vector<T*> data;

public:
    explicit LazyContainer(size_t n) : data(n, nullptr) {}

    ~LazyContainer()
    {
        for (auto ptr : data)
        {
            delete ptr;
        }
    }

    T& operator[](size_t index)
    {
        if (index >= data.size()) throw std::out_of_range("Выход за границы массива!");
        if (!data[index]) data[index] = new T();
        return *data[index];
    }

    size_t size() const { return data.size(); }
};

// 2. Пирамидальная сортировка
void heapify(std::vector<int>& arr, int n, int i)
{
    int largest = i;  
    int left = 2 * i + 1;  
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 3. Проверка на перестановку
bool isPermutation(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size()) return false;

    std::unordered_map<int, int> freq;
    for (int num : a) freq[num]++;
    for (int num : b)
    {
        if (freq[num] == 0) return false;
        freq[num]--;
    }
    return true;
}


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Тест LazyContainer
    std::cout << " Демонстрация LazyContainer \n";
    LazyContainer<S> lazyS(3);
    for (size_t i = 0; i < lazyS.size(); ++i)
    {
        std::cout << "Доступ к элементу " << i << ": " << lazyS[i].m << "\n";
    }

    // Тест сортировки
    std::vector<int> vec = {12, 11, 13, 5, 6, 7};
    std::cout << "\nИсходный массив:\n";
    for (int x : vec) std::cout << x << " ";
    std::cout << "\n";

    heapSort(vec);

    std::cout << "Отсортированный массив:\n";
    for (int x : vec) std::cout << x << " ";
    std::cout << "\n";

    // Тест на перестановки
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 5, 1, 4, 2};
    std::vector<int> v3 = {1, 2, 3, 4, 6};

    std::cout << "\nПроверка перестановок:\n";
    std::cout << "v1 и v2: " << (isPermutation(v1, v2) ? "Да" : "Нет") << "\n";
    std::cout << "v1 и v3: " << (isPermutation(v1, v3) ? "Да" : "Нет") << "\n";

    return 0;
}









