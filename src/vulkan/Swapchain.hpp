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
        Device& device;
        Surface& surface;

        VkSwapchainKHR handle = VK_NULL_HANDLE;
        VkSurfaceFormatKHR surfaceFormat;
        VkPresentModeKHR presentMode;
        VkExtent2D extent;
        std::vector<VkImage> images;
        std::vector<VkImageView> imageViews;

        Swapchain(Device&);
        Swapchain(const Swapchain&) = delete;

        ~Swapchain();

        bool initialize(uint32_t width, uint32_t height);
        void deinitialize();

    private:
        bool findSurfaceFormat(VkSurfaceFormatKHR* requested);
        bool findPresentMode(VkPresentModeKHR* requested);
        void findExtent();
        uint32_t findImageCount();
    };

}

#endif
