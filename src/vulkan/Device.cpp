#include "Device.hpp"

namespace Acamarachi::Vulkan
{
    Result Device::initialize(Core::Allocator::Interface &allocator, DeviceInitializationInfo info)
    {
        Result state = Result::Success;
        for (size_t i = 0; i < info.physicalDevices.len; i += 1)
        {
            if ((state = isPhysicalDeviceSuitable(info.physicalDevices[i])) == Result::Success)
            {
                physicalDevice = info.physicalDevices[i];
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            std::cout << "Failed to find suitable device\n";
            return Result::NotSuitableDevice;
        }

        if ((state = findQueueFamilies(allocator, info.surface)) != Result::Success)
        {
            std::cout << "Failed to find suitable queue families\n";
            return state;
        }

        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo queueCreateInfo[3] = {};
        queueCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo[0].queueCount = 1;
        queueCreateInfo[0].queueFamilyIndex = graphicQueue.familyIndex;
        queueCreateInfo[0].pQueuePriorities = &queuePriority;

        queueCreateInfo[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo[1].queueCount = 1;
        queueCreateInfo[1].queueFamilyIndex = presentQueue.familyIndex;
        queueCreateInfo[1].pQueuePriorities = &queuePriority;

        queueCreateInfo[2].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo[2].queueCount = 1;
        queueCreateInfo[2].queueFamilyIndex = transferQueue.familyIndex;
        queueCreateInfo[2].pQueuePriorities = &queuePriority;

        VkPhysicalDeviceVulkan12Features featureVk1_2 = {};
        featureVk1_2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
        featureVk1_2.bufferDeviceAddress = VK_TRUE;
        featureVk1_2.descriptorIndexing = VK_TRUE;

        VkPhysicalDeviceVulkan13Features featureVk1_3 = {};
        featureVk1_3.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
        featureVk1_3.pNext = &featureVk1_2;
        featureVk1_3.dynamicRendering = VK_TRUE;
        featureVk1_3.synchronization2 = VK_TRUE;

        VkPhysicalDeviceFeatures features = {};

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = &featureVk1_3;
        deviceCreateInfo.enabledExtensionCount = (uint32_t)info.requiredExtensions.len;
        deviceCreateInfo.ppEnabledExtensionNames = info.requiredExtensions.ptr;
        deviceCreateInfo.enabledLayerCount = (uint32_t)info.requiredValidationLayers.len;
        deviceCreateInfo.ppEnabledLayerNames = info.requiredValidationLayers.ptr;
        deviceCreateInfo.queueCreateInfoCount = 3;
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;
        deviceCreateInfo.pEnabledFeatures = &features;

        VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, 0, &handle);
        switch (result)
        {
        case VK_SUCCESS:
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return Result::OutOfHostMemory;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return Result::OutOfDeviceMemory;
        case VK_ERROR_INITIALIZATION_FAILED:
            return Result::InitializationFailed;
        case VK_ERROR_LAYER_NOT_PRESENT:
            return Result::MissingLayer;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return Result::MissingExtension;
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return Result::ImcompatibleDriver;
        default:
            return Result::Unexpected;
        }

        vkGetDeviceQueue(handle, graphicQueue.familyIndex, 0, &graphicQueue.handle);
        vkGetDeviceQueue(handle, presentQueue.familyIndex, 0, &presentQueue.handle);
        vkGetDeviceQueue(handle, transferQueue.familyIndex, 0, &transferQueue.handle);

        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, info.surface.handle, &surfaceCapabilites);

        return state;
    }

    void Device::deinitialize()
    {
        vkDestroyDevice(handle, 0);
        handle = VK_NULL_HANDLE;
    }

    Result Device::isPhysicalDeviceSuitable(VkPhysicalDevice pDevice)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;

        vkGetPhysicalDeviceProperties(pDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(pDevice, &deviceFeatures);

        return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) ? Result::Success : Result::NotSuitableDevice;
    }

    Result Device::findQueueFamilies(Core::Allocator::Interface &allocator, Surface &surface)
    {
        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, 0);

        Core::Slice<VkQueueFamilyProperties> properties = Core::Slice<VkQueueFamilyProperties>();
        if (allocator.allocSlice(count, alignof(VkQueueFamilyProperties), properties) != Core::Allocator::Result::Success)
        {
            return Result::OutOfHostMemory;
        }
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.ptr);

        for (size_t i = 0; i < properties.len; i += 1)
        {
            auto current = properties[i];
            VkBool32 supported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface.handle, &supported);
            if (graphicQueue.familyIndex == std::numeric_limits<uint32_t>::max() && current.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                graphicQueue.familyIndex = i;
            }
            else if (transferQueue.familyIndex == std::numeric_limits<uint32_t>::max() && current.queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                transferQueue.familyIndex = i;
            }
            else if (presentQueue.familyIndex == std::numeric_limits<uint32_t>::max() && supported)
            {
                presentQueue.familyIndex = i;
            }
        }
        allocator.free(properties);
        const bool valid = !(graphicQueue.familyIndex == std::numeric_limits<uint32_t>::max() ||
                             transferQueue.familyIndex == std::numeric_limits<uint32_t>::max() ||
                             presentQueue.familyIndex == std::numeric_limits<uint32_t>::max());
        return valid ? Result::Success : Result::QueueQueryFailed;
    }
};