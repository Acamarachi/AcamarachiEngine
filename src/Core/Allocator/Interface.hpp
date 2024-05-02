#pragma once

#ifdef _MSC_VER
#include "../MSVC/unistd.h"
#else
#include <unistd.h>
#endif

#include "../Slice.hpp"

namespace Acamarachi::Core::Allocator
{
    enum class Result
    {
        Success,
        OutOfMemory,
        NoReallocImpl,
        NoAllocImpl,
        NoFreeImpl,
    };

    size_t align(size_t x, size_t alignment);

    using AllocFunction = Result (*)(void *, size_t size, size_t alignment, void **out_ptr);
    using ReallocFunction = Result (*)(void *, void *old_ptr, size_t size, size_t alignment, void **out_ptr);
    using FreeFunction = Result (*)(void *, void *ptr);

    struct AllocatorVirtualTable
    {
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

        Result alloc(size_t size, void **ptrOut)
        {
            return vtable.alloc(typeErasedAllocator, size, 16, ptrOut);
        }

        Result calloc(size_t size, void **ptrOut)
        {
            const Result res = vtable.alloc(typeErasedAllocator, size, 16, ptrOut);
            if (res != Result::Success)
                return res;

            memset(*ptrOut, 0, size);
            return Result::Success;
        }

        Result allocAlignment(size_t size, size_t alignment, void **ptrOut)
        {
            return vtable.alloc(typeErasedAllocator, size, alignment, ptrOut);
        }

        template <typename T>
        Result allocSlice(size_t size, size_t alignment, Slice<T> &slice)
        {
            void *ptr = nullptr;
            Result res = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment, &ptr);
            if (res != Result::Success) {
                return res;
            }

            slice = std::move(Acamarachi::Core::Slice((T *)ptr, size));
            return Result::Success;
        }

        template <typename T>
        Result callocSlice(size_t size, size_t alignment, Slice<T> &slice)
        {
            void *ptr = nullptr;
            Result res = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment, &ptr);
            if (res != Result::Success)
                return res;

            memset(ptr, 0, sizeof(T) * size);
            slice = std::move(Acamarachi::Core::Slice((T *)ptr, size));
            return Result::Success;
        }

        Result realloc(void *old_ptr, size_t size, void **ptrOut)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, 16, ptrOut);
        }

        Result reallocAlignment(void *old_ptr, size_t size, size_t alignment, void **ptrOut)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, alignment, ptrOut);
        }

        template <typename T>
        Result reallocSlice(Slice<T> &oldSlice, size_t size, size_t alignment, Slice<T> &newSlice)
        {
            void *ptr = nullptr;
            Result res = vtable.realloc(typeErasedAllocator, sizeof(T) * size, alignment, &ptr);
            if (res != Result::Success)
                return res;

            oldSlice = std::move(Slice<T>());
            newSlice = std::move(Slice<T>((T *)ptr, size));
            return Result::Success;
        }

        Result free(void *ptr)
        {
            return vtable.free(typeErasedAllocator, ptr);
        }

        template <typename T>
        Result free(Slice<T> &slice)
        {
            const Result res = vtable.free(typeErasedAllocator, (void *)slice.ptr);
            slice = std::move(Slice<T>());
            return res;
        }
    };

    Interface getCAllocatorInterface();

    size_t getCAllocatorTotalBytesUsage();
    size_t getCAllocatorCurrentBytesUsage();
    size_t getCAllocatorAllocationCount();
    size_t getCAllocatorFreeCount();
}