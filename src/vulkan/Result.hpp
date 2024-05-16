#pragma once

#include "vulkan/vulkan.h"

namespace Acamarachi::Vulkan
{

    enum class Result
    {
        Success,

        // VkResult
        OutOfHostMemory,
        OutOfDeviceMemory,
        InitializationFailed,

        // VkResult possibly not error
        NotReady,
        Timeout,
        EventSet,
        EventReset,
        Incomplete,

        MissingLayer,
        MissingExtension,
        ImcompatibleDriver,

        // Custom
        NotSuitableDevice,
        QueueQueryFailed,
        NoSuitableSurfaceFormat,
        NoSuitablePresentMode,

        Unexpected,
    };

    template <bool everythingError>
    inline Result fromVkResult(VkResult vkRes)
    {
        if (!everythingError)
        {
            switch (vkRes)
            {
            case VK_SUCCESS:
            case VK_INCOMPLETE:
                return Result::Success;
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                return Result::OutOfHostMemory;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return Result::OutOfDeviceMemory;
            case VK_ERROR_INITIALIZATION_FAILED:
                return Result::InitializationFailed;
            case VK_ERROR_LAYER_NOT_PRESENT:
                return Result::MissingLayer;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                return Result::MissingExtension;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                return Result::ImcompatibleDriver;
            default:
                return Result::Unexpected;
            }
        }
        else
        {
            switch (vkRes)
            {
            case VK_SUCCESS:
                return Result::Success;
            case VK_INCOMPLETE:
                return Result::Incomplete;
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                return Result::OutOfHostMemory;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return Result::OutOfDeviceMemory;
            case VK_ERROR_INITIALIZATION_FAILED:
                return Result::InitializationFailed;
            case VK_ERROR_LAYER_NOT_PRESENT:
                return Result::MissingLayer;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                return Result::MissingExtension;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                return Result::ImcompatibleDriver;
            default:
                return Result::Unexpected;
            }
        }
    }
}