#pragma once

#include <unistd.h>
#include "../Error.hpp"
#include "../Slice.hpp"

namespace Acamarachi::Core::Allocator
{
    size_t align(size_t x, size_t alignment);

    using AllocFunction = ErrorOr<void *> (*)(void *, size_t size, size_t alignment);
    using ReallocFunction = ErrorOr<void *> (*)(void *, void *old_ptr, size_t size, size_t alignment);
    using FreeFunction = void (*)(void *, void *ptr);

    struct AllocatorVirtualTable {
        AllocFunction alloc = nullptr;
        ReallocFunction realloc = nullptr;
        FreeFunction free = nullptr;
    };

    class Interface
    {
    private:
        void *typeErasedAllocator = nullptr;
        AllocatorVirtualTable vtable;

    public:
        Interface(void *allocator, AllocFunction allocFn, ReallocFunction reallocFn, FreeFunction freeFn)
        {
            typeErasedAllocator = allocator;
            vtable.alloc = allocFn;
            vtable.realloc = reallocFn;
            vtable.free = freeFn;
        }

        ErrorOr<void *> alloc(size_t size)
        {
            return vtable.alloc(typeErasedAllocator, size, 16);
        }

        ErrorOr<void *> calloc(size_t size)
        {
            auto maybe_mem = vtable.alloc(typeErasedAllocator, size, 16);
            if (!maybe_mem) {
                return maybe_mem.error();
            }

            void *mem = maybe_mem.result();
            memset(mem, 0, size);
            return mem;
        }

        ErrorOr<void *> allocAlignment(size_t size, size_t alignment)
        {
            return vtable.alloc(typeErasedAllocator, size, alignment);
        }

        template<typename T>
        ErrorOr<Slice<T>> allocSlice(size_t size, size_t alignment)
        {
            auto maybe_memory = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment);
            if (!maybe_memory) {
                return maybe_memory.error();
            }

            return Acamarachi::Core::Slice((T *)maybe_memory.result(), size);
        }

        template<typename T>
        ErrorOr<Slice<T>> callocSlice(size_t size, size_t alignment)
        {
            auto maybe_memory = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment);
            if (!maybe_memory) {
                return maybe_memory.error();
            }
            void *mem = maybe_memory.result();
            memset(mem, 0, sizeof(T) * size);
            return Acamarachi::Core::Slice((T *)mem, size);
        }

        ErrorOr<void *> realloc(void* old_ptr, size_t size)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, 16);
        }

        ErrorOr<void *> reallocAlignment(void* old_ptr, size_t size, size_t alignment)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, alignment);
        }

        template<typename T>
        ErrorOr<Slice<T>> reallocSlice(Slice<T>& oldSlice, size_t size, size_t alignment)
        {
            auto maybe_memory = vtable.realloc(typeErasedAllocator, (void *)oldSlice.ptr, sizeof(T) * size, alignment);
            if (!maybe_memory) {
                return maybe_memory.error();
            }
            oldSlice = std::move(Slice<T>());
            return Slice<T>((T *)maybe_memory.result(), size);
        }

        void free(void *ptr)
        {
            return vtable.free(typeErasedAllocator, ptr);
        }

        template<typename T>
        void free(Slice<T>& slice)
        {
            vtable.free(typeErasedAllocator, (void *)slice.ptr);
            slice = std::move(Slice<T>());
        }
    };

    Interface getCAllocatorInterface();

    size_t getCAllocatorTotalBytesUsage();
    size_t getCAllocatorCurrentBytesUsage();
    size_t getCAllocatorAllocationCount() ;
    size_t getCAllocatorFreeCount();
}