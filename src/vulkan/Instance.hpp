#ifndef ACAMARACHI_VULKAN_INSTANCE
#define ACAMARACHI_VULKAN_INSTANCE 1

#include <vulkan/vulkan.h>
#include <vector>
#include "Error.hpp"

namespace Acamarachi::Vulkan
{
    class Instance
    {
    public:
        using Error = Core::Expected<Instance, VulkanError>;

        VkInstance handle = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

        Instance() = default;
        Instance(const Instance &) = default;
        ~Instance() = default;

        // Create a Vulkan Instance with the specified extensions and validation layers
        // It will also create a debug messenger for more information about Vulkan
        static Error initialize(const char *appName, std::vector<const char *> requiredExtensions, std::vector<const char *> requiredValidationLayers);
        void deinitialize();

        // Try to get the possible devices.
        //
        // It will count once the number of available physical devices then get them.
        bool getAvailablePhysicalDevices(std::vector<VkPhysicalDevice>&);
    };
}

#endif