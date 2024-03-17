#include <iostream>
#include "Device.hpp"

bool Acamarachi::Vulkan::Device::initialize(Acamarachi::Vulkan::Instance &instance, Acamarachi::Vulkan::Surface &surface, std::vector<const char *> requiredExtensions, std::vector<char const *> requiredValidationLayers)
{
    std::vector<VkPhysicalDevice> physicalDevices;

    // Ask the instance for available physical devices
    if (!instance.getAvailablePhysicalDevices(physicalDevices))
    {
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

    if (physicalDevice == VK_NULL_HANDLE)
    {
        return false;
    }

    if (!updateSurfaceCapabilities(surface))
    {
        std::cerr << "Failed to query physical device surface capabilities" << std::endl;
        return false;
    }

    if (!findQueueFamilies(surface))
    {
        std::cerr << "Failed to query physical device queues " << graphicQueue.familyIndex << ", " << presentQueue.familyIndex << ", " << transferQueue.familyIndex << ", " << std::endl;
        return false;
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
    deviceCreateInfo.enabledExtensionCount = requiredExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
    deviceCreateInfo.enabledLayerCount = requiredValidationLayers.size();
    deviceCreateInfo.ppEnabledLayerNames = requiredValidationLayers.data();
    deviceCreateInfo.queueCreateInfoCount = 3;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = &features;

    VkResult res = vkCreateDevice(physicalDevice, &deviceCreateInfo, 0, &this->handle);
    if (res != VK_SUCCESS)
    {
        return false;
    }

    vkGetDeviceQueue(handle, graphicQueue.familyIndex, 0, &graphicQueue.handle);
    vkGetDeviceQueue(handle, presentQueue.familyIndex, 0, &presentQueue.handle);
    vkGetDeviceQueue(handle, transferQueue.familyIndex, 0, &transferQueue.handle);

    return true;
}

void Acamarachi::Vulkan::Device::deinitialize()
{
    vkDestroyDevice(handle, 0);
}

bool Acamarachi::Vulkan::Device::isPhysicalDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

bool Acamarachi::Vulkan::Device::updateSurfaceCapabilities(Acamarachi::Vulkan::Surface& surface)
{
    return vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface.handle, &surfaceCapabilites) == VK_SUCCESS;
}

bool Acamarachi::Vulkan::Device::findQueueFamilies(Acamarachi::Vulkan::Surface& surface)
{
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, 0);

    std::vector<VkQueueFamilyProperties> properties = std::vector<VkQueueFamilyProperties>(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.data());

    for (uint32_t i = 0; i < count; i++)
    {
        VkQueueFamilyProperties current = properties[i];
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

    return !(graphicQueue.familyIndex == std::numeric_limits<uint32_t>::max() || transferQueue.familyIndex == std::numeric_limits<uint32_t>::max() || presentQueue.familyIndex == std::numeric_limits<uint32_t>::max());
}