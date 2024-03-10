#include "Surface.hpp"
#include <iostream>

Acamarachi::Vulkan::Surface::Surface(Acamarachi::Vulkan::Instance& instance)
    : instance(instance)
{ }

Acamarachi::Vulkan::Surface::~Surface()
{
    deinitialize();
}

bool Acamarachi::Vulkan::Surface::initialize(void* window, CreateWindowSurfaceFunction* createWindowSurface)
{
    std::cout << "Creating surface" << std::endl;
    return createWindowSurface(this->instance.handle, window, 0, &this->handle) == VK_SUCCESS;
}

void Acamarachi::Vulkan::Surface::deinitialize()
{
    vkDestroySurfaceKHR(instance.handle, this->handle, 0);
}