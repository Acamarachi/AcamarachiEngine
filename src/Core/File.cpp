#include "File.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

namespace Acamarachi::Core
{

    ErrorOr<File> File::openFile(const char *filepath, OpenMode mode)
    {
        File f = {};
        f.fd = open(filepath, (int)mode);
        if (f.fd == -1)
        {
            switch (errno)
            {
            case EACCES:
                return ErrorCode::AccessDenied;
            case EEXIST:
                return ErrorCode::PathAlreadyExists;
            case EINTR:
                return ErrorCode::Unexpected;
            case EINVAL:
                return ErrorCode::Unexpected;
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

    Acamarachi::Core::ErrorOr<Acamarachi::Core::File> Acamarachi::Core::File::openFile(const std::string &filepath, OpenMode mode)
    {
        return openFile(filepath.c_str(), mode);
    }

    ErrorOr<Slice<char>> Acamarachi::Core::File::readAll(AllocatorInterface allocator)
    {
        assert(mode != File::OpenMode::Write);
        auto maybe_slice = allocator.allocSlice<char>(size, 1);
        if (!maybe_slice) return maybe_slice.error();

        Slice<char> slice = maybe_slice.result();
        ssize_t r = read(fd, slice.ptr, (unsigned int)size);
        if (r == -1) {
            allocator.free(slice);
            switch (errno) {
                case EFAULT:
                    return ErrorCode::PointsOutOfMemory;
                default:
                    return ErrorCode::Unexpected;
            }
        }

        return slice;
    }

    ErrorOr<_off_t> Acamarachi::Core::File::getFileSize()
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

    void Acamarachi::Core::File::closeFile()
    {
        close(fd);
    }

}