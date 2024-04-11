#include "File.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

const auto cRead = &read;

namespace Acamarachi::Core
{

    ErrorOr<File> File::open(const char *filepath, OpenMode mode)
    {
        File f = {};
        f.fd = _open(filepath, (int)mode);
        if (f.fd == -1)
        {
            switch (errno)
            {
            case EACCES:
                return ErrorCode::AccessDenied;
            case EEXIST:
                return ErrorCode::PathAlreadyExists;
            case EISDIR:
                return ErrorCode::IsDirectory;
            case ELOOP:
                return ErrorCode::SymbolicLinkLoop;
            case EMFILE:
                return ErrorCode::ProcessFdQuotaExceeded;
            case ENAMETOOLONG:
                return ErrorCode::NameTooLong;
            case ENFILE:
                return ErrorCode::SystemFdQuotaExceeded;
            case ENOENT:
                return ErrorCode::FileNotFound;
            case ENOSPC:
                return ErrorCode::NoSpaceLeft;
            case EOVERFLOW:
                return ErrorCode::Overflow;
            case EROFS:
                return ErrorCode::ReadOnlyFileSystem;
            case EAGAIN:
                return ErrorCode::WouldBlock;
            case ENOMEM:
                return ErrorCode::OutOfMemory;
            case ETXTBSY:
                return ErrorCode::TextBusy;
            default:
                return ErrorCode::Unexpected;
            }
        }
        auto maybe_size = f.getFileSize();
        if (!maybe_size)
        {
            return maybe_size.error();
        }
        f.size = maybe_size.result();
        f.mode = mode;
        return f;
    }

    ErrorOr<File> File::open(const std::string &filepath, OpenMode mode)
    {
        return open(filepath.c_str(), mode);
    }

    ErrorOr<ssize_t> File::read(char *buffer, size_t n)
    {
        assert(mode != File::OpenMode::Write);
        assert(fd != -1);
        ssize_t r = cRead(fd, buffer, (unsigned int)n);
        if (r == -1)
        {
            switch (errno)
            {
            case EFAULT:
                return ErrorCode::PointsOutOfMemory;
            default:
                return ErrorCode::Unexpected;
            }
        }
        return r;
    }

    ErrorOr<ssize_t> File::read(Slice<char> &slice)
    {
        assert(mode != File::OpenMode::Write);
        assert(fd != -1);
        ssize_t r = cRead(fd, slice.ptr, (unsigned int)slice.len);
        if (r == -1)
        {
            switch (errno)
            {
            case EFAULT:
                return ErrorCode::PointsOutOfMemory;
            default:
                return ErrorCode::Unexpected;
            }
        }
        return r;
    }

    // Using mingw64 read replace '\n\r' to '\n', but mingw64 stat counts '\r' in the file size.
    // This lead to over allocation of memory, 1 byte per newline.
    ErrorOr<Slice<char>> File::readAll(Allocator::Interface allocator)
    {
        assert(mode != File::OpenMode::Write);
        auto maybe_slice = allocator.allocSlice<char>(size, 1);
        if (!maybe_slice)
            return maybe_slice.error();

        Slice<char> slice = maybe_slice.result();
        ssize_t r = cRead(fd, slice.ptr, (unsigned int)slice.len + 1);
        if (r == -1)
        {
            allocator.free(slice);
            switch (errno)
            {
            case EFAULT:
                return ErrorCode::PointsOutOfMemory;
            default:
                return ErrorCode::Unexpected;
            }
        }
        for (size_t i = (size_t)r; i < slice.len; ++i) { slice[i] = 0; }

        return slice;
    }

    ErrorOr<_off_t> File::getFileSize()
    {
        if (size < 0)
        {
            struct stat buf;
            if (fstat(fd, &buf) == -1)
            {
                switch (errno)
                {
                case EACCES:
                    return ErrorCode::AccessDenied;
                case EFAULT:
                    return ErrorCode::PointsOutOfMemory;
                case ENOMEM:
                    return ErrorCode::OutOfMemory;
                default:
                    return ErrorCode::Unexpected;
                }
            }
            return buf.st_size;
        }
        else
        {
            return size;
        }
    }

    void File::closeFile()
    {
        close(fd);
    }

}