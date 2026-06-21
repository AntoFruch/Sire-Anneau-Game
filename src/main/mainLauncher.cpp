//
// Created by Antonin Fruchet on 25/05/2026.
//
#include "Engine.h"

#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

std::filesystem::path getExecutablePath()
{
#if defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);

    std::string buffer(size, '\0');
    if (_NSGetExecutablePath(buffer.data(), &size) != 0)
    {
        throw std::runtime_error("Could not get executable path");
    }

    return std::filesystem::weakly_canonical(buffer.c_str());

#elif defined(_WIN32)
    std::wstring buffer(MAX_PATH, L'\0');

    DWORD size = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));

    if (size == 0)
    {
        throw std::runtime_error("Could not get executable path");
    }

    while (size == buffer.size())
    {
        buffer.resize(buffer.size() * 2);
        size = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));

        if (size == 0)
        {
            throw std::runtime_error("Could not get executable path");
        }
    }

    buffer.resize(size);
    return std::filesystem::path(buffer);

#elif defined(__linux__)
    std::vector<char> buffer(1024);

    while (true)
    {
        ssize_t size = readlink("/proc/self/exe", buffer.data(), buffer.size());

        if (size == -1)
        {
            throw std::runtime_error("Could not get executable path");
        }

        if (static_cast<std::size_t>(size) < buffer.size())
        {
            return std::filesystem::weakly_canonical(
                std::string(buffer.data(), static_cast<std::size_t>(size))
            );
        }

        buffer.resize(buffer.size() * 2);
    }

#else
    throw std::runtime_error("Unsupported platform");
#endif
}

void setWorkingDirectoryToExecutableDirectory()
{
    const auto executablePath = getExecutablePath();
    std::filesystem::current_path(executablePath.parent_path());
}

int main() {
    setWorkingDirectoryToExecutableDirectory();
    Game game("resources/scenes/main_menu.xml");
    game.run();
    return 0;
}