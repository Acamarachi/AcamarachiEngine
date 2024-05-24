#include "Utils.hpp"

namespace Acamarachi::Vulkan
{
    const char *vkErrorToString(VkResult res)
    {
        return string_VkResult(res);
    }

    void transitionImage(VkCommandBuffer cmd, VkImage img, VkImageLayout srcLayout, VkImageLayout dstLayout)
    {
        VkImageMemoryBarrier2 imgBarrier = {};
        imgBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;

        imgBarrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        imgBarrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
        imgBarrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        imgBarrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

        imgBarrier.oldLayout = srcLayout;
        imgBarrier.newLayout = dstLayout;

        VkImageAspectFlags aspectMask = (dstLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
        imgBarrier.subresourceRange.aspectMask = aspectMask;
        imgBarrier.subresourceRange.baseMipLevel = 0;
        imgBarrier.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
        imgBarrier.subresourceRange.baseArrayLayer = 0;
        imgBarrier.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

        imgBarrier.image = img;

        VkDependencyInfo depInfo = {};
        depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        depInfo.imageMemoryBarrierCount = 1;
        depInfo.pImageMemoryBarriers = &imgBarrier;

        vkCmdPipelineBarrier2(cmd, &depInfo);
    }
}