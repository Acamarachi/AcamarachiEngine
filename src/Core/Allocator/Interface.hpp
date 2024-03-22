#pragma once

#include <unistd.h>
#include "../Expected.hpp"

namespace Acamarachi::Core
{
	size_t calculatePadding(const size_t baseAddress, const size_t alignment);

    size_t calculatePaddingWithHeader(const size_t baseAddress, const size_t alignment, const size_t headerSize);

    size_t align(size_t x, size_t alignment);

    enum class AllocatorErrorValue
    {
        OutOfMemory,

        NoReallocImpl,
        NoAllocImpl,
        NoFreeImpl,
    };

    using AllocatorError = Acamarachi::Core::Expected<void *, AllocatorErrorValue>;

    using AllocFunction = AllocatorError (*)(void *, size_t size, size_t alignment);
    using ReallocFunction = AllocatorError (*)(void *, void *old_ptr, size_t size, size_t alignment);
    using FreeFunction = void (*)(void *, void *ptr);

    struct AllocatorVirtualTable {
        AllocFunction alloc = nullptr;
        ReallocFunction realloc = nullptr;
        FreeFunction free = nullptr;
    };

    class AllocatorInterface
    {
    private:
        void *typeErasedAllocator = nullptr;
        AllocatorVirtualTable vtable;

    public:
        AllocatorInterface(void *allocator, AllocFunction allocFn, ReallocFunction reallocFn, FreeFunction freeFn)
        {
            typeErasedAllocator = allocator;
            vtable.alloc = allocFn;
            vtable.realloc = reallocFn;
            vtable.free = freeFn;
        }

        AllocatorError alloc(size_t size, size_t alignment)
        {
            return vtable.alloc(typeErasedAllocator, size, alignment);
        }

        AllocatorError realloc(void* old_ptr, size_t size, size_t alignment)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, alignment);
        }

        void free(void *ptr)
        {
            return vtable.free(typeErasedAllocator, ptr);
        }

        static AllocatorInterface getCAllocatorInterface();
    };
}