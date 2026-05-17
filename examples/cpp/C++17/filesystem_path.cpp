// CodeNebula - C++17 Example: std::filesystem::path
// Compile: g++ -std=c++17 -Wall -Wextra -o example filesystem_path.cpp -lstdc++fs

// std::filesystem::path represents a filesystem path and provides methods
// to construct, decompose, and manipulate path components portably.

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // --- Construction ---
    std::cout << "=== Construction ===" << std::endl;
    fs::path p1("/usr/local/bin/app");
    fs::path p2("C:\\Users\\dev\\file.txt");
    fs::path p3 = fs::path("src") / "main" / "app.cpp";
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3 (composed): " << p3 << std::endl;

    // --- Decomposition ---
    std::cout << "\n=== Decomposition ===" << std::endl;
    fs::path file("/home/user/docs/report.tar.gz");
    std::cout << "Full path:       " << file << std::endl;
    std::cout << "root_path:       " << file.root_path() << std::endl;
    std::cout << "parent_path:     " << file.parent_path() << std::endl;
    std::cout << "filename:        " << file.filename() << std::endl;
    std::cout << "stem:            " << file.stem() << std::endl;
    std::cout << "extension:       " << file.extension() << std::endl;

    // --- Queries ---
    std::cout << "\n=== Queries ===" << std::endl;
    std::cout << "has_root_path:   " << file.has_root_path() << std::endl;
    std::cout << "has_parent_path: " << file.has_parent_path() << std::endl;
    std::cout << "has_filename:    " << file.has_filename() << std::endl;
    std::cout << "has_extension:   " << file.has_extension() << std::endl;
    std::cout << "is_absolute:     " << file.is_absolute() << std::endl;
    std::cout << "is_relative:     " << file.is_relative() << std::endl;

    // --- Manipulation ---
    std::cout << "\n=== Manipulation ===" << std::endl;
    fs::path mp("project/src/main.cpp");
    mp.replace_filename("util.cpp");
    std::cout << "replace_filename: " << mp << std::endl;
    mp.replace_extension(".hpp");
    std::cout << "replace_extension: " << mp << std::endl;
    mp.remove_filename();
    std::cout << "remove_filename:  " << mp << std::endl;

    // --- Iteration over components ---
    std::cout << "\n=== Path components ===" << std::endl;
    fs::path cp("/usr/local/include/header.h");
    for (const auto& part : cp) {
        std::cout << "  [" << part << "]" << std::endl;
    }

    return 0;
}

/*
Expected output (on POSIX systems):
=== Construction ===
p1: "/usr/local/bin/app"
p2: "C:\\Users\\dev\\file.txt"
p3 (composed): "src/main/app.cpp"

=== Decomposition ===
Full path:       "/home/user/docs/report.tar.gz"
root_path:       "/"
parent_path:     "/home/user/docs"
filename:        "report.tar.gz"
stem:            "report.tar"
extension:       ".gz"

=== Queries ===
has_root_path:   1
has_parent_path: 1
has_filename:    1
has_extension:   1
is_absolute:     1
is_relative:     0

=== Manipulation ===
replace_filename: project/src/util.cpp
replace_extension: project/src/util.hpp
remove_filename:  project/src/

=== Path components ===
  ["/"]
  ["usr"]
  ["local"]
  ["include"]
  ["header.h"]
*/
