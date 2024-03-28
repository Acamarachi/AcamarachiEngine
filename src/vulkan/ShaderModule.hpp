#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Error.hpp"

namespace Acamarachi::Vulkan
{
    class ShaderModule {
        private:
            VkShaderModule handle;
            VkShaderStageFlags stage;
        public:
            using Error = Acamarachi::Core::Expected<ShaderModule, VulkanError>;

            ShaderModule() = default;
            ShaderModule(const ShaderModule&) = default;
            ~ShaderModule() = default;

            static Error initialize(const std::vector<uint32_t>& code);
            void deinitialize();
    };
} // namespace Acamarachi::Vulkan
