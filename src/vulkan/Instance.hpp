#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "../Core/Slice.hpp"
#include "../Core/Allocator/Interface.hpp"
#include "Result.hpp"

namespace Acamarachi::Vulkan
{
    class Instance
    {
    public:
        VkInstance handle = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

        Instance() = default;
        Instance(const Instance &) = delete;
        ~Instance() = default;

        Result initialize(const char* appName, Core::Slice<const char *>& requiredExtensions, Core::Slice<const char *>& requiredValidationLayers);
        void deinitialize();

        Result getAvailablePhysicalDevice(Core::Allocator::Interface& allocator, Core::Slice<VkPhysicalDevice>& devices) const;
    };
}