#include "ShaderModule.hpp"

namespace Acamarachi::Vulkan
{
    Result ShaderModule::initialize(Device& device, Stage s, const Core::Slice<uint32_t> &code)
    {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.len;
        createInfo.pCode = code.ptr;

        this->stage = (uint32_t)s;

        VkResult res = vkCreateShaderModule(device.handle, &createInfo, nullptr, &handle);
        if (res != VK_SUCCESS) return fromVkResult<true>(res);
        return Result::Success;
    }

    void ShaderModule::deinitialize(Device& device)
    {
        vkDestroyShaderModule(device.handle, handle, nullptr);
        handle = VK_NULL_HANDLE;
    }
}
