// CodeNebula - C++17 Example: std::filesystem::copy_options
// Compile: g++ -std=c++17 -Wall -Wextra -o example copy_options.cpp -lstdc++fs

// std::filesystem::copy_options is a bitmask controlling copy behavior:
// how to handle existing files, symlinks, and whether to copy recursively.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_copy_opts";
        fs::create_directories(base);
        fs::path src = base / "source.txt";
        fs::path dst = base / "dest.txt";

        { std::ofstream(src) << "original content"; }
        { std::ofstream(dst) << "existing content"; }

        // --- Default: fails if destination exists ---
        std::cout << "=== copy_options::none (default) ===" << std::endl;
        std::error_code ec;
        fs::copy_file(src, dst, fs::copy_options::none, ec);
        std::cout << "Copy with none: " << (ec ? "failed" : "succeeded")
                  << " (" << ec.message() << ")" << std::endl;

        // --- skip_existing: silently skip ---
        std::cout << "\n=== copy_options::skip_existing ===" << std::endl;
        bool result = fs::copy_file(src, dst, fs::copy_options::skip_existing);
        std::cout << "Copied: " << result << " (false means skipped)" << std::endl;

        // --- overwrite_existing: replace destination ---
        std::cout << "\n=== copy_options::overwrite_existing ===" << std::endl;
        result = fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        std::cout << "Copied: " << result << std::endl;

        // --- update_existing: copy only if source is newer ---
        std::cout << "\n=== copy_options::update_existing ===" << std::endl;
        result = fs::copy_file(src, dst, fs::copy_options::update_existing);
        std::cout << "Copied: " << result << " (false if dest is same age or newer)" << std::endl;

        // --- Demonstrate copy_options for directory copy ---
        std::cout << "\n=== Directory copy options ===" << std::endl;
        fs::path dir_src = base / "dir_src";
        fs::path dir_dst = base / "dir_dst";
        fs::create_directories(dir_src / "sub");
        { std::ofstream(dir_src / "a.txt") << "a"; }
        { std::ofstream(dir_src / "sub" / "b.txt") << "b"; }

        // copy with recursive option
        fs::copy(dir_src, dir_dst, fs::copy_options::recursive);
        int count = 0;
        for (const auto& e : fs::recursive_directory_iterator(dir_dst)) {
            std::cout << "  " << e.path().filename().string() << std::endl;
            ++count;
        }
        std::cout << "Entries copied recursively: " << count << std::endl;

        // --- Show all option flags ---
        std::cout << "\n=== Available copy_options flags ===" << std::endl;
        std::cout << "none               (existing file handling)" << std::endl;
        std::cout << "skip_existing      (silently skip)" << std::endl;
        std::cout << "overwrite_existing (replace target)" << std::endl;
        std::cout << "update_existing    (replace if newer)" << std::endl;
        std::cout << "recursive          (copy directories recursively)" << std::endl;
        std::cout << "copy_symlinks      (copy symlinks as symlinks)" << std::endl;
        std::cout << "skip_symlinks      (ignore symlinks)" << std::endl;
        std::cout << "directories_only   (copy directory structure only)" << std::endl;
        std::cout << "create_symlinks    (create symlinks instead of copies)" << std::endl;
        std::cout << "create_hard_links  (create hard links instead)" << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== copy_options::none (default) ===
Copy with none: failed (File exists)

=== copy_options::skip_existing ===
Copied: 0 (false means skipped)

=== copy_options::overwrite_existing ===
Copied: 1

=== copy_options::update_existing ===
Copied: 0 (false if dest is same age or newer)

=== Directory copy options ===
  a.txt
  sub
  b.txt
Entries copied recursively: 3

=== Available copy_options flags ===
none               (existing file handling)
skip_existing      (silently skip)
overwrite_existing (replace target)
update_existing    (replace if newer)
recursive          (copy directories recursively)
copy_symlinks      (copy symlinks as symlinks)
skip_symlinks      (ignore symlinks)
directories_only   (copy directory structure only)
create_symlinks    (create symlinks instead of copies)
create_hard_links  (create hard links instead)
*/
