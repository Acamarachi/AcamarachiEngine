#include "File.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

const auto cRead = &read;

namespace Acamarachi::Core
{

    File::Result File::open(const char *filepath, OpenMode mode)
    {
        fd = _open(filepath, (int)mode);
        if (fd == -1)
        {
            switch (errno)
            {
            case EACCES:
                return File::Result::AccessDenied;
            case EEXIST:
                return File::Result::PathAlreadyExists;
            case EISDIR:
                return File::Result::IsDirectory;
            case ELOOP:
                return File::Result::SymbolicLinkLoop;
            case EMFILE:
                return File::Result::ProcessFdQuotaExceeded;
            case ENAMETOOLONG:
                return File::Result::NameTooLong;
            case ENFILE:
                return File::Result::SystemFdQuotaExceeded;
            case ENOENT:
                return File::Result::FileNotFound;
            case ENOSPC:
                return File::Result::NoSpaceLeft;
            case EOVERFLOW:
                return File::Result::Overflow;
            case EROFS:
                return File::Result::ReadOnlyFileSystem;
            case EAGAIN:
                return File::Result::WouldBlock;
            case ENOMEM:
                return File::Result::OutOfMemory;
            case ETXTBSY:
                return File::Result::TextBusy;
            default:
                return File::Result::Unexpected;
            }
        }
        Result getFileSizeResult = File::Result::Success;
        size = getFileSize(getFileSizeResult);
        if (getFileSizeResult != File::Result::Success)
        {
            return getFileSizeResult;
        }
        mode = mode;
        return File::Result::Success;
    }

    File::Result File::open(const std::string &filepath, OpenMode mode)
    {
        return open(filepath.c_str(), mode);
    }

    File::Result File::read(char *buffer, size_t n, ssize_t &r)
    {
        assert(mode != File::OpenMode::Write);
        assert(fd != -1);
        r = cRead(fd, buffer, (unsigned int)n);
        if (r == -1)
        {
            switch (errno)
            {
            case EFAULT:
                return File::Result::PointsOutOfMemory;
            default:
                return File::Result::Unexpected;
            }
        }
        return File::Result::Success;
    }

    File::Result File::read(Slice<char> &slice, ssize_t &r)
    {
        return read(slice.ptr, slice.len, r);
    }

    // Using mingw64 read replace '\n\r' to '\n', but mingw64 stat counts '\r' in the file size.
    // This lead to over allocation of memory, 1 byte per newline.
    Slice<char> File::readAll(Allocator::Interface allocator, Result &res)
    {
        res = File::Result::Success;
        assert(mode != File::OpenMode::Write);
        Slice<char> slice = Slice<char>();
        auto allocRes = allocator.callocSlice(size, 1, slice);
        if (allocRes != Allocator::Result::Success)
        {
            std::cerr << "Allocator failed with: " << (int)allocRes << "\n";
            res = File::Result::OutOfMemory;
            return Slice<char>();
        }

        ssize_t r = 0;
        Result readResult = read(slice, r);
        if ((readResult = read(slice, r)) != File::Result::Success)
        {
            res = readResult;
            allocator.free(slice);
            return Slice<char>();
        }

        return slice;
    }

    off_t File::getFileSize(File::Result &res)
    {
        struct stat buf;
        if (fstat(fd, &buf) == -1)
        {
            switch (errno)
            {
            case EACCES:
                res = File::Result::AccessDenied;
                return 0;
            case EFAULT:
                res = File::Result::PointsOutOfMemory;
                return 0;
            case ENOMEM:
                res = File::Result::OutOfMemory;
                return 0;
            default:
                res = File::Result::Unexpected;
                return 0;
            }
        }
        return buf.st_size;
    }

    void File::closeFile()
    {
        close(fd);
    }
}