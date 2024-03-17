#include "Surface.hpp"
#include <iostream>

bool Acamarachi::Vulkan::Surface::initialize(Acamarachi::Vulkan::Instance& instance, void* window, CreateWindowSurfaceFunction* createWindowSurface)
{
    std::cout << "Creating surface" << std::endl;
    return createWindowSurface(instance.handle, window, 0, &this->handle) == VK_SUCCESS;
}

void Acamarachi::Vulkan::Surface::deinitialize(Acamarachi::Vulkan::Instance& instance)
{
    vkDestroySurfaceKHR(instance.handle, this->handle, 0);
}