#include "FileSystem.hpp"
#include <filesystem>
#include <string>
#include <whereami.h>

std::string FileSystem::getExecutablePath()
{
    // Get path length
    const int length = wai_getExecutablePath(nullptr, 0, nullptr);
    if (length <= 0)
        return "";
    // Temporarily store executable path
    char *buff = new char[length + 1];
    // Get path
    int dirname_length = 0;
    wai_getExecutablePath(static_cast<char *>(buff), length, &dirname_length);
    buff[length] = '\0'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    // Store path in c++ string
    auto path = std::string(std::filesystem::path(buff).remove_filename()) + "/";
    // Cleanup
    delete[] buff;
    return path;
}
