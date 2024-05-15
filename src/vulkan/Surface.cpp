#include "Surface.hpp"
#include <iostream>

namespace Acamarachi::Vulkan
{
    Result Surface::initialize(Instance &instance, void *window, CreateWindowSurfaceFunction *fnc)
    {
        const VkResult res = fnc(instance.handle, window, 0, &handle);
        switch (res)
        {
        case VK_SUCCESS:
            return Result::Success;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return Result::OutOfHostMemory;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return Result::OutOfDeviceMemory;
        default:
            return Result::Unexpected;
        }
    }

    void Surface::deinitialize(Instance& instance)
    {
        vkDestroySurfaceKHR(instance.handle, handle, 0);
        handle = VK_NULL_HANDLE;
    }
}

// Acamarachi::Vulkan::Surface::Error Acamarachi::Vulkan::Surface::initialize(Acamarachi::Vulkan::Instance& instance, void* window, CreateWindowSurfaceFunction* createWindowSurface)
// {
//     Surface surface;

//     const VkResult res = createWindowSurface(instance.handle, window, 0, &surface.handle);
//     if (res != VK_SUCCESS) {
//         return VkResultToVulkanError(res);
//     }
//     return surface;
// }

// void Acamarachi::Vulkan::Surface::deinitialize(Acamarachi::Vulkan::Instance& instance)
// {
//     vkDestroySurfaceKHR(instance.handle, handle, 0);
//     handle = VK_NULL_HANDLE;
// }
