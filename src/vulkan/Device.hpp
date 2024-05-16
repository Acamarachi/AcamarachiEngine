#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <limits>

#include "../Core/Slice.hpp"
#include "../Core/Allocator/Interface.hpp"
#include "Result.hpp"
#include "Instance.hpp"
#include "Surface.hpp"

namespace Acamarachi::Vulkan
{
    struct Queue
    {
        uint32_t familyIndex = std::numeric_limits<uint32_t>::max();
        VkQueue handle = VK_NULL_HANDLE;
    };

    struct DeviceInitializationInfo
    {
        DeviceInitializationInfo(Instance &instance,
        Surface &surface,
        Core::Slice<const char *>& requiredExtensions,
        Core::Slice<const char *>& requiredValidationLayers,
        Core::Slice<VkPhysicalDevice>& physicalDevices)
            : instance(instance), 
              surface(surface),
              requiredExtensions(requiredExtensions), 
              requiredValidationLayers(requiredValidationLayers), 
              physicalDevices(physicalDevices) {}

        Instance &instance;
        Surface &surface;
        Core::Slice<const char *>& requiredExtensions;
        Core::Slice<const char *>& requiredValidationLayers;
        Core::Slice<VkPhysicalDevice>& physicalDevices;
    };

    class Device
    {
    public:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice handle = VK_NULL_HANDLE;
        VkSurfaceCapabilitiesKHR surfaceCapabilites = {};

        Queue graphicQueue = {};
        Queue presentQueue = {};
        Queue transferQueue = {};

        VkPhysicalDeviceMemoryProperties memoryProperties;

        Device() = default;
        Device(const Device &) = delete;
        ~Device() = default;

        Result initialize(Core::Allocator::Interface &allocator, DeviceInitializationInfo info);
        void deinitialize();

    private:
        Result isPhysicalDeviceSuitable(VkPhysicalDevice);
        Result findQueueFamilies(Core::Allocator::Interface &allocator, Surface &surface);
    };
}