#pragma once

namespace Acamarachi::Vulkan
{

    enum class Result
    {
        Success,

        // VkResult
        OutOfHostMemory,
        OutOfDeviceMemory,
        InitializationFailed,

        MissingLayer,
        MissingExtension,
        ImcompatibleDriver,

        // Custom
        NotSuitableDevice,
        QueueQueryFailed,
        
        Unexpected,
    };

}