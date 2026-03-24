// CodeNebula - C++23 Example: filesystem::recursive_directory_iterator Improvements
// Compile: g++ -std=c++23 -Wall -Wextra -o example filesystem_recursive.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// C++23 continues to refine <filesystem>. This example demonstrates
// recursive_directory_iterator with improved error handling,
// directory_options, and integration with C++23 ranges.

void print_tree(const fs::path& root, int max_depth = 3) {
    std::error_code ec;
    auto options = fs::directory_options::skip_permission_denied;
    auto it = fs::recursive_directory_iterator(root, options, ec);

    if (ec) {
        std::cout << "Error opening " << root << ": " << ec.message() << "\n";
        return;
    }

    for (const auto& entry : it) {
        if (it.depth() > max_depth) {
            it.disable_recursion_pending();
            continue;
        }
        std::string indent(it.depth() * 2, ' ');
        if (entry.is_directory(ec)) {
            std::cout << indent << "[DIR]  " << entry.path().filename().string() << "/\n";
        } else if (entry.is_regular_file(ec)) {
            auto size = entry.file_size(ec);
            std::cout << indent << "[FILE] " << entry.path().filename().string()
                      << " (" << (ec ? 0 : size) << " bytes)\n";
        }
    }
}

int main() {
    std::cout << "=== filesystem::recursive_directory_iterator improvements ===\n\n";

    // Create a temporary directory structure for demonstration
    auto temp = fs::temp_directory_path() / "codenebula_fs_demo";
    fs::remove_all(temp);  // Clean up previous run
    fs::create_directories(temp / "src" / "core");
    fs::create_directories(temp / "src" / "utils");
    fs::create_directories(temp / "docs");

    // Create some files
    for (auto name : {"main.cpp", "README.md"}) {
        std::ofstream(temp / name) << "// " << name << "\n";
    }
    for (auto name : {"engine.cpp", "engine.h"}) {
        std::ofstream(temp / "src" / "core" / name) << "// " << name << "\n";
    }
    std::ofstream(temp / "src" / "utils" / "helpers.h") << "// helpers\n";
    std::ofstream(temp / "docs" / "guide.md") << "# Guide\n";

    // Print directory tree
    std::cout << "Directory tree of " << temp.filename().string() << "/:\n";
    print_tree(temp);

    // Collect all .cpp files recursively
    std::cout << "\n--- All .cpp files ---\n";
    std::vector<fs::path> cpp_files;
    for (const auto& entry : fs::recursive_directory_iterator(temp)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            cpp_files.push_back(entry.path());
        }
    }
    std::ranges::sort(cpp_files);
    for (const auto& p : cpp_files) {
        std::cout << "  " << fs::relative(p, temp).string() << "\n";
    }

    // Count entries by type
    std::cout << "\n--- Statistics ---\n";
    int dirs = 0, files = 0;
    for (const auto& entry : fs::recursive_directory_iterator(temp)) {
        if (entry.is_directory()) ++dirs;
        else if (entry.is_regular_file()) ++files;
    }
    std::cout << "Directories: " << dirs << "\n";
    std::cout << "Files: " << files << "\n";

    // Cleanup
    fs::remove_all(temp);
    std::cout << "\nTemporary directory cleaned up.\n";

    return 0;
}

// Expected output (paths may vary):
// === filesystem::recursive_directory_iterator improvements ===
//
// Directory tree of codenebula_fs_demo/:
// [DIR]  docs/
//   [FILE] guide.md (8 bytes)
// [DIR]  src/
//   [DIR]  core/
//     [FILE] engine.cpp (15 bytes)
//     [FILE] engine.h (14 bytes)
//   [DIR]  utils/
//     [FILE] helpers.h (11 bytes)
// [FILE] main.cpp (13 bytes)
// [FILE] README.md (14 bytes)
//
// --- All .cpp files ---
//   main.cpp
//   src/core/engine.cpp
//
// --- Statistics ---
// Directories: 4
// Files: 5
//
// Temporary directory cleaned up.
