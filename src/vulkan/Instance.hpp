#ifndef ACAMARACHI_VULKAN_INSTANCE
#define ACAMARACHI_VULKAN_INSTANCE 1

#include <vulkan/vulkan.h>
#include <vector>

namespace Acamarachi::Vulkan
{
    class Instance
    {

    public:
        VkInstance handle = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

        Instance();
        Instance(const Instance &) = delete;
        ~Instance();

        // Create a Vulkan Instance with the specified extensions and validation layers
        // It will also create a debug messenger store for more information about Vulkan
        bool initialize(const char *appName, std::vector<const char *> requiredExtensions, std::vector<const char *> requiredValidationLayers);
        void deinitialize();

        bool getAvailablePhysicalDevices(std::vector<VkPhysicalDevice>&);
    };
}

#endif