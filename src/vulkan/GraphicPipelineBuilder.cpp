#include "GraphicPipelineBuilder.hpp"
#include "../macros.h"

Acamarachi::Vulkan::GraphicPipelineBuilder::GraphicPipelineBuilder()
{
    clear();
}

void Acamarachi::Vulkan::GraphicPipelineBuilder::clear()
{
    shaderStages.clear();
    vertexInputState = {};
    vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    inputAssemblyState = {};
    inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

    tessellationState = {};
    tessellationState.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

    viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

    rasterizationState = {};
    rasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

    multisampleState = {};
    multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

    depthStencilState = {};
    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

    colorBlendState = {};
    colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

    dynamicState = {};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

    colorAttachementFormat = VK_FORMAT_R8G8B8A8_SRGB;
}

VkPipeline Acamarachi::Vulkan::GraphicPipelineBuilder::build(Device &device)
{
    UNUSED_PARAM(device);
    viewportState.scissorCount = 1;
    viewportState.viewportCount = 1;
    

    return VkPipeline();
}
