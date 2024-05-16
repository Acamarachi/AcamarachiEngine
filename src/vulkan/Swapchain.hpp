#pragma once

#include <vulkan/vulkan.h>

#include "Device.hpp"
#include "Surface.hpp"

namespace Acamarachi::Vulkan
{

    class Swapchain {
    public:
        VkSwapchainKHR handle = VK_NULL_HANDLE;
        VkSurfaceFormatKHR surfaceFormat;
        VkPresentModeKHR presentMode;
        VkExtent2D extent;

        Core::Slice<VkImage> images;
        Core::Slice<VkImageView> imageViews;

        Swapchain() = default;
        Swapchain(const Swapchain&) = default;
        ~Swapchain() = default;

        Result initialize(Core::Allocator::Interface& allocator, Device& device, Surface& surface, uint32_t width, uint32_t height);
        void deinitialize(Core::Allocator::Interface& allocator, Device& device);

    private:
        VkResult findSurfaceFormat(Device& device, Surface& surface, VkSurfaceFormatKHR* requested);
        VkResult findPresentMode(Device& device, Surface& surface, VkPresentModeKHR* requested);
        void findExtent(Device& device);
        uint32_t findImageCount(Device& device);
    };

}
