#ifndef ACAMARACHI_VULKAN_DEVICE
#define ACAMARACHI_VULKAN_DEVICE 1

#include <vulkan/vulkan.h>
#include <vector>
#include <limits>

#include "Instance.hpp"
#include "Surface.hpp"

namespace Acamarachi::Vulkan
{

    struct Queue {
        uint32_t familyIndex = std::numeric_limits<uint32_t>::max();
        VkQueue handle = VK_NULL_HANDLE;
    };

    class Device
    {
    public:
        Instance& instance;
        Surface& surface;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice handle = VK_NULL_HANDLE;
        VkSurfaceCapabilitiesKHR surfaceCapabilites = {};

        Queue graphicQueue = {};
        Queue presentQueue = {};
        Queue transferQueue = {};

        // To create a device you need a working Vulkan instance, otherwise it will not work
        // as the devices a get through the instance
        Device(Instance& instance, Surface& surface);
        Device(const Device &) = delete;
        ~Device();

        // Initialize the device and ask the instance to find some physical devices
        // then it will update physicalDevice and handle
        bool initialize(std::vector<const char *> requiredExtensions, std::vector<char const *> requiredValidationLayers);
        void deinitialize();

        // Perform a check to see if the device is what we want
        bool isPhysicalDeviceSuitable(VkPhysicalDevice device);
        bool updateSurfaceCapabilities();

    private:
        bool findQueueFamilies();

        //TODO: ADD RATING FOR THE BEST PHYSICAL DEVICE
    };

}

#endif