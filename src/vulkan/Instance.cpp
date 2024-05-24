#include <iostream>
#include "Instance.hpp"

namespace Acamarachi::Vulkan
{
    bool debuggerEnabled(Core::Slice<const char *> &requiredExtensions)
    {
        for (size_t i = 0; i < requiredExtensions.len; i += 1)
        {
            if (strcmp(requiredExtensions[i], "VK_EXT_debug_utils") == 0) {
                return true;
            }
        }
        return false;
    }

    static VkBool32 debugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT *data, void *userdata)
    {
        (void)userdata;
        std::cout << "Validation layer(" << severity << " :: " << (int)type << "): " << data->pMessage << std::endl;
        return VK_FALSE;
    }

    Result Instance::initialize(const char *appName, Core::Slice<const char *> &requiredExtensions, Core::Slice<const char *> &requiredValidationLayers)
    {
        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pNext = 0;
        applicationInfo.pApplicationName = appName;
        applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        applicationInfo.pEngineName = "Acamarachi Engine";
        applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        applicationInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = 0;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledLayerCount = (uint32_t)requiredValidationLayers.len;
        instanceCreateInfo.ppEnabledLayerNames = requiredValidationLayers.ptr;
        instanceCreateInfo.enabledExtensionCount = (uint32_t)requiredExtensions.len;
        instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.ptr;

        VkResult result = vkCreateInstance(&instanceCreateInfo, 0, &handle);
        if (result != VK_SUCCESS) return fromVkResult<false>(result);

        if (debuggerEnabled(requiredExtensions))
        {
            // VK_EXT_debug_utils allow more debug information to the user
            // for more info see : https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VK_EXT_debug_utils.html

            PFN_vkCreateDebugUtilsMessengerEXT fn = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(handle, "vkCreateDebugUtilsMessengerEXT");
            VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
            debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                                   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            debugMessengerCreateInfo.pfnUserCallback = &debugMessengerCallback;

            fn(handle, &debugMessengerCreateInfo, 0, &debugMessenger);
        }
        return Result::Success;
    }

    void Instance::deinitialize()
    {
        if (debugMessenger != VK_NULL_HANDLE)
        {
            PFN_vkDestroyDebugUtilsMessengerEXT fn = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(handle, "vkDestroyDebugUtilsMessengerEXT");
            fn(handle, debugMessenger, 0);
            debugMessenger = VK_NULL_HANDLE;
        }
        vkDestroyInstance(handle, nullptr);
        handle = VK_NULL_HANDLE;
    }

    Result Instance::getAvailablePhysicalDevice(Core::Allocator::Interface &allocator, Core::Slice<VkPhysicalDevice> &devices) const
    {
        uint32_t count = 0;
        VkResult res = vkEnumeratePhysicalDevices(handle, &count, VK_NULL_HANDLE);
        switch (res)
        {
        case VK_SUCCESS:
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return Result::OutOfHostMemory;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return Result::OutOfDeviceMemory;
        case VK_ERROR_INITIALIZATION_FAILED:
            return Result::InitializationFailed;
        default:
            return Result::Unexpected;
        };

        if (allocator.allocSlice((size_t)count, alignof(VkPhysicalDevice), devices) != Core::Allocator::Result::Success)
        {
            return Result::OutOfHostMemory;
        }

        (void)vkEnumeratePhysicalDevices(handle, &count, devices.ptr);

        return Result::Success;
    }
}
