#include <iostream>
#include "Context.hpp"

// TODO: Better error handling and reporting
Acamarachi::Vulkan::Context::Error Acamarachi::Vulkan::Context::initialize(const char *appName, GetRequiredExtensions *getRequiredExtensions, void *window, CreateWindowSurfaceFunction *createWindowSurface)
{
    Acamarachi::Vulkan::Context context = {};
    
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
        return maybe_instance.error();
    }
    context.instance = maybe_instance.result();

    auto maybe_surface = Acamarachi::Vulkan::Surface::initialize(context.instance, window, createWindowSurface) catch_err(maybe_surface) {
        return maybe_surface.error();
    }
    context.surface = maybe_surface.result();

    auto maybe_device = Acamarachi::Vulkan::Device::initialize(context.instance, context.surface, device_extensions, instance_layers) catch_err(maybe_device) {
        return maybe_device.error();
    }
    context.device = maybe_device.result();

    auto maybe_swapchain = Acamarachi::Vulkan::Swapchain::initialize(context.device, context.surface, 1280, 720) catch_err(maybe_swapchain) {
        return maybe_swapchain.error();
    }
    context.swapchain = maybe_swapchain.result();

    auto maybe_frameInfo = Acamarachi::Vulkan::FrameInformation::initialize(context.device) catch_err(maybe_frameInfo) {
        return maybe_frameInfo.error();
    }
    context.frameInfo = maybe_frameInfo.result();

    return context;
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