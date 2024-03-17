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

        VkFence renderFence;
        VkSemaphore swapchainSemaphore;
        VkSemaphore renderSemaphore;
    } FrameManagementData;

    class FrameInformation
    {
    public:
        Device &device;
        Swapchain& swapchain;
        FrameManagementData frameData[FRAME_BUFFERING];
        std::size_t currentFrame = 0;

        FrameInformation(Device &device, Swapchain& swapchain);
        FrameInformation(const FrameInformation &) = delete;

        ~FrameInformation();

        bool initialize();
        void deinitialize();

        FrameManagementData getCurrentFrameData();

        bool draw();
    };

}

#endif