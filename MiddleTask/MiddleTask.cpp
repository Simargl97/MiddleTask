#include <iostream>
#include <vector>
#include <iterator>

// Константный forward-итератор 
// LegacyForwardIterator

template <typename T>
class ConstForwardIterator {
public:
    // Категория итератора
    using iterator_category = std::forward_iterator_tag;
    // Тип значения
    using value_type = T;
    // Разница между итераторами
    using difference_type = std::ptrdiff_t;
    // Указатель на константное значение
    using pointer = const T*;
    // Константная ссылка на значение
    using reference = const T&; 

    // Конструктор принимает указатель на элемент
    explicit ConstForwardIterator(pointer ptr) : m_ptr(ptr) {}
    
    // Оператор разыменования
    reference operator*() const { return *m_ptr; }
    // Оператор доступа к членам структуры/класса через итератор
    pointer operator->() const { return m_ptr; }

    // Префиксный инкремент: сначала увеличивает указатель, затем возвращает ссылку на себя
    ConstForwardIterator& operator++() { ++m_ptr; return *this; }
    // Постфиксный инкремент: создаёт копию, увеличивает указатель, возвращает копию
    ConstForwardIterator operator++(int) { ConstForwardIterator temp = *this; ++m_ptr; return temp; }
    
    // Операторы сравнения
    bool operator==(const ConstForwardIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ConstForwardIterator& other) const { return m_ptr != other.m_ptr; }

private:
    pointer m_ptr; // Указатель на текущий элемент
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // Итераторы на начало и конец
    ConstForwardIterator<int> begin(vec.data()), end(vec.data() + vec.size()); 
    
    // Перебираем элементы с помощью итератора
    while (begin != end) {
        std::cout << *begin << " "; 
        ++begin;
    }
    std::cout << std::endl;
    
    return 0;
}





