#ifndef ACAMARACH_VULKAN_UTILS
#define ACAMARACH_VULKAN_UTILS 1

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>

namespace Acamarachi::Vulkan
{

    const char *vkErrorToString(VkResult res)
    {
        return string_VkResult(res);
    }

};

#endif