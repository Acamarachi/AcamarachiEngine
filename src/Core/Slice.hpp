#pragma once

#ifdef _MSC_VER
#include "MSVC/unistd.h"
#else
#include <unistd.h>
#endif
#include <iterator>
#include <cstddef>
#include <assert.h>
#include <iostream>

namespace Acamarachi::Core
{

    template <typename T>
    class Slice
    {
    public:
        T *ptr;
        size_t len;

        struct Iterator
        {
        private:
            T *ptr;

        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;

            Iterator(pointer ptr) : ptr(ptr) {}

            reference operator*() const { return *ptr; }
            pointer operator->() { return ptr; }
            Iterator &operator++()
            {
                ptr += 1;
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator tmp = *this;
                (*this) += 1;
                return tmp;
            }
            friend bool operator==(const Iterator &a, const Iterator &b) { return a.ptr == b.ptr; }
            friend bool operator!=(const Iterator &a, const Iterator &b) { return a.ptr != b.ptr; }
        };

        Slice() : ptr(nullptr), len(0) {}
        Slice(T *ptr, size_t len) : ptr(ptr), len(len) {}
        Slice(const Slice<T> &other) : ptr(other.ptr), len(other.len) {}
        Slice(Slice<T> &&other) noexcept
        {
            ptr = other.ptr;
            len = other.len;

            other.ptr = nullptr;
            other.len = 0;
        }

        ~Slice()
        { };

        T &operator[](size_t index)
        {
            assert(index < len && "Out of bound");
            return ptr[index];
        }

        T operator[](size_t index) const
        {
            assert(index < len && "Out of bound");
            return ptr[index];
        }

        Slice<T> operator()(size_t start, size_t end) const
        {
            assert(start < len);
            assert(end <= len);
            assert(start < end);
            return Slice<T>(ptr + start, end - start);
        }

        Slice<T> &operator=(Slice<T> &&other) noexcept
        {
            ptr = std::move(other.ptr);
            len = std::move(other.len);

            other.ptr = nullptr;
            other.len = 0;
            return *this;
        }

        Iterator begin() { return Iterator(ptr); }
        Iterator end() { return Iterator(ptr + len); }
    };

}