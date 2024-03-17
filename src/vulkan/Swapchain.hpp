#ifndef ACAMARACHI_VULKAN_SWAPCHAIN
#define ACAMARACHI_VULKAN_SWAPCHAIN 1

#include <vulkan/vulkan.h>
#include <vector>

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
        std::vector<VkImage> images;
        std::vector<VkImageView> imageViews;

        Swapchain() = default;
        Swapchain(const Swapchain&) = delete;

        ~Swapchain() = default;

        bool initialize(Device& device, Surface& surface, uint32_t width, uint32_t height);
        void deinitialize(Device& device);

    private:
        bool findSurfaceFormat(Device& device, Surface& surface, VkSurfaceFormatKHR* requested);
        bool findPresentMode(Device& device, Surface& surface, VkPresentModeKHR* requested);
        void findExtent(Device& device);
        uint32_t findImageCount(Device& device);
    };

}

#endif
