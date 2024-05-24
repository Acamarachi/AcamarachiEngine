#include <iostream>
#include "Context.hpp"
#include "../Core/Slice.hpp"

namespace Acamarachi::Vulkan
{

    Result Context::initialize(Core::Allocator::Interface &allocator, const char *appName, GetRequiredExtensions *getRequiredExtensions, void *window, CreateWindowSurfaceFunction *createWindowSurface)
    {
        const char *device_ext = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        Core::Slice<const char *> instance_extensions = Core::Slice<const char *>();
        Core::Slice<const char *> instance_layers = Core::Slice<const char *>();
        Core::Slice<const char *> device_extensions = Core::Slice<const char *>(&device_ext, 1);

        uint32_t count = 0;
        auto glfwExtensions = getRequiredExtensions(&count);
        allocator.allocSlice(count + 1, alignof(const char *), instance_extensions);

        for (uint32_t i = 0; i < count; ++i)
        {
            instance_extensions[i] = glfwExtensions[i];
        }
        instance_extensions[count] = "VK_EXT_debug_utils";

        Result state = Result::Success;

        state = instance.initialize(appName, instance_extensions, instance_layers);
        if (state != Result::Success)
        {
            return state;
        }

        Core::Slice<VkPhysicalDevice> pDevices = Core::Slice<VkPhysicalDevice>();
        state = instance.getAvailablePhysicalDevice(allocator, pDevices);
        if (state != Result::Success)
        {
            std::cout << "Failed to retrieve instance's physical devices" << std::endl;
            instance.deinitialize();
            return state;
        }

        state = surface.initialize(instance, window, createWindowSurface);
        if (state != Result::Success)
        {
            allocator.free(pDevices);
            instance.deinitialize();
            return state;
        }

        Acamarachi::Vulkan::DeviceInitializationInfo info = Acamarachi::Vulkan::DeviceInitializationInfo(instance, surface, device_extensions, instance_layers, pDevices);
        state = device.initialize(allocator, info);
        if (state != Result::Success)
        {
            surface.deinitialize(instance);
            instance.deinitialize();
            return state;
        }
        allocator.free(pDevices);

        // TODO: Dynamic window size
        state = swapchain.initialize(allocator, device, surface, 640, 480);
        if (state != Result::Success)
        {
            device.deinitialize();
            surface.deinitialize(instance);
            instance.deinitialize();
            return state;
        }

        state = frameInfo.initialize(device);
        if (state != Result::Success)
        {
            swapchain.deinitialize(allocator, device);
            device.deinitialize();
            surface.deinitialize(instance);
            instance.deinitialize();
            return state;
        }

        return Result::Success;
    }

    void Context::deinitialize(Core::Allocator::Interface &allocator)
    {
        vkDeviceWaitIdle(device.handle);
        frameInfo.deinitialize(device);
        swapchain.deinitialize(allocator, device);
        device.deinitialize();
        surface.deinitialize(instance);
        instance.deinitialize();
    }

};