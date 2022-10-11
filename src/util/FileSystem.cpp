#include "FileSystem.hpp"
#include <filesystem>
#include <mach-o/dyld.h>
#include <string>
#include <whereami.h>

std::string FileSystem::getExecutablePath()
{
    std::string path;
#if __APPLE__
#include <climits>
    // Temporarily store executable path
    char buff[PATH_MAX];          // NOLINT(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    uint32_t size = sizeof(buff); // NOLINT(misc-const-correctness)
    // Get executable path
    if (_NSGetExecutablePath(static_cast<char *>(buff), &size) == 0)
        // Successfully retrieved path - store in c++ string
        path = std::string(std::filesystem::path(buff).remove_filename()) + "/";
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
    buff[length] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    // Store path in c++ string
    path = std::string(static_cast<char *>(buff)) + "/";
    // Cleanup
    delete[] buff;
#endif
    return path;
}
