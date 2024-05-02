#pragma once

#include <fcntl.h>
#include <string>
#include "Allocator/Interface.hpp"
#include "Slice.hpp"
#include "Error.hpp"

namespace Acamarachi::Core
{
    class File
    {
    public:
        enum class Result
        {
            Success,
            OutOfMemory,
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

        using Stat = struct stat;

        enum class OpenMode
        {
            Read = O_RDONLY,
            Write = O_WRONLY,
            ReadWrite = O_RDWR,
        };

        File() = default;
        File(const File &) = default;
        ~File() = default;

        File &operator=(File &&other) noexcept
        {
            fd = std::move(other.fd);
            mode = std::move(other.mode);
            size = std::move(other.size);

            other.fd = -1;
            other.size = 0;
            return *this;
        }

        Result open(const char *, OpenMode);
        Result open(const std::string &, OpenMode);

        Result read(char *, size_t, ssize_t &);
        Result read(Slice<char> &, ssize_t &);
        Slice<char> readAll(Allocator::Interface, Result&);

        off_t getFileSize(Result &res);
        _off_t fileSize() const { return size; }

        void closeFile();

    private:
        int fd = -1;
        OpenMode mode = OpenMode::Read;
        _off_t size = -1;
    };
}