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
        Instance &instance;
        VkSurfaceKHR handle;

        Surface(Instance &instance);
        Surface(const Surface &) = delete;

        ~Surface();

        bool initialize(void* window, CreateWindowSurfaceFunction*);

        void deinitialize();
    };

}

#endif