#ifndef ACAMARACHI_VULKAN_DEVICE
#define ACAMARACHI_VULKAN_DEVICE 1

#include <vulkan/vulkan.h>
#include <vector>
#include "Instance.hpp"

namespace Acamarachi::Vulkan
{

    class Device
    {
    public:
        Instance& instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice handle = VK_NULL_HANDLE;

        // To create a device you need a working Vulkan instance, otherwise it will not work
        // as the devices a get through the instance
        Device(Instance& instance);
        Device(const Device &) = delete;
        ~Device();

        // Initialize de devices, if the instance find some physical devices
        // then it will update physicalDevice and handle
        bool initialize(std::vector<const char *> requiredExtensions, std::vector<char const *> requiredValidationLayers);
        void deinitialize();
    };

}

#endif