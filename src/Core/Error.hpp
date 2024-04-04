#pragma once

#include "Expected.hpp"

namespace Acamarachi::Core
{
    enum class ErrorCode
    {
        // Allocator
        OutOfMemory,
        NoReallocImpl,
        NoAllocImpl,

        // File
        SharingViolation,
        PathAlreadyExists,
        FileNotFound,
        AccessDenied,
        PipeBusy,
        NameTooLong,
        Unexpected,
        IsDirectory,
        SymbolicLinkLoop,
        ProcessFdQuotaExceeded,
        SystemFdQuotaExceeded,
        NoSpaceLeft,
        Overflow,
        ReadOnlyFileSystem,
        WouldBlock,
        TextBusy,
        PointsOutOfMemory,
    };

    template<typename T>
    using ErrorOr = Expected<T, ErrorCode>;
}