#include "Utils.hpp"
#include "FrameInformation.hpp"

Acamarachi::Vulkan::FrameInformation::Error Acamarachi::Vulkan::FrameInformation::initialize(Acamarachi::Vulkan::Device &device)
{
    VkResult res = VK_SUCCESS;
    Acamarachi::Vulkan::FrameInformation frameInfo;

    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = device.graphicQueue.familyIndex;

	VkCommandBufferAllocateInfo cmdAllocInfo = {};
	cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdAllocInfo.pNext = nullptr;
	cmdAllocInfo.commandBufferCount = 1;
	cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    for (std::size_t i = 0; i < FRAME_BUFFERING; ++i) {
        res = vkCreateCommandPool(device.handle, &commandPoolCreateInfo, 0, &frameInfo.frameData[i].commandPool);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);
	    cmdAllocInfo.commandPool = frameInfo.frameData[i].commandPool;

        res = vkAllocateCommandBuffers(device.handle, &cmdAllocInfo, &frameInfo.frameData[i].primaryCommandBuffer);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);

        res = vkCreateFence(device.handle, &fenceCreateInfo, 0, &frameInfo.frameData[i].renderFence);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);

        res = vkCreateSemaphore(device.handle, &semaphoreCreateInfo, 0, &frameInfo.frameData[i].swapchainSemaphore);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);

        res = vkCreateSemaphore(device.handle, &semaphoreCreateInfo, 0, &frameInfo.frameData[i].renderSemaphore);
        if (res != VK_SUCCESS) return VkResultToVulkanError(res);
    }

    return frameInfo;
}

void Acamarachi::Vulkan::FrameInformation::deinitialize(Acamarachi::Vulkan::Device &device)
{
    for (std::size_t i = 0; i < FRAME_BUFFERING; ++i) {
        vkDestroyFence(device.handle, frameData[i].renderFence, 0);
        vkDestroySemaphore(device.handle, frameData[i].swapchainSemaphore, 0);
        vkDestroySemaphore(device.handle, frameData[i].renderSemaphore, 0);
        vkDestroyCommandPool(device.handle, frameData[i].commandPool, 0);
    }
}

Acamarachi::Vulkan::FrameManagementData Acamarachi::Vulkan::FrameInformation::getCurrentFrameData()
{
    return frameData[currentFrameIndex % FRAME_BUFFERING];
}

bool Acamarachi::Vulkan::FrameInformation::draw(Acamarachi::Vulkan::Device &device, Acamarachi::Vulkan::Swapchain& swapchain)
{
    FrameManagementData currentFrame = getCurrentFrameData();
    vkWaitForFences(device.handle, 1, &currentFrame.renderFence, VK_TRUE, 1000000000);
    vkResetFences(device.handle, 1, &currentFrame.renderFence);

    uint32_t imageIndex = 0;
    vkAcquireNextImageKHR(device.handle, swapchain.handle, 1000000000, currentFrame.swapchainSemaphore, 0, &imageIndex);

    vkResetCommandBuffer(currentFrame.primaryCommandBuffer, 0);

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(currentFrame.primaryCommandBuffer, &beginInfo);

    transitionImage(currentFrame.primaryCommandBuffer, swapchain.images[imageIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

	VkClearColorValue clearValue;
	clearValue = { { 0.0f, 0.0f, 1.0f, 1.0f } };

    VkImageSubresourceRange clearRange = {};
    clearRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    clearRange.baseMipLevel = 0;
    clearRange.levelCount = VK_REMAINING_MIP_LEVELS;
    clearRange.baseArrayLayer = 0;
    clearRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

    vkCmdClearColorImage(currentFrame.primaryCommandBuffer, swapchain.images[imageIndex], VK_IMAGE_LAYOUT_GENERAL, &clearValue, 1, &clearRange);

    transitionImage(currentFrame.primaryCommandBuffer, swapchain.images[imageIndex], VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

    vkEndCommandBuffer(currentFrame.primaryCommandBuffer);

    VkCommandBufferSubmitInfo cmdSubmitInfo = {};
    cmdSubmitInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    cmdSubmitInfo.commandBuffer = currentFrame.primaryCommandBuffer;

    VkSemaphoreSubmitInfo waitInfo = {};
    waitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    waitInfo.semaphore = currentFrame.swapchainSemaphore;
    waitInfo.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR;
    waitInfo.value = 1;

    VkSemaphoreSubmitInfo signalInfo = {};
    signalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    signalInfo.semaphore = currentFrame.renderSemaphore;
    signalInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
    signalInfo.value = 1;

    VkSubmitInfo2 submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    submitInfo.waitSemaphoreInfoCount = 1;
    submitInfo.pWaitSemaphoreInfos = &waitInfo;
    submitInfo.signalSemaphoreInfoCount = 1;
    submitInfo.pSignalSemaphoreInfos = &signalInfo;
    submitInfo.commandBufferInfoCount = 1;
    submitInfo.pCommandBufferInfos = &cmdSubmitInfo;

    vkQueueSubmit2(device.graphicQueue.handle, 1, &submitInfo, currentFrame.renderFence);

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &swapchain.handle;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &currentFrame.renderSemaphore;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(device.presentQueue.handle, &presentInfo);

    return false;
}
