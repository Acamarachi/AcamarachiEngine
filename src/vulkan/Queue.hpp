#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

namespace Acamarachi::Vulkan
{
    class Queue
    {

    public:
        VkQueue handle = VK_NULL_HANDLE;

        Queue();
        ~Queue();

        bool findQueueFamilies(VkQueueFlagBits flag);
    };
}