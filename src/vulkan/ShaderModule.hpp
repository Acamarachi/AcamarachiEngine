#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Result.hpp"
#include "Device.hpp"
#include "../Core/Slice.hpp"

namespace Acamarachi::Vulkan
{
    class ShaderModule
    {
    private:
        VkShaderModule handle;
        VkShaderStageFlags stage;

    public:
        enum class Stage
        {
            Vertex = VK_SHADER_STAGE_VERTEX_BIT,
            Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
        };

        ShaderModule() = default;
        ShaderModule(const ShaderModule &) = default;
        ~ShaderModule() = default;

        Result initialize(Device &device, Stage stage, const Core::Slice<uint32_t> &code);
        void deinitialize(Device &device);
    };
}
