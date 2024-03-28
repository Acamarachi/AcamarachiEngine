#pragma once

#include <vulkan/vulkan.h>
#include "Error.hpp"

namespace Acamarachi::Vulkan
{

class GraphicPipeline {
private:
    VkPipeline handle;
    VkPipelineLayout layout;
};

}