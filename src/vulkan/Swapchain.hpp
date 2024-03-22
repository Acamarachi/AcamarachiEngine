#ifndef ACAMARACHI_VULKAN_SWAPCHAIN
#define ACAMARACHI_VULKAN_SWAPCHAIN 1

#include <vulkan/vulkan.h>
#include <vector>

#include "Error.hpp"
#include "Device.hpp"
#include "Surface.hpp"

namespace Acamarachi::Vulkan
{

    class Swapchain {
    public:
        using Error = Core::Expected<Swapchain, VulkanError>;

        VkSwapchainKHR handle = VK_NULL_HANDLE;
        VkSurfaceFormatKHR surfaceFormat;
        VkPresentModeKHR presentMode;
        VkExtent2D extent;
        std::vector<VkImage> images;
        std::vector<VkImageView> imageViews;

        Swapchain() = default;
        Swapchain(const Swapchain&) = default;

        ~Swapchain() = default;

        static Error initialize(Device& device, Surface& surface, uint32_t width, uint32_t height);
        void deinitialize(Device& device);

    private:
        VkResult findSurfaceFormat(Device& device, Surface& surface, VkSurfaceFormatKHR* requested);
        VkResult findPresentMode(Device& device, Surface& surface, VkPresentModeKHR* requested);
        void findExtent(Device& device);
        uint32_t findImageCount(Device& device);
    };

}

#endif
