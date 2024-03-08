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

        Device(Instance& instance);
        Device(const Device &) = delete;
        ~Device();

        bool initialize(std::vector<const char *> requiredExtensions, std::vector<char const *> requiredValidationLayers);
        void deinitialize();
    };

}

#endif