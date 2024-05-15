#pragma once

#include <vulkan/vulkan.h>

#include "Instance.hpp"
#include "Result.hpp"

namespace Acamarachi::Vulkan
{

    using CreateWindowSurfaceFunction = VkResult (VkInstance instance, void* window, const VkAllocationCallbacks* callbacks, VkSurfaceKHR *surface);

    class Surface
    {
    public:

        VkSurfaceKHR handle = VK_NULL_HANDLE;

        Surface() = default;
        Surface(const Surface &) = delete;
        ~Surface() = default;

        Result initialize(Instance &instance, void *window, CreateWindowSurfaceFunction *fnc);
        void deinitialize(Instance& instance);
    };

}
