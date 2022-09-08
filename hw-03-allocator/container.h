#include <memory>
#include <iostream>

#include "allocator.h"

template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
public:
    MyVector()
        : m_capacity{10}
        , m_size{0}
        , m_data{m_allocator.allocate(m_capacity)}
    {}

    ~MyVector() {
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(&m_data[i]);
        }
    }
    
    void PushBack(const T & elem) {
        if (m_size == m_capacity) {
            std::cerr << "Size exceeded capacity";
        }
        else {
            // &m_data[m_size] = m_allocator.allocate(1);
            m_allocator.construct(&m_data[m_size], elem);
            m_size++;
        }
    }

    void PopBack(const T &elem) {
        if (m_size == 0) {
            std::cerr << "Pop with 0 size";
        }
        else {
            m_allocator.destroy(&m_data[m_size]);
            m_size--;
            // m_allocator.deallocate(&m_data[m_size], 1);
        }
    }

    T const * begin() const {
        return m_data;
    }

    T const * end() const {
        return m_data + m_size;
    }

private:
    Allocator m_allocator;

    const size_t m_capacity;
    size_t m_size;
    T * m_data;
};