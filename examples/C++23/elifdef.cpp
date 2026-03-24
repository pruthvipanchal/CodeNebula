// CodeNebula - C++23 Example: #elifdef and #elifndef Directives
// Compile: g++ -std=c++23 -Wall -Wextra -o example elifdef.cpp
// Note: Requires GCC 12+ / Clang 13+ / MSVC 19.32+

// C++23 adds #elifdef and #elifndef as shorthand for:
//   #elif defined(MACRO)   ->  #elifdef MACRO
//   #elif !defined(MACRO)  ->  #elifndef MACRO

#include <iostream>

// --- Platform detection using #elifdef ---
// Define one to test: PLATFORM_LINUX, PLATFORM_MACOS, PLATFORM_WINDOWS
#define PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
    constexpr const char* PLATFORM = "Linux";
    constexpr const char* PATH_SEP = "/";
#elifdef PLATFORM_MACOS
    constexpr const char* PLATFORM = "macOS";
    constexpr const char* PATH_SEP = "/";
#elifdef PLATFORM_WINDOWS
    constexpr const char* PLATFORM = "Windows";
    constexpr const char* PATH_SEP = "\\";
#else
    constexpr const char* PLATFORM = "Unknown";
    constexpr const char* PATH_SEP = "/";
#endif

// --- Feature detection using #elifndef ---
// #define HAS_OPENGL
// #define HAS_VULKAN
#define HAS_DIRECTX

#ifdef HAS_OPENGL
    constexpr const char* RENDERER = "OpenGL";
#elifdef HAS_VULKAN
    constexpr const char* RENDERER = "Vulkan";
#elifdef HAS_DIRECTX
    constexpr const char* RENDERER = "DirectX";
#elifndef HAS_SOFTWARE_RENDERER
    constexpr const char* RENDERER = "No renderer available";
#else
    constexpr const char* RENDERER = "Software renderer";
#endif

// --- Build type with #elifndef ---
#define NDEBUG

#ifdef DEBUG
    constexpr const char* BUILD = "Debug";
#elifndef NDEBUG
    constexpr const char* BUILD = "Debug (NDEBUG not set)";
#else
    constexpr const char* BUILD = "Release";
#endif

int main() {
    std::cout << "=== #elifdef / #elifndef ===" << std::endl;

    std::cout << "\nPlatform detection:" << std::endl;
    std::cout << "  Platform:  " << PLATFORM << std::endl;
    std::cout << "  Path sep:  " << PATH_SEP << std::endl;

    std::cout << "\nRenderer detection:" << std::endl;
    std::cout << "  Renderer:  " << RENDERER << std::endl;

    std::cout << "\nBuild type:" << std::endl;
    std::cout << "  Build:     " << BUILD << std::endl;

    std::cout << "\n=== Syntax comparison ===" << std::endl;
    std::cout << "  Old: #elif defined(X)   -> New: #elifdef X" << std::endl;
    std::cout << "  Old: #elif !defined(X)  -> New: #elifndef X" << std::endl;

    return 0;
}

/*
Expected output:
=== #elifdef / #elifndef ===

Platform detection:
  Platform:  Windows
  Path sep:  \

Renderer detection:
  Renderer:  DirectX

Build type:
  Build:     Release

=== Syntax comparison ===
  Old: #elif defined(X)   -> New: #elifdef X
  Old: #elif !defined(X)  -> New: #elifndef X
*/
