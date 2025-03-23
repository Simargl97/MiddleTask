#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

// Константный forward-итератор для массива элементов типа T
// LegacyForwardIterator

template <typename T>
class ConstForwIter
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    // Конструкторы
    ConstForwIter() : m_ptr(nullptr) {}  
    explicit ConstForwIter(pointer ptr) : m_ptr(ptr) {}
    
    // Оператор разыменования
    reference operator*() const { assert(m_ptr); return *m_ptr; }
    pointer operator->() const { return m_ptr; }
    
    // Префиксный и постфиксный инкремент
    ConstForwIter& operator++() { ++m_ptr; return *this; }
    ConstForwIter operator++(int) { ConstForwIter temp = *this; ++m_ptr; return temp; }
    
    // Операторы сравнения
    bool operator==(const ConstForwIter& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ConstForwIter& other) const { return m_ptr != other.m_ptr; }
    
    // Операторы сложения и вычитания (для std::advance, std::distance)
    ConstForwIter operator+(difference_type n) const { return ConstForwIter(m_ptr + n); }
    ConstForwIter operator-(difference_type n) const { return ConstForwIter(m_ptr - n); }
    
    // Разница между итераторами
    difference_type operator-(const ConstForwIter& other) const { return m_ptr - other.m_ptr; }
    
    // Продвигаем итератор вперёд (std::advance)
    ConstForwIter& operator+=(difference_type n) { m_ptr += n; return *this; }

private:
    pointer m_ptr;
};

// std::distance для ConstForwIter
template <typename T>
typename ConstForwIter<T>::difference_type distance(ConstForwIter<T> first, ConstForwIter<T> last)
{
    return last - first;
}

// std::advance для ConstForwIter
template <typename T>
void advance(ConstForwIter<T>& it, typename ConstForwIter<T>::difference_type n)
{
    it += n;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    
    // Исходный вектор
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Итераторы
    ConstForwIter<int> begin(vec.data()), end(vec.data() + vec.size());
    while (begin != end)
    {
        std::cout << *begin << std::endl;
        ++begin;
    }
    
    ConstForwIter<int> beginD(vec.data()), endD(vec.data() + vec.size());
    // Используем std::distance
    std::cout << "Расстояние между begin и end: " << distance(beginD, endD) << std::endl;
    
    // Используем std::advance
    advance(beginD, 2);
    std::cout << "Элемент после сдвига на 2 позиции: " << *beginD << std::endl;
    
    return 0;
}





