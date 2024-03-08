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
    // (Void) suppress compilater warning
    (void)requiredExtensions;
    (void)requiredValidationLayers;
    std::vector<VkPhysicalDevice> physicalDevices;
    
    // Ask the instance for available physical devices
    if (!instance.getAvailablePhysicalDevices(physicalDevices)) {
        return false;
    }

    // Loop over all the possible devices and take the first that satify the condition.
    for (VkPhysicalDevice device : physicalDevices)
    {
        if (isPhysicalDeviceSuitable(device))
        {
            physicalDevice = device;
            break;
        }
    }

    return true;
}

void Acamarachi::Vulkan::Device::deinitialize()
{

}

bool Acamarachi::Vulkan::Device::isPhysicalDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}
