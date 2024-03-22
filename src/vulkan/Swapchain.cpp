#include <iostream>
#include <vulkan/vk_enum_string_helper.h>
#include <limits>
#include <algorithm>
#include "Swapchain.hpp"

Acamarachi::Vulkan::Swapchain::Error Acamarachi::Vulkan::Swapchain::initialize(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, uint32_t width, uint32_t height)
{
    VkResult res = VK_SUCCESS;
    Swapchain swapchain;
    swapchain.extent.width = width;
    swapchain.extent.height = height;

    swapchain.surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
    swapchain.surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    res = swapchain.findSurfaceFormat(device, surface, &swapchain.surfaceFormat);
    if (res != VK_SUCCESS) return VkResultToVulkanError(res);

    swapchain.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    res = swapchain.findPresentMode(device, surface, &swapchain.presentMode);
    if (res != VK_SUCCESS) return VkResultToVulkanError(res);

    swapchain.findExtent(device);
    uint32_t imageCount = swapchain.findImageCount(device);

    uint32_t queueFamilies[2] = {device.graphicQueue.familyIndex, device.presentQueue.familyIndex};
    VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = surface.handle;
    swapchainCreateInfo.imageColorSpace = swapchain.surfaceFormat.colorSpace;
    swapchainCreateInfo.imageFormat = swapchain.surfaceFormat.format;
    swapchainCreateInfo.imageExtent = swapchain.extent;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.minImageCount = imageCount;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    swapchainCreateInfo.presentMode = swapchain.presentMode;
    swapchainCreateInfo.queueFamilyIndexCount = 2;
    swapchainCreateInfo.pQueueFamilyIndices = queueFamilies;
    swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchainCreateInfo.preTransform = device.surfaceCapabilites.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = swapchain.handle;

    res = vkCreateSwapchainKHR(device.handle, &swapchainCreateInfo, 0, &swapchain.handle);
    if (res != VK_SUCCESS) return VkResultToVulkanError(res);

    uint32_t actualImageCount = 0;
    res = vkGetSwapchainImagesKHR(device.handle, swapchain.handle, &actualImageCount, 0) ;
    if (res != VK_SUCCESS) return VkResultToVulkanError(res);

    swapchain.images.resize(actualImageCount);
    swapchain.imageViews.resize(actualImageCount);
    res = vkGetSwapchainImagesKHR(device.handle, swapchain.handle, &actualImageCount, swapchain.images.data());
    if (res != VK_SUCCESS) return VkResultToVulkanError(res);

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = swapchain.surfaceFormat.format;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;
    for (uint32_t i = 0; i < actualImageCount; i++)
    {
        imageViewCreateInfo.image = swapchain.images[i];
        res = vkCreateImageView(device.handle, &imageViewCreateInfo, 0, &swapchain.imageViews[i]);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);
    }

    return swapchain;
}

void Acamarachi::Vulkan::Swapchain::deinitialize(Acamarachi::Vulkan::Device& device)
{
    for (std::size_t i = 0; i < imageViews.size(); i++)
    {
        vkDestroyImageView(device.handle, imageViews[i], 0);
    }
    vkDestroySwapchainKHR(device.handle, handle, 0);
    handle = VK_NULL_HANDLE;
}

VkResult Acamarachi::Vulkan::Swapchain::findSurfaceFormat(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, VkSurfaceFormatKHR *requested)
{
    VkResult res = VK_SUCCESS;
    uint32_t count = 0;
    res = vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, 0);
    if (res != VK_SUCCESS) return res;

    std::vector<VkSurfaceFormatKHR> formats = std::vector<VkSurfaceFormatKHR>(count);
    res = vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, formats.data());
    if (res != VK_SUCCESS) return res;


    for (std::size_t i = 0; i < formats.size(); i++)
    {
        VkSurfaceFormatKHR available = formats[i];
        if (available.format == (*requested).format && available.colorSpace == (*requested).colorSpace)
        {
            return VK_SUCCESS;
        }
    }
    *requested = formats[0];
    return VK_SUCCESS;
}

VkResult Acamarachi::Vulkan::Swapchain::findPresentMode(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, VkPresentModeKHR *requested)
{
    VkResult res = VK_SUCCESS;
    uint32_t count = 0;
    res = vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, 0);
    if (res != VK_SUCCESS) return res;

    std::vector<VkPresentModeKHR> modes = std::vector<VkPresentModeKHR>(count);
    res = vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, modes.data());
    if (res != VK_SUCCESS) return res;

    for (std::size_t i = 0; i < count; i++)
    {
        if (modes[i] == *requested)
        {
            return VK_SUCCESS;
        }
    }
    std::cout << "Trying to get present mode " << string_VkPresentModeKHR(*requested) << ", couldn't find it so falling back to VK_PRESENT_MODE_FIFO_KHR" << std::endl;
    *requested = VK_PRESENT_MODE_FIFO_KHR;
    return VK_SUCCESS;
}

void Acamarachi::Vulkan::Swapchain::findExtent(Acamarachi::Vulkan::Device& device)
{
    if (device.surfaceCapabilites.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        extent = device.surfaceCapabilites.currentExtent;
    }
    else
    {
        extent.width = std::clamp(extent.width, device.surfaceCapabilites.minImageExtent.width, device.surfaceCapabilites.maxImageExtent.width);
        extent.height = std::clamp(extent.height, device.surfaceCapabilites.minImageExtent.height, device.surfaceCapabilites.maxImageExtent.height);
    }
}

uint32_t Acamarachi::Vulkan::Swapchain::findImageCount(Acamarachi::Vulkan::Device& device)
{
    uint32_t minImageCount = device.surfaceCapabilites.minImageCount + 1;
    if (device.surfaceCapabilites.maxImageCount > 0)
    {
        return std::min(minImageCount, device.surfaceCapabilites.maxImageCount);
    }
    else
    {
        return minImageCount;
    }
}
