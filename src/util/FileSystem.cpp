#include "FileSystem.hpp"
#include <climits>
#include <filesystem>
#include <string>
#include <whereami.h>

#if __linux__
#include <unistd.h>
#endif

std::string FileSystem::getExecutablePath()
{
    std::string path;
#if __linux__
    // Temporarily store executable path
    char buff[PATH_MAX]; // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    // Get executable path
    ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff) - 1);
    // Successfully retrieved path - store in c++ string
    if (len != -1)
    {
        buff[len] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,
                          // cppcoreguidelines-pro-bounds-constant-array-index)
        path = std::string(std::filesystem::path(buff).remove_filename()) + "/";
    }
#else
    // Get path length
    const int length = wai_getExecutablePath(nullptr, 0, nullptr);
    if (length <= 0)
        return path;
    // Temporarily store executable path
    char *buff = new char[length + 1];
    // Get path
    int dirname_length = 0;
    wai_getExecutablePath(static_cast<char *>(buff), length, &dirname_length);
    buff[length] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    // Store path in c++ string
    path = std::string(std::filesystem::path(buff).remove_filename()) + "/";
    // Cleanup
    delete[] buff;
#endif
    return path;
}
