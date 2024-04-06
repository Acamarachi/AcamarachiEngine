#ifndef ACAMARACHI_VULKAN_FRAME_INFORMATION
#define ACAMARACHI_VULKAN_FRAME_INFORMATION 1

#include <vulkan/vulkan.h>
#include <vector>

#include "Device.hpp"
#include "Swapchain.hpp"

namespace Acamarachi::Vulkan
{
    constexpr std::size_t FRAME_BUFFERING = 2;

    typedef struct FrameManagementData
    {
        VkCommandPool commandPool = VK_NULL_HANDLE;
        VkCommandBuffer primaryCommandBuffer = VK_NULL_HANDLE;

        VkFence renderFence = VK_NULL_HANDLE;
        VkSemaphore swapchainSemaphore;
        VkSemaphore renderSemaphore;
    } FrameManagementData;

    class FrameInformation
    {
    public:
        using Error = Core::Expected<FrameInformation, VulkanError>;

        FrameManagementData frameData[FRAME_BUFFERING];
        std::size_t currentFrameIndex = 0;

        FrameInformation() = default;
        FrameInformation(const FrameInformation &) = default;
        ~FrameInformation() = default;

        static Error initialize(Device &device);
        void deinitialize(Device &device);

        FrameManagementData getCurrentFrameData();

        bool draw(Device &device, Swapchain& swapchain);
    };

}

#endif