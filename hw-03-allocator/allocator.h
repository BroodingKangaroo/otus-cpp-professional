#pragma once

#include <stack>
#include <vector>
#include <queue>

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <array>
#include <stdexcept>
#include <cassert>
#include <memory>


template <typename T, std::size_t max_size>
struct PoolAllocator {
    using value_type = T;

    PoolAllocator() = default;

    template <typename U>
    explicit PoolAllocator(const PoolAllocator<U, max_size>&) {}

    template<class U>
    struct rebind { 
        using other = PoolAllocator<U, max_size>; 
    };

    template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	};

    template <typename U>
	void destroy(U *p) {
		p->~U();
	}

    class MemoryPool {
    public:
        /// available adresses
        std::queue<T *> aa;

        MemoryPool():
            bytes(new char[sizeof (T) * max_size])
        {
            T * begin       = reinterpret_cast<T *> (bytes.get());
            const T * end   = begin + max_size;

            while (begin != end)
                aa.push(begin++);
        }

    private:
        /// actual memory
        std::unique_ptr<char[]> bytes;
    };

    T * allocate(size_t n)
    {
        if (n > max_size)
            throw std::invalid_argument("MemoryPool::allocate(), bad `n'");

        if (mp.aa.empty())
            throw std::bad_alloc();

        T * p = mp.aa.front();
        mp.aa.pop();
        return p;
    }

    void deallocate(T * p, size_t n)
    {
        if (n > max_size)
            throw std::invalid_argument("MemoryPool::deallocate(), bad `n'");

        if (mp.aa.size() == max_size)
            throw std::runtime_error("MemoryPool::deallocate(), `aa' is full");

        mp.aa.push(p);
    }

private:
    MemoryPool mp;
};