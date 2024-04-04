#include <stdlib.h>
#include "Interface.hpp"

size_t Acamarachi::Core::align(size_t x, size_t alignment)
{
    return (x + alignment - 1) & ~(alignment - 1);
}

struct CAllocatorInfo {
    size_t total_bytes_used;
    size_t bytes_used;
    size_t n_allocation;
    size_t n_free;
};

static CAllocatorInfo infos = {};

static Acamarachi::Core::AllocatorError interface_malloc(void *allocator, size_t size, size_t alignment)
{
    (void)allocator;
    (void)alignment;
    void *ptr = malloc(size);
    if (!ptr) {
        return Acamarachi::Core::AllocatorErrorValue::OutOfMemory;
    } else {
        infos.total_bytes_used += size;
        infos.bytes_used += size;
        infos.n_allocation += 1;
        return ptr;
    }
}

static Acamarachi::Core::AllocatorError interface_realloc(void *allocator, void *oldPtr, size_t size, size_t alignment)
{
    (void)allocator;
    (void)alignment;
    void *ptr = realloc(oldPtr, size);
    if (!ptr) {
        return Acamarachi::Core::AllocatorErrorValue::OutOfMemory;
    } else {
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

Acamarachi::Core::AllocatorInterface Acamarachi::Core::AllocatorInterface::getCAllocatorInterface()
{
    return Acamarachi::Core::AllocatorInterface(nullptr, interface_malloc, interface_realloc, interface_free);
}

size_t Acamarachi::Core::AllocatorInterface::getCAllocatorTotalBytesUsage()
{
    return infos.total_bytes_used;
}

size_t Acamarachi::Core::AllocatorInterface::getCAllocatorCurrentBytesUsage()
{
    return infos.bytes_used;
}

size_t Acamarachi::Core::AllocatorInterface::getCAllocatorAllocationCount()
{
    return infos.n_allocation;
}

size_t Acamarachi::Core::AllocatorInterface::getCAllocatorFreeCount()
{
    return infos.n_free;
}
