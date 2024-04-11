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

        static ErrorOr<File> open(const char *, OpenMode);
        static ErrorOr<File> open(const std::string &, OpenMode);

        ErrorOr<ssize_t> read(char *, size_t n);
        ErrorOr<ssize_t> read(Slice<char> &);
        ErrorOr<Slice<char>> readAll(Allocator::Interface);


        ErrorOr<_off_t> getFileSize();
        _off_t fileSize() const { return size; }

        void closeFile();

    private:
        int fd = -1;
        OpenMode mode = OpenMode::Read;
        _off_t size = -1;
    };
}