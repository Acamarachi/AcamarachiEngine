#include "Surface.hpp"
#include <iostream>

Acamarachi::Vulkan::Surface::Error Acamarachi::Vulkan::Surface::initialize(Acamarachi::Vulkan::Instance& instance, void* window, CreateWindowSurfaceFunction* createWindowSurface)
{
    Surface surface;

    const VkResult res = createWindowSurface(instance.handle, window, 0, &surface.handle);
    if (res != VK_SUCCESS) {
        return VkResultToVulkanError(res);
    }
    return surface;
}

void Acamarachi::Vulkan::Surface::deinitialize(Acamarachi::Vulkan::Instance& instance)
{
    vkDestroySurfaceKHR(instance.handle, handle, 0);
    handle = VK_NULL_HANDLE;
}