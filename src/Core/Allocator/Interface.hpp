#pragma once

#ifdef _MSC_VER
#include "../MSVC/unistd.h"
#else
#include <unistd.h>
#endif

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

        Result alloc(size_t size, void **ptr_out)
        {
            return vtable.alloc(typeErasedAllocator, size, 16, ptr_out);
        }

        Result calloc(size_t size, void **ptr_out)
        {
            const Result res = vtable.alloc(typeErasedAllocator, size, 16, ptr_out);
            if (res != Result::Success)
                return res;

            memset(*ptr_out, 0, size);
            return Result::Success;
        }

        Result allocAlignment(size_t size, size_t alignment, void **ptr_out)
        {
            return vtable.alloc(typeErasedAllocator, size, alignment, ptr_out);
        }

        // template<typename T>
        // ResultOr<Slice<T>> allocSlice(size_t size, size_t alignment)
        // {
        //     auto maybe_memory = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment);
        //     if (!maybe_memory) {
        //         return maybe_memory.error();
        //     }

        //     return Acamarachi::Core::Slice((T *)maybe_memory.result(), size);
        // }

        // template<typename T>
        // ResultOr<Slice<T>> callocSlice(size_t size, size_t alignment)
        // {
        //     auto maybe_memory = vtable.alloc(typeErasedAllocator, sizeof(T) * size, alignment);
        //     if (!maybe_memory) {
        //         return maybe_memory.error();
        //     }
        //     void *mem = maybe_memory.result();
        //     memset(mem, 0, sizeof(T) * size);
        //     return Acamarachi::Core::Slice((T *)mem, size);
        // }

        Result realloc(void *old_ptr, size_t size, void **ptr_out)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, 16, ptr_out);
        }

        Result reallocAlignment(void *old_ptr, size_t size, size_t alignment, void **ptr_out)
        {
            return vtable.realloc(typeErasedAllocator, old_ptr, size, alignment, ptr_out);
        }

        // template <typename T>
        // ResultOr<Slice<T>> reallocSlice(Slice<T> &oldSlice, size_t size, size_t alignment)
        // {
        //     auto maybe_memory = vtable.realloc(typeErasedAllocator, (void *)oldSlice.ptr, sizeof(T) * size, alignment);
        //     if (!maybe_memory)
        //     {
        //         return maybe_memory.error();
        //     }
        //     oldSlice = std::move(Slice<T>());
        //     return Slice<T>((T *)maybe_memory.result(), size);
        // }

        Result free(void *ptr)
        {
            return vtable.free(typeErasedAllocator, ptr);
        }

        // template <typename T>
        // void free(Slice<T> &slice)
        // {
        //     vtable.free(typeErasedAllocator, (void *)slice.ptr);
        //     slice = std::move(Slice<T>());
        // }
    };

    Interface getCAllocatorInterface();

    size_t getCAllocatorTotalBytesUsage();
    size_t getCAllocatorCurrentBytesUsage();
    size_t getCAllocatorAllocationCount();
    size_t getCAllocatorFreeCount();
}