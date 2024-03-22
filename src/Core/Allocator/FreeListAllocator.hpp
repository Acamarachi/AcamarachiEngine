#pragma once

#include "Interface.hpp"

namespace Acamarachi::Core
{

    struct FreeListNode {
        FreeListNode *next = nullptr;
        size_t size = 0;
    };

    struct FreeListAllocatorHeader {
        size_t size = 0;
        size_t padding = 0;
    };

    class FreeListAllocator {
    public:
        using Error = Expected<FreeListAllocator, AllocatorErrorValue>;

        ~FreeListAllocator() = default;

        static Error initialize(AllocatorInterface& parent, size_t size);
        void deinitialize();

        AllocatorInterface getInterface();

    private:
        FreeListAllocator(AllocatorInterface& parent) : parent(parent) {}

        static const size_t AllocationHeaderSize = sizeof(FreeListAllocatorHeader);
        static const size_t FreeHeaderSize = sizeof(FreeListNode);

        static AllocatorError internal_alloc(FreeListAllocator *, size_t, size_t);
        static AllocatorError internal_realloc(FreeListAllocator *, void*, size_t, size_t);
        static void internal_free(FreeListAllocator *, void *);

        static size_t getAllocationSize(size_t size);

        AllocatorInterface& parent;
        void *memory;
        size_t size;
        FreeListNode *head = nullptr;
    };

}