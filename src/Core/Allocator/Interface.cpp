#include <stdlib.h>
#include "Interface.hpp"

namespace Acamarachi::Core::Allocator
{
    size_t align(size_t x, size_t alignment)
    {
        return (x + alignment - 1) & ~(alignment - 1);
    }

    struct CAllocatorInfo
    {
        size_t total_bytes_used;
        size_t bytes_used;
        size_t n_allocation;
        size_t n_free;
    };

    static CAllocatorInfo infos = {};

    static ErrorOr<void *> interface_malloc(void *allocator, size_t size, size_t alignment)
    {
        (void)allocator;
        (void)alignment;
        void *ptr = malloc(size);
        if (!ptr)
        {
            return ErrorCode::OutOfMemory;
        }
        else
        {
            infos.total_bytes_used += size;
            infos.bytes_used += size;
            infos.n_allocation += 1;
            return ptr;
        }
    }

    static ErrorOr<void *> interface_realloc(void *allocator, void *oldPtr, size_t size, size_t alignment)
    {
        (void)allocator;
        (void)alignment;
        void *ptr = realloc(oldPtr, size);
        if (!ptr)
        {
            return ErrorCode::OutOfMemory;
        }
        else
        {
            infos.total_bytes_used += size;
            infos.n_allocation += 1;
            infos.n_free += 1;
            return ptr;
        }
    }

    static void interface_free(void *allocator, void *ptr)
    {
        (void)allocator;
        infos.n_free += 1;
        free(ptr);
    }

    Interface getCAllocatorInterface()
    {
        return Interface(nullptr, interface_malloc, interface_realloc, interface_free);
    }

    size_t getCAllocatorTotalBytesUsage()
    {
        return infos.total_bytes_used;
    }

    size_t getCAllocatorCurrentBytesUsage()
    {
        return infos.bytes_used;
    }

    size_t getCAllocatorAllocationCount()
    {
        return infos.n_allocation;
    }

    size_t getCAllocatorFreeCount()
    {
        return infos.n_free;
    }

}
