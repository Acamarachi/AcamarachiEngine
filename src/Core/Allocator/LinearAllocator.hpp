#pragma once

#include "Interface.hpp"

namespace Acamarachi::Core {

    class LinearAllocator {
    public:
        using Error = Acamarachi::Core::Expected<LinearAllocator, AllocatorErrorValue>;

        LinearAllocator(AllocatorInterface& parent) : parent(parent) {}
        ~LinearAllocator() = default;

        static Error initialize(AllocatorInterface& parent, size_t capacity);
        void deinitialize();

        AllocatorInterface getInterface();

    private:
        static AllocatorError internal_alloc(LinearAllocator *, size_t, size_t);
        static AllocatorError internal_realloc(LinearAllocator *, void*, size_t, size_t);
        static void internal_free(LinearAllocator *, void *);

        AllocatorInterface& parent;
        void *memory = nullptr;
        size_t size;
        size_t offset;
    };

}