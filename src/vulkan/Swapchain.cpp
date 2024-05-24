#include <iostream>
#include <vulkan/vk_enum_string_helper.h>
#include <limits>
#include <algorithm>
#include "Swapchain.hpp"

namespace Acamarachi::Vulkan
{
    Result Swapchain::initialize(Core::Allocator::Interface& allocator, Device &device, Surface &surface, uint32_t width, uint32_t height)
    {
        VkResult res = VK_SUCCESS;
        this->extent.width = width;
        this->extent.height = height;

        this->surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
        this->surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        res = findSurfaceFormat(device, surface, &this->surfaceFormat);
        if (res != VK_SUCCESS)
        {
            return Result::NoSuitableSurfaceFormat;
        }

        this->presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        res = findPresentMode(device, surface, &this->presentMode);
        if (res != VK_SUCCESS)
        {
            return Result::NoSuitablePresentMode;
        }

        std::cout << "Extent " << this->extent.width << " " << extent.height << "\n";
        findExtent(device);
        std::cout << "Extent " << this->extent.width << " " << extent.height << "\n";
        uint32_t imageCount = findImageCount(device);

        uint32_t queueFamilies[2] = {device.graphicQueue.familyIndex, device.presentQueue.familyIndex};
        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = surface.handle;
        swapchainCreateInfo.imageColorSpace = this->surfaceFormat.colorSpace;
        swapchainCreateInfo.imageFormat = this->surfaceFormat.format;
        swapchainCreateInfo.imageExtent = this->extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.minImageCount = imageCount;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        swapchainCreateInfo.presentMode = this->presentMode;
        swapchainCreateInfo.queueFamilyIndexCount = 2;
        swapchainCreateInfo.pQueueFamilyIndices = queueFamilies;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchainCreateInfo.preTransform = device.surfaceCapabilites.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
        res = vkCreateSwapchainKHR(device.handle, &swapchainCreateInfo, 0, &this->handle);
        if (res != VK_SUCCESS)
            return fromVkResult<false>(res);

        uint32_t actualImageCount = 0;
        res = vkGetSwapchainImagesKHR(device.handle, this->handle, &actualImageCount, 0);
        if (res != VK_SUCCESS)
            return fromVkResult<false>(res);

        if (allocator.allocSlice((size_t)actualImageCount, alignof(VkImage), this->images) != Core::Allocator::Result::Success)
        {
            return Result::OutOfHostMemory;
        }
        if (allocator.allocSlice((size_t)actualImageCount, alignof(VkImageView), this->imageViews) != Core::Allocator::Result::Success)
        {
            return Result::OutOfHostMemory;
        }
        res = vkGetSwapchainImagesKHR(device.handle, this->handle, &actualImageCount, this->images.ptr);
        if (res != VK_SUCCESS)
            return fromVkResult<false>(res);

        VkImageViewCreateInfo imageViewCreateInfo = {};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = this->surfaceFormat.format;
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
            imageViewCreateInfo.image = this->images[i];
            res = vkCreateImageView(device.handle, &imageViewCreateInfo, 0, &this->imageViews[i]);
            if (res != VK_SUCCESS)
                return fromVkResult<false>(res);
        }

        return Result::Success;
    }

    void Swapchain::deinitialize(Core::Allocator::Interface& allocator, Device &device)
    {
        for (size_t i = 0; i < this->imageViews.len; i += 1)
        {
            vkDestroyImageView(device.handle, this->imageViews[i], nullptr);
        }
        vkDestroySwapchainKHR(device.handle, this->handle, nullptr);
        allocator.free(this->images);
        allocator.free(this->imageViews);
    }

    VkResult Swapchain::findSurfaceFormat(Device &device, Surface &surface, VkSurfaceFormatKHR *requested)
    {
        VkResult res = VK_SUCCESS;
        uint32_t count = 0;
        res = vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, 0);
        if (res != VK_SUCCESS)
            return res;

        std::vector<VkSurfaceFormatKHR> formats = std::vector<VkSurfaceFormatKHR>(count);
        res = vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice, surface.handle, &count, formats.data());
        if (res != VK_SUCCESS)
            return res;

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

    VkResult Swapchain::findPresentMode(Device &device, Surface &surface, VkPresentModeKHR *requested)
    {
        VkResult res = VK_SUCCESS;
        uint32_t count = 0;
        res = vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, 0);
        if (res != VK_SUCCESS)
            return res;

        std::vector<VkPresentModeKHR> modes = std::vector<VkPresentModeKHR>(count);
        res = vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalDevice, surface.handle, &count, modes.data());
        if (res != VK_SUCCESS)
            return res;

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

    void Swapchain::findExtent(Device &device)
    {
        std::cout << "Width: " << device.surfaceCapabilites.currentExtent.width << "\n";
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

    uint32_t Swapchain::findImageCount(Device &device)
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

}
