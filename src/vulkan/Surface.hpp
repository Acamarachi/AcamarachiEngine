#ifndef ACAMARACHI_VULKAN_SURFACE
#define ACAMARACHI_VULKAN_SURFACE 1

#include <vulkan/vulkan.h>
#include <vector>

#include "Instance.hpp"

namespace Acamarachi::Vulkan
{

    using CreateWindowSurfaceFunction = VkResult (VkInstance instance, void* window, const VkAllocationCallbacks* callbacks, VkSurfaceKHR *surface);

    class Surface
    {
    public:
        VkSurfaceKHR handle;

        Surface() = default;
        Surface(const Surface &) = delete;

        ~Surface() = default;

        bool initialize(Instance &instance, void* window, CreateWindowSurfaceFunction*);

        void deinitialize(Acamarachi::Vulkan::Instance& instance);
    };

}

#endif