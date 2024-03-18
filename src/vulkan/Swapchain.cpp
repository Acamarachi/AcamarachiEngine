#include <iostream>
#include <vulkan/vk_enum_string_helper.h>
#include <limits>
#include <algorithm>
#include "Swapchain.hpp"

bool Acamarachi::Vulkan::Swapchain::initialize(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, uint32_t width, uint32_t height)
{
    extent.width = width;
    extent.height = height;

    surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
    surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    if (!findSurfaceFormat(device, surface, &surfaceFormat))
    {
        return false;
    }

    presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    if (!findPresentMode(device, surface, &presentMode))
    {
        return false;
    }

    findExtent(device);
    uint32_t imageCount = findImageCount(device);

    uint32_t queueFamilies[2] = {device.graphicQueue.familyIndex, device.presentQueue.familyIndex};
    VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = surface.handle;
    swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapchainCreateInfo.imageFormat = surfaceFormat.format;
    swapchainCreateInfo.imageExtent = extent;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.minImageCount = imageCount;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    swapchainCreateInfo.presentMode = presentMode;
    swapchainCreateInfo.queueFamilyIndexCount = 2;
    swapchainCreateInfo.pQueueFamilyIndices = queueFamilies;
    swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchainCreateInfo.preTransform = device.surfaceCapabilites.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = handle;

    if (vkCreateSwapchainKHR(device.handle, &swapchainCreateInfo, 0, &handle) != VK_SUCCESS)
    {
        return false;
    }

    uint32_t actualImageCount = 0;
    if (vkGetSwapchainImagesKHR(device.handle, handle, &actualImageCount, 0) != VK_SUCCESS)
    {
        return false;
    }

    images.resize(actualImageCount);
    imageViews.resize(actualImageCount);
    if (vkGetSwapchainImagesKHR(device.handle, handle, &actualImageCount, images.data()) != VK_SUCCESS)
    {
        return false;
    }

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = surfaceFormat.format;
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
        imageViewCreateInfo.image = images[i];
        if (vkCreateImageView(device.handle, &imageViewCreateInfo, 0, &imageViews[i]) != VK_SUCCESS) {
            return false;
        }
    }

    return true;
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

bool Acamarachi::Vulkan::Swapchain::findSurfaceFormat(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, VkSurfaceFormatKHR *requested)
{
    uint32_t count = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, 0) != VK_SUCCESS)
    {
        return false;
    }

    std::vector<VkSurfaceFormatKHR> formats = std::vector<VkSurfaceFormatKHR>(count);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, formats.data()) != VK_SUCCESS)
    {
        return false;
    }

    for (std::size_t i = 0; i < formats.size(); i++)
    {
        VkSurfaceFormatKHR available = formats[i];
        if (available.format == (*requested).format && available.colorSpace == (*requested).colorSpace)
        {
            return true;
        }
    }
    *requested = formats[0];
    return true;
}

bool Acamarachi::Vulkan::Swapchain::findPresentMode(Acamarachi::Vulkan::Device& device, Acamarachi::Vulkan::Surface& surface, VkPresentModeKHR *requested)
{
    uint32_t count = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, 0) != VK_SUCCESS)
    {
        return false;
    }

    std::vector<VkPresentModeKHR> modes = std::vector<VkPresentModeKHR>(count);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, modes.data()) != VK_SUCCESS)
    {
        return false;
    }

    for (std::size_t i = 0; i < count; i++)
    {
        if (modes[i] == *requested)
        {
            return true;
        }
    }
    std::cout << "Trying to get present mode " << string_VkPresentModeKHR(*requested) << ", couldn't find it so falling back to VK_PRESENT_MODE_FIFO_KHR" << std::endl;
    *requested = VK_PRESENT_MODE_FIFO_KHR;
    return false;
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
