#include "Device.hpp"

Acamarachi::Vulkan::Device::Device(Acamarachi::Vulkan::Instance &instance)
    : instance(instance)
{ }

Acamarachi::Vulkan::Device::~Device()
{
    this->deinitialize();
}

bool Acamarachi::Vulkan::Device::initialize(std::vector<const char *> requiredExtensions, std::vector<char const *> requiredValidationLayers)
{
    (void)requiredExtensions;
    (void)requiredValidationLayers;
    std::vector<VkPhysicalDevice> physicalDevices;
    
    if (!instance.getAvailablePhysicalDevices(physicalDevices)) {
        return false;
    }

    return true;
}

void Acamarachi::Vulkan::Device::deinitialize()
{

}