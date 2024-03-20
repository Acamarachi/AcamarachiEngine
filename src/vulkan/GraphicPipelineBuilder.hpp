#ifndef ACAMARACHI_VULKAN_GRAPHIC_PIPELINE_BUILDER
#define ACAMARACHI_VULKAN_GRAPHIC_PIPELINE_BUILDER 1

#include <vulkan/vulkan.h>
#include <vector>

#include "Device.hpp"

namespace Acamarachi::Vulkan
{

    class GraphicPipelineBuilder
    {
        std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {};
        VkPipelineVertexInputStateCreateInfo vertexInputState;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
        VkPipelineTessellationStateCreateInfo tessellationState;
        VkPipelineViewportStateCreateInfo viewportState;
        VkPipelineRasterizationStateCreateInfo rasterizationState;
        VkPipelineMultisampleStateCreateInfo multisampleState;
        VkPipelineDepthStencilStateCreateInfo depthStencilState;
        VkPipelineColorBlendStateCreateInfo colorBlendState;
        VkPipelineDynamicStateCreateInfo dynamicState;
        VkFormat colorAttachementFormat;
    
        GraphicPipelineBuilder();
        GraphicPipelineBuilder(const GraphicPipelineBuilder&) = delete;

        ~GraphicPipelineBuilder() = default;

        void clear();

        VkPipeline build(Device& device);
    };
}

#endif