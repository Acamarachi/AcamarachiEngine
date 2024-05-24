#ifndef ACAMARACHI_VULKAN_FRAME_INFORMATION
#define ACAMARACHI_VULKAN_FRAME_INFORMATION 1

#include <vulkan/vulkan.h>
#include <vector>

#include "Result.hpp"
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
        VkSemaphore swapchainSemaphore = VK_NULL_HANDLE;
        VkSemaphore renderSemaphore = VK_NULL_HANDLE;
    } FrameManagementData;

    class FrameInformation
    {
    public:

        FrameManagementData frameData[FRAME_BUFFERING];
        std::size_t currentFrameIndex = 0;

        FrameInformation() = default;
        FrameInformation(const FrameInformation &) = default;
        ~FrameInformation() = default;

        Result initialize(Device& device);
        void deinitialize(Device &device);

        FrameManagementData getCurrentFrameData();

        Result draw(Device &device, Swapchain& swapchain);
    };

}

#endif