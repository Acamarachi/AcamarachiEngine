#include <stdlib.h>
#include "Interface.hpp"

size_t Acamarachi::Core::align(size_t x, size_t alignment)
{
    return (x + alignment - 1) & ~(alignment - 1);
}

static Acamarachi::Core::AllocatorError interface_malloc(void *allocator, size_t size, size_t alignment)
{
    (void)allocator;
    (void)alignment;
    void *ptr = malloc(size);
    if (!ptr) {
        return Acamarachi::Core::AllocatorErrorValue::OutOfMemory;
    } else {
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
        return ptr;
    }
}

static void interface_free(void *allocator, void *ptr)
{
    (void)allocator;
    free(ptr);
}

Acamarachi::Core::AllocatorInterface Acamarachi::Core::AllocatorInterface::getCAllocatorInterface()
{
    return Acamarachi::Core::AllocatorInterface(nullptr, interface_malloc, interface_realloc, interface_free);
}
