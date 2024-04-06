#include <iostream>
#include "Context.hpp"

// TODO: Better error handling and reporting
void Acamarachi::Vulkan::Context::initialize(const char *appName, GetRequiredExtensions *getRequiredExtensions, void *window, CreateWindowSurfaceFunction *createWindowSurface)
{   
    std::vector<const char *> instance_layers;
    std::vector<const char *> instance_extensions;
    std::vector<const char *> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    instance_layers.push_back("VK_LAYER_KHRONOS_validation");

    instance_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    uint32_t count = 0;
    const char **glfw_required_extensions = getRequiredExtensions(&count);
    for (uint32_t i = 0; i < count; i++)
    {
        instance_extensions.push_back(glfw_required_extensions[i]);
    }

    auto maybe_instance = Acamarachi::Vulkan::Instance::initialize(appName, instance_extensions, instance_layers) catch_err(maybe_instance) {
        throw maybe_instance.error();
    }
    this->instance = maybe_instance.result();

    auto maybe_surface = Acamarachi::Vulkan::Surface::initialize(this->instance, window, createWindowSurface) catch_err(maybe_surface) {
        throw maybe_surface.error();
    }
    this->surface = maybe_surface.result();

    auto maybe_device = Acamarachi::Vulkan::Device::initialize(this->instance, this->surface, device_extensions, instance_layers) catch_err(maybe_device) {
        throw maybe_device.error();
    }
    this->device = maybe_device.result();

    auto maybe_swapchain = Acamarachi::Vulkan::Swapchain::initialize(this->device, this->surface, 1280, 720) catch_err(maybe_swapchain) {
        throw maybe_swapchain.error();
    }
    this->swapchain = maybe_swapchain.result();

    auto maybe_frameInfo = Acamarachi::Vulkan::FrameInformation::initialize(this->device) catch_err(maybe_frameInfo) {
        throw maybe_frameInfo.error();
    }
    this->frameInfo = maybe_frameInfo.result();

}

void Acamarachi::Vulkan::Context::deinitialize()
{
    vkDeviceWaitIdle(device.handle);
    frameInfo.deinitialize(device);
    swapchain.deinitialize(device);
    device.deinitialize();
    surface.deinitialize(instance);
    instance.deinitialize();
}