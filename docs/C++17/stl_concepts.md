# C++17 STL Concepts

This document covers new or evolved C++17 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++17/). Only additions or evolutions from C++98/C++03/C++11/C++14 are included.

## Containers

### std::string_view
**Explanation**: A lightweight, non-owning reference to a contiguous sequence of characters. It avoids copying strings when you only need read access, dramatically improving performance in parsing, logging, and any function that accepts string-like input.
**Real-World Scenario**: Parse HTTP headers without allocating copies of each header name and value.
**Snippet**:
```cpp
#include <string_view>
#include <iostream>

void greet(std::string_view name) {
    std::cout << "Hello, " << name << "!\n";
}

greet("world");                          // no allocation
std::string s = "Alice";
greet(s);                                // no copy
greet(std::string_view(s).substr(0, 3)); // "Ali", zero-copy substring
```
**Example**: [string_view.cpp](../examples/C++17/string_view.cpp)

### std::optional
**Explanation**: Represents a value that may or may not be present, providing a type-safe alternative to sentinel values, null pointers, or out-parameters. It makes function signatures self-documenting about the possibility of absence.
**Real-World Scenario**: Return an optional user record from a database lookup that may find no matching row.
**Snippet**:
```cpp
#include <optional>
#include <string>

std::optional<std::string> findUser(int id) {
    if (id == 1) return "Alice";
    return std::nullopt;
}

if (auto user = findUser(1); user.has_value()) {
    std::cout << "Found: " << *user << "\n";
}
```
**Example**: [optional.cpp](../examples/C++17/optional.cpp)

### std::variant
**Explanation**: A type-safe union that can hold one of several specified types at any time. Unlike raw unions, it tracks which type is active and throws `std::bad_variant_access` on incorrect access, eliminating a major source of undefined behavior.
**Real-World Scenario**: Represent different event payloads (click, keypress, resize) in a GUI framework's event system.
**Snippet**:
```cpp
#include <variant>
#include <string>

using Event = std::variant<int, double, std::string>;

Event e = "button_click";
std::visit([](const auto& val) {
    std::cout << val << "\n";
}, e);
```
**Example**: [variant.cpp](../examples/C++17/variant.cpp)

### std::any
**Explanation**: A type-safe container for single values of any type. It uses type erasure internally and provides `std::any_cast` for safe retrieval, replacing `void*` patterns with a much safer alternative.
**Real-World Scenario**: Store heterogeneous configuration values (ints, strings, booleans) in a dynamic settings registry.
**Snippet**:
```cpp
#include <any>
#include <string>

std::any config = 42;
int port = std::any_cast<int>(config);

config = std::string("localhost");
std::string host = std::any_cast<std::string>(config);
```
**Example**: [any.cpp](../examples/C++17/any.cpp)

## Filesystem Library

### std::filesystem::path
**Explanation**: Represents a filesystem path in a platform-independent way, handling separators, extensions, and parent directories. It supports concatenation, decomposition, and conversion between native and generic formats.
**Real-World Scenario**: Build output file paths from user-supplied directory and filename components in a cross-platform build tool.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::path p = "/home/user/docs";
p /= "report.txt";
std::cout << "Stem: " << p.stem() << ", Extension: " << p.extension() << "\n";
std::cout << "Parent: " << p.parent_path() << "\n";
```
**Example**: [filesystem_path.cpp](../examples/C++17/filesystem_path.cpp)

### std::filesystem::directory_entry
**Explanation**: Represents a single entry within a directory, caching file attributes (type, size, last write time) to minimize redundant OS calls when iterating over directory contents.
**Real-World Scenario**: Display file metadata (name, size, type) in a file manager application.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::directory_entry entry("/home/user/docs/report.txt");
if (entry.exists()) {
    std::cout << "Size: " << entry.file_size() << " bytes\n";
    std::cout << "Is regular file: " << entry.is_regular_file() << "\n";
}
```
**Example**: [directory_entry.cpp](../examples/C++17/directory_entry.cpp)

### std::filesystem::directory_iterator
**Explanation**: An input iterator that traverses the immediate entries of a single directory (non-recursively). It is the primary way to list files and subdirectories at one level.
**Real-World Scenario**: List all configuration files in a settings directory.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (const auto& entry : fs::directory_iterator("/etc/myapp")) {
    std::cout << entry.path().filename() << "\n";
}
```
**Example**: [directory_iterator.cpp](../examples/C++17/directory_iterator.cpp)

### std::filesystem::recursive_directory_iterator
**Explanation**: Similar to `directory_iterator` but descends into subdirectories recursively, visiting the entire directory tree beneath a given root path.
**Real-World Scenario**: Search for all `.log` files across an entire project directory tree for a log aggregation tool.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (const auto& entry : fs::recursive_directory_iterator("/var/log")) {
    if (entry.path().extension() == ".log") {
        std::cout << entry.path() << "\n";
    }
}
```
**Example**: [recursive_directory_iterator.cpp](../examples/C++17/recursive_directory_iterator.cpp)

### std::filesystem::file_status
**Explanation**: Holds the type and permissions of a file, as returned by `status()` or `symlink_status()`. It decouples the OS query from the inspection, allowing efficient batch checks.
**Real-World Scenario**: Check whether a deployment artifact is a regular file or a symlink before processing it in a CI/CD pipeline.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::file_status stat = fs::status("/usr/bin/python3");
if (stat.type() == fs::file_type::symlink) {
    std::cout << "It's a symbolic link\n";
} else if (stat.type() == fs::file_type::regular) {
    std::cout << "It's a regular file\n";
}
```
**Example**: [file_status.cpp](../examples/C++17/file_status.cpp)

### std::filesystem::space_info
**Explanation**: Holds capacity, free space, and available space for a filesystem, returned by `std::filesystem::space()`. Useful for monitoring disk usage.
**Real-World Scenario**: Check available disk space before writing a large export file to prevent out-of-space errors.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::space_info si = fs::space("/");
std::cout << "Capacity:  " << si.capacity / (1024*1024) << " MB\n";
std::cout << "Free:      " << si.free / (1024*1024) << " MB\n";
std::cout << "Available: " << si.available / (1024*1024) << " MB\n";
```
**Example**: [space_info.cpp](../examples/C++17/space_info.cpp)

### std::filesystem::file_type
**Explanation**: An enumeration that classifies filesystem entries into categories such as `regular`, `directory`, `symlink`, `block`, `character`, `fifo`, `socket`, `unknown`, and `not_found`.
**Real-World Scenario**: Route processing logic based on whether an entry is a file, directory, or symlink in a backup utility.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto type = fs::status("/tmp").type();
switch (type) {
    case fs::file_type::directory: std::cout << "Directory\n"; break;
    case fs::file_type::regular:   std::cout << "Regular file\n"; break;
    case fs::file_type::symlink:   std::cout << "Symlink\n"; break;
    default:                       std::cout << "Other\n"; break;
}
```
**Example**: [file_type.cpp](../examples/C++17/file_type.cpp)

### std::filesystem::perms
**Explanation**: A bitmask type representing POSIX-style file permissions (owner/group/others read/write/execute). Supports bitwise operations for combining and testing permission flags.
**Real-World Scenario**: Verify that a secrets file is not world-readable before loading credentials.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto p = fs::status("secrets.conf").permissions();
if ((p & fs::perms::others_read) != fs::perms::none) {
    std::cerr << "WARNING: secrets file is world-readable!\n";
}
```
**Example**: [perms.cpp](../examples/C++17/perms.cpp)

### std::filesystem::copy_options
**Explanation**: A bitmask enumeration controlling the behavior of `copy()` and `copy_file()`, such as whether to overwrite existing files, skip them, or update only if the source is newer.
**Real-World Scenario**: Implement an incremental backup that only copies files newer than the destination.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::copy_file("source.dat", "backup.dat",
              fs::copy_options::update_existing);
```
**Example**: [copy_options.cpp](../examples/C++17/copy_options.cpp)

### std::filesystem::directory_options
**Explanation**: Controls the behavior of directory iterators, such as whether to follow symlinks or skip permission-denied entries instead of throwing exceptions.
**Real-World Scenario**: Scan a directory tree while gracefully skipping folders the current user cannot access.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (const auto& entry : fs::recursive_directory_iterator(
        "/var", fs::directory_options::skip_permission_denied)) {
    std::cout << entry.path() << "\n";
}
```
**Example**: [directory_options.cpp](../examples/C++17/directory_options.cpp)

### std::filesystem::create_directory / create_directories
**Explanation**: `create_directory` creates a single directory; `create_directories` creates the entire path including all intermediate directories (like `mkdir -p`). Both return `true` if a new directory was actually created.
**Real-World Scenario**: Ensure a nested output directory exists before writing report files in a data pipeline.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::create_directory("output");
fs::create_directories("output/2025/reports/Q4");
```
**Example**: [create_directory.cpp](../examples/C++17/create_directory.cpp)

### std::filesystem::copy / copy_file
**Explanation**: `copy` copies files, directories, or symlinks with configurable options. `copy_file` is specifically for regular files and returns a boolean indicating success. Both respect `copy_options` for conflict resolution.
**Real-World Scenario**: Deploy built artifacts by copying them from a build directory to a staging area.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::copy_file("build/app.bin", "deploy/app.bin",
              fs::copy_options::overwrite_existing);

fs::copy("assets/", "deploy/assets/",
         fs::copy_options::recursive);
```
**Example**: [copy_file.cpp](../examples/C++17/copy_file.cpp)

### std::filesystem::remove / remove_all
**Explanation**: `remove` deletes a single file or empty directory. `remove_all` recursively deletes a directory and all its contents, returning the number of entries removed. Both are the C++ equivalent of `rm` and `rm -rf`.
**Real-World Scenario**: Clean up temporary build artifacts after a compilation step.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::remove("temp/build.log");
auto count = fs::remove_all("temp/build_cache");
std::cout << "Removed " << count << " entries\n";
```
**Example**: [remove.cpp](../examples/C++17/remove.cpp)

### std::filesystem::rename
**Explanation**: Atomically renames or moves a file or directory within the same filesystem. If the destination exists and is a file, it is replaced; if it is a non-empty directory, an error is reported.
**Real-World Scenario**: Atomically swap a newly written configuration file into place to avoid partial reads.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

// Write to a temp file, then atomically rename
fs::rename("config.tmp", "config.json");
```
**Example**: [rename.cpp](../examples/C++17/rename.cpp)

### std::filesystem::resize_file
**Explanation**: Changes the size of a regular file. If the new size is larger, the file is extended with zero bytes; if smaller, the file is truncated. Useful for pre-allocating file space or cleaning up logs.
**Real-World Scenario**: Truncate a log file to zero bytes during log rotation without deleting and recreating it.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::resize_file("application.log", 0);  // truncate to empty
```
**Example**: [resize_file.cpp](../examples/C++17/resize_file.cpp)

### std::filesystem::space
**Explanation**: Queries the filesystem for capacity, free space, and available space at a given path, returning a `space_info` struct. Available space may be less than free space due to filesystem quotas.
**Real-World Scenario**: Display a disk usage summary in a system monitoring dashboard.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto info = fs::space("/data");
double usedPercent = 100.0 * (1.0 - static_cast<double>(info.available) / info.capacity);
std::cout << "Disk usage: " << usedPercent << "%\n";
```
**Example**: [space.cpp](../examples/C++17/space.cpp)

### std::filesystem::last_write_time
**Explanation**: Gets or sets the last modification time of a file. Returns a `file_time_type` that can be compared or converted. The setter form allows touching files or restoring timestamps during backup operations.
**Real-World Scenario**: Compare file modification times to determine whether a cached result is stale.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto sourceTime = fs::last_write_time("source.cpp");
auto objectTime = fs::last_write_time("source.o");
if (sourceTime > objectTime) {
    std::cout << "Source is newer; recompilation needed\n";
}
```
**Example**: [last_write_time.cpp](../examples/C++17/last_write_time.cpp)

### std::filesystem::permissions
**Explanation**: Modifies the permissions of a file or directory. Supports adding, removing, or replacing permissions using `perm_options` flags (`replace`, `add`, `remove`).
**Real-World Scenario**: Make a generated script executable after writing it to disk.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::permissions("deploy.sh",
    fs::perms::owner_exec | fs::perms::group_exec,
    fs::perm_options::add);
```
**Example**: [permissions.cpp](../examples/C++17/permissions.cpp)

### std::filesystem::current_path
**Explanation**: Retrieves or changes the current working directory for the process. The getter returns the absolute path; the setter changes the working directory.
**Real-World Scenario**: Save and restore the working directory when a library function temporarily changes it.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto original = fs::current_path();
fs::current_path("/tmp");
// ... perform operations ...
fs::current_path(original);  // restore
```
**Example**: [current_path.cpp](../examples/C++17/current_path.cpp)

### std::filesystem::temp_directory_path
**Explanation**: Returns the path to the system's temporary directory (e.g., `/tmp` on POSIX, `%TEMP%` on Windows), suitable for creating temporary files without hardcoding platform-specific paths.
**Real-World Scenario**: Create a temporary working directory for intermediate build artifacts.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto tmpDir = fs::temp_directory_path() / "myapp_build";
fs::create_directories(tmpDir);
std::cout << "Working in: " << tmpDir << "\n";
```
**Example**: [temp_directory_path.cpp](../examples/C++17/temp_directory_path.cpp)

### std::filesystem::exists
**Explanation**: Checks whether a file or directory exists at the given path. It is a simple boolean query that does not throw on permission errors when used with the error-code overload.
**Real-World Scenario**: Verify that a required configuration file is present before starting an application.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

if (!fs::exists("config.yaml")) {
    std::cerr << "Missing config.yaml, using defaults\n";
}
```
**Example**: [exists.cpp](../examples/C++17/exists.cpp)

### std::filesystem::is_directory
**Explanation**: Returns `true` if the given path refers to a directory. Useful for validating user-supplied paths before attempting directory-specific operations.
**Real-World Scenario**: Validate that a user-provided output path is a directory before writing multiple files into it.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

if (fs::is_directory(outputPath)) {
    // write files into the directory
} else {
    std::cerr << outputPath << " is not a directory\n";
}
```
**Example**: [is_directory.cpp](../examples/C++17/is_directory.cpp)

### std::filesystem::is_regular_file
**Explanation**: Returns `true` if the given path refers to a regular file (not a directory, symlink, or special file). Essential for safely opening files for reading.
**Real-World Scenario**: Filter out non-file entries when processing a list of paths provided by the user.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (const auto& entry : fs::directory_iterator(".")) {
    if (fs::is_regular_file(entry)) {
        std::cout << "File: " << entry.path().filename() << "\n";
    }
}
```
**Example**: [is_regular_file.cpp](../examples/C++17/is_regular_file.cpp)

### std::filesystem::is_symlink
**Explanation**: Returns `true` if the given path is a symbolic link, without following it. This allows code to detect and handle symlinks differently from regular files or directories.
**Real-World Scenario**: Skip symbolic links during a backup to avoid duplicating data that is already backed up via its canonical path.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

if (fs::is_symlink("/usr/bin/python")) {
    auto target = fs::read_symlink("/usr/bin/python");
    std::cout << "Symlink -> " << target << "\n";
}
```
**Example**: [is_symlink.cpp](../examples/C++17/is_symlink.cpp)

### std::filesystem::file_size
**Explanation**: Returns the size of a regular file in bytes. Throws `filesystem_error` if the path does not refer to a regular file, or use the error-code overload for non-throwing behavior.
**Real-World Scenario**: Check file sizes before uploading to enforce a maximum upload limit.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto size = fs::file_size("upload.zip");
if (size > 100 * 1024 * 1024) {
    std::cerr << "File exceeds 100 MB upload limit\n";
}
```
**Example**: [file_size.cpp](../examples/C++17/file_size.cpp)

### std::filesystem::hard_link_count
**Explanation**: Returns the number of hard links to the given file. A count greater than one means the file has multiple directory entries pointing to the same inode.
**Real-World Scenario**: Detect files with multiple hard links in a deduplication tool to avoid counting storage twice.
**Snippet**:
```cpp
#include <filesystem>
namespace fs = std::filesystem;

auto count = fs::hard_link_count("data.bin");
if (count > 1) {
    std::cout << "File has " << count << " hard links\n";
}
```
**Example**: [hard_link_count.cpp](../examples/C++17/hard_link_count.cpp)

## Algorithms

### std::sample
**Explanation**: Randomly selects `n` elements from an input range and writes them to an output iterator, using a uniform random number generator. The relative order of selected elements is preserved.
**Real-World Scenario**: Select a random subset of users for A/B testing from a user database.
**Snippet**:
```cpp
#include <algorithm>
#include <random>
#include <vector>

std::vector<int> population = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::vector<int> sample(3);

std::sample(population.begin(), population.end(),
            sample.begin(), 3, std::mt19937{std::random_device{}()});
```
**Example**: [sample.cpp](../examples/C++17/sample.cpp)

### std::for_each_n
**Explanation**: Applies a function to exactly the first `n` elements of a range, returning an iterator past the last processed element. It is safer than manually computing an end iterator for partial range operations.
**Real-World Scenario**: Process the first `n` highest-priority tasks from a sorted task queue.
**Snippet**:
```cpp
#include <algorithm>
#include <vector>

std::vector<int> tasks = {10, 20, 30, 40, 50};
std::for_each_n(tasks.begin(), 3, [](int& t) {
    std::cout << "Processing task " << t << "\n";
});
```
**Example**: [for_each_n.cpp](../examples/C++17/for_each_n.cpp)

### std::reduce
**Explanation**: Generalized reduction over a range, similar to `std::accumulate` but with relaxed ordering requirements that permit parallel execution. The binary operation must be associative and commutative for correct parallel results.
**Real-World Scenario**: Compute the total revenue from a large sales dataset using parallel reduction.
**Snippet**:
```cpp
#include <numeric>
#include <vector>
#include <execution>

std::vector<double> sales = {1200.50, 3400.75, 890.25, 5600.00};
double total = std::reduce(std::execution::par, sales.begin(), sales.end(), 0.0);
```
**Example**: [reduce.cpp](../examples/C++17/reduce.cpp)

### std::transform_reduce
**Explanation**: Combines a transformation and a reduction into a single operation, supporting parallel execution. It is the parallel-friendly equivalent of a map-reduce pattern.
**Real-World Scenario**: Compute the dot product of two vectors in a machine learning library.
**Snippet**:
```cpp
#include <numeric>
#include <vector>

std::vector<double> a = {1.0, 2.0, 3.0};
std::vector<double> b = {4.0, 5.0, 6.0};
double dot = std::transform_reduce(a.begin(), a.end(), b.begin(), 0.0);
// 1*4 + 2*5 + 3*6 = 32.0
```
**Example**: [transform_reduce.cpp](../examples/C++17/transform_reduce.cpp)

### std::inclusive_scan
**Explanation**: Computes a running total (prefix sum) where each output element includes the corresponding input element. Supports parallel execution and custom binary operations.
**Real-World Scenario**: Generate cumulative page view counts for a real-time analytics dashboard.
**Snippet**:
```cpp
#include <numeric>
#include <vector>

std::vector<int> daily = {100, 150, 200, 80};
std::vector<int> cumulative(daily.size());
std::inclusive_scan(daily.begin(), daily.end(), cumulative.begin());
// cumulative: {100, 250, 450, 530}
```
**Example**: [inclusive_scan.cpp](../examples/C++17/inclusive_scan.cpp)

### std::exclusive_scan
**Explanation**: Computes a prefix sum where each output element excludes the corresponding input element (shifted by one position). The first element of the output is the identity value. Supports parallel execution.
**Real-World Scenario**: Calculate offset positions for variable-length records in a binary file format.
**Snippet**:
```cpp
#include <numeric>
#include <vector>

std::vector<int> sizes = {10, 20, 30, 40};
std::vector<int> offsets(sizes.size());
std::exclusive_scan(sizes.begin(), sizes.end(), offsets.begin(), 0);
// offsets: {0, 10, 30, 60}
```
**Example**: [exclusive_scan.cpp](../examples/C++17/exclusive_scan.cpp)

### std::transform_inclusive_scan
**Explanation**: Applies a unary transformation to each element and then computes an inclusive prefix sum of the transformed values. Supports parallel execution for large datasets.
**Real-World Scenario**: Compute cumulative squared distances for a GPS trajectory analysis tool.
**Snippet**:
```cpp
#include <numeric>
#include <vector>

std::vector<int> values = {1, 2, 3, 4};
std::vector<int> result(values.size());
std::transform_inclusive_scan(values.begin(), values.end(), result.begin(),
    std::plus<>{}, [](int x) { return x * x; });
// result: {1, 5, 14, 30}  (1, 1+4, 1+4+9, 1+4+9+16)
```
**Example**: [transform_inclusive_scan.cpp](../examples/C++17/transform_inclusive_scan.cpp)

### std::transform_exclusive_scan
**Explanation**: Applies a unary transformation to each element and computes an exclusive prefix sum (shifted by one, starting with the identity). Supports parallel execution.
**Real-World Scenario**: Compute memory offsets for a list of objects where each object's serialized size must be squared for alignment purposes.
**Snippet**:
```cpp
#include <numeric>
#include <vector>

std::vector<int> values = {1, 2, 3, 4};
std::vector<int> result(values.size());
std::transform_exclusive_scan(values.begin(), values.end(), result.begin(),
    0, std::plus<>{}, [](int x) { return x * x; });
// result: {0, 1, 5, 14}  (0, 0+1, 0+1+4, 0+1+4+9)
```
**Example**: [transform_exclusive_scan.cpp](../examples/C++17/transform_exclusive_scan.cpp)

### Parallel Algorithms (std::execution::seq / par / par_unseq)
**Explanation**: C++17 adds execution policies to over 60 existing STL algorithms (sort, for_each, transform, find, count, etc.). `seq` runs sequentially, `par` allows parallel execution across threads, and `par_unseq` additionally allows vectorized (SIMD) execution within threads.
**Real-World Scenario**: Sort a multi-million-row dataset in a data analytics pipeline using all available CPU cores.
**Snippet**:
```cpp
#include <algorithm>
#include <execution>
#include <vector>

std::vector<int> data(10'000'000);
// ... fill data ...

std::sort(std::execution::par, data.begin(), data.end());
auto it = std::find(std::execution::par, data.begin(), data.end(), 42);
std::for_each(std::execution::par_unseq, data.begin(), data.end(),
              [](int& x) { x *= 2; });
```
**Example**: [parallel_algorithms.cpp](../examples/C++17/parallel_algorithms.cpp)

## Utilities

### std::byte
**Explanation**: A distinct type for raw byte manipulation that does not implicitly convert to or from integer types. It supports only bitwise operations, preventing accidental arithmetic on raw data and improving type safety in low-level code.
**Real-World Scenario**: Parse binary network protocol packets where each byte has a specific meaning.
**Snippet**:
```cpp
#include <cstddef>

std::byte b{0xAB};
std::byte mask{0x0F};
std::byte low = b & mask;     // 0x0B
int value = std::to_integer<int>(low);  // 11
```
**Example**: [byte.cpp](../examples/C++17/byte.cpp)

### std::apply
**Explanation**: Calls a callable with the elements of a tuple unpacked as individual arguments. It bridges tuple-based data and function-call interfaces, making it easy to forward stored arguments.
**Real-World Scenario**: Invoke a database query function with parameters stored as a tuple from a prepared statement cache.
**Snippet**:
```cpp
#include <tuple>
#include <functional>

auto args = std::make_tuple(std::string("users"), 42, true);
auto result = std::apply([](const std::string& table, int id, bool active) {
    return table + " WHERE id=" + std::to_string(id);
}, args);
```
**Example**: [apply.cpp](../examples/C++17/apply.cpp)

### std::invoke
**Explanation**: A uniform calling mechanism that works with regular functions, member functions, member data pointers, and any callable object. It eliminates the need for separate calling conventions in generic code.
**Real-World Scenario**: Build a generic task scheduler that can invoke any callable -- free functions, lambdas, or member functions -- without special-casing.
**Snippet**:
```cpp
#include <functional>

struct Printer {
    void print(int x) { std::cout << x << "\n"; }
};

Printer p;
std::invoke(&Printer::print, p, 42);       // member function
std::invoke([](int x) { return x * 2; }, 5); // lambda
std::invoke(std::plus<>{}, 3, 4);           // function object
```
**Example**: [invoke.cpp](../examples/C++17/invoke.cpp)

### std::is_invocable / std::is_invocable_r
**Explanation**: Type traits that check at compile time whether a callable can be invoked with given argument types (`is_invocable`) and additionally whether the return type is convertible to a specified type (`is_invocable_r`). They are essential for writing robust SFINAE-based generic code.
**Real-World Scenario**: Constrain a callback registration function to only accept callables with the correct signature.
**Snippet**:
```cpp
#include <type_traits>

static_assert(std::is_invocable_v<decltype(std::sqrt), double>);
static_assert(std::is_invocable_r_v<double, decltype(std::sqrt), double>);

template<typename Func>
auto safeCall(Func f, int x) -> std::enable_if_t<std::is_invocable_r_v<int, Func, int>, int> {
    return std::invoke(f, x);
}
```
**Example**: [is_invocable.cpp](../examples/C++17/is_invocable.cpp)

### std::invoke_result
**Explanation**: A type trait that deduces the return type of invoking a callable with given argument types. It replaces the deprecated `std::result_of` with a cleaner interface that does not require wrapping the callable in a function signature.
**Real-World Scenario**: Deduce the return type of a user-supplied transformation function in a pipeline builder.
**Snippet**:
```cpp
#include <type_traits>

auto square = [](int x) { return x * x; };
using ResultType = std::invoke_result_t<decltype(square), int>;
static_assert(std::is_same_v<ResultType, int>);
```
**Example**: [invoke_result.cpp](../examples/C++17/invoke_result.cpp)

### std::is_swappable / std::is_nothrow_swappable
**Explanation**: Type traits that check whether a type can be swapped with `std::swap` (`is_swappable`) and whether that swap is guaranteed not to throw (`is_nothrow_swappable`). These enable conditional noexcept specifications and better container optimizations.
**Real-World Scenario**: Write a generic container that provides a strong exception guarantee by checking whether its element type can be swapped without throwing.
**Snippet**:
```cpp
#include <type_traits>
#include <string>

static_assert(std::is_swappable_v<int>);
static_assert(std::is_nothrow_swappable_v<int>);
static_assert(std::is_swappable_v<std::string>);

template<typename T>
void optimizedSwap(T& a, T& b) noexcept(std::is_nothrow_swappable_v<T>) {
    std::swap(a, b);
}
```
**Example**: [is_swappable.cpp](../examples/C++17/is_swappable.cpp)

### std::void_t
**Explanation**: A simple but powerful metaprogramming utility that maps any sequence of types to `void`. Its primary purpose is enabling SFINAE-based detection of valid expressions, type members, or nested types in template specializations.
**Real-World Scenario**: Detect whether a type has a `serialize()` member function to choose between custom and default serialization in a framework.
**Snippet**:
```cpp
#include <type_traits>

// Primary template: type does not have a .size() method
template<typename T, typename = void>
struct has_size : std::false_type {};

// Specialization: enabled only if T has a .size() method
template<typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};

static_assert(has_size<std::vector<int>>::value);
static_assert(!has_size<int>::value);
```
**Example**: [void_t.cpp](../examples/C++17/void_t.cpp)

### std::bool_constant
**Explanation**: An alias template for `std::integral_constant<bool, B>`, providing a shorter way to define compile-time boolean constants. `std::true_type` and `std::false_type` are specializations of it.
**Real-World Scenario**: Define custom type traits that produce clean true/false compile-time values for a serialization framework.
**Snippet**:
```cpp
#include <type_traits>

template<typename T>
using is_small = std::bool_constant<(sizeof(T) <= sizeof(void*))>;

static_assert(is_small<int>::value);
static_assert(!is_small<std::array<int, 100>>::value);
```
**Example**: [bool_constant.cpp](../examples/C++17/bool_constant.cpp)

### std::conjunction / std::disjunction / std::negation
**Explanation**: Logical metafunctions that perform short-circuit AND (`conjunction`), OR (`disjunction`), and NOT (`negation`) on type traits. They short-circuit instantiation, improving compile times and enabling better error messages compared to fold expressions over traits.
**Real-World Scenario**: Constrain a variadic function template to accept only arguments that are all arithmetic and all nothrow-copyable.
**Snippet**:
```cpp
#include <type_traits>

template<typename... Ts>
using all_arithmetic = std::conjunction<std::is_arithmetic<Ts>...>;

template<typename T>
using not_pointer = std::negation<std::is_pointer<T>>;

template<typename... Ts>
using any_floating = std::disjunction<std::is_floating_point<Ts>...>;

static_assert(all_arithmetic<int, float, double>::value);
static_assert(not_pointer<int>::value);
static_assert(any_floating<int, double, char>::value);
```
**Example**: [logical_traits.cpp](../examples/C++17/logical_traits.cpp)

### std::clamp
**Explanation**: Constrains a value to lie within a specified minimum and maximum range. If the value is below the minimum, the minimum is returned; if above the maximum, the maximum is returned; otherwise the value itself is returned.
**Real-World Scenario**: Clamp pixel color values to the valid 0-255 range in an image processing pipeline.
**Snippet**:
```cpp
#include <algorithm>

int brightness = 280;
int clamped = std::clamp(brightness, 0, 255);  // 255

double temperature = -5.0;
double safe = std::clamp(temperature, 0.0, 100.0);  // 0.0
```
**Example**: [clamp.cpp](../examples/C++17/clamp.cpp)

### std::from_chars / std::to_chars
**Explanation**: High-performance, locale-independent functions for converting between numeric values and character strings. They do not allocate memory, do not throw exceptions, and are significantly faster than `std::stoi`, `std::to_string`, or streams.
**Real-World Scenario**: Parse millions of numeric values from a CSV file in a high-frequency trading data loader.
**Snippet**:
```cpp
#include <charconv>
#include <string_view>

// String to number
std::string_view sv = "314159";
int value = 0;
auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);

// Number to string
char buffer[32];
auto [end, ec2] = std::to_chars(buffer, buffer + sizeof(buffer), 42);
std::string_view result(buffer, end - buffer);  // "42"
```
**Example**: [from_to_chars.cpp](../examples/C++17/from_to_chars.cpp)

### std::not_fn
**Explanation**: Creates a callable that negates the result of a given callable. It is a generalized replacement for `std::not1` and `std::not2`, working with any callable without requiring adaptor base classes.
**Real-World Scenario**: Filter out elements that do not match a predicate when composing algorithm chains.
**Snippet**:
```cpp
#include <functional>
#include <algorithm>
#include <vector>

auto isEven = [](int x) { return x % 2 == 0; };
auto isOdd = std::not_fn(isEven);

std::vector<int> nums = {1, 2, 3, 4, 5, 6};
auto count = std::count_if(nums.begin(), nums.end(), isOdd);  // 3
```
**Example**: [not_fn.cpp](../examples/C++17/not_fn.cpp)

### std::gcd / std::lcm
**Explanation**: Compute the greatest common divisor and least common multiple of two integers, respectively. Both handle negative values and zero correctly according to mathematical conventions.
**Real-World Scenario**: Simplify fractions in a rational number library or compute scheduling intervals that align multiple periodic tasks.
**Snippet**:
```cpp
#include <numeric>

int g = std::gcd(24, 36);   // 12
int l = std::lcm(4, 6);     // 12

// Simplify a fraction
int num = 18, den = 24;
int d = std::gcd(num, den);
std::cout << num/d << "/" << den/d << "\n";  // 3/4
```
**Example**: [gcd_lcm.cpp](../examples/C++17/gcd_lcm.cpp)

### std::as_const
**Explanation**: Returns a `const` reference to its argument, useful for forcing const overload selection without writing a verbose `static_cast<const T&>`. This is particularly handy when passing objects to templates that should not modify them.
**Real-World Scenario**: Pass a container to a function template ensuring the const overload of `begin()`/`end()` is selected for thread-safe iteration.
**Snippet**:
```cpp
#include <utility>
#include <vector>

std::vector<int> data = {1, 2, 3};

// Forces use of const overloads
for (auto& val : std::as_const(data)) {
    // val is const int& -- cannot be modified
    std::cout << val << " ";
}
```
**Example**: [as_const.cpp](../examples/C++17/as_const.cpp)

### std::make_from_tuple
**Explanation**: Constructs an object of type `T` by unpacking a tuple as constructor arguments. It is the construction counterpart of `std::apply`, enabling factory patterns that store constructor arguments as tuples.
**Real-World Scenario**: Implement a deferred object factory that stores construction parameters and creates objects on demand.
**Snippet**:
```cpp
#include <tuple>

struct Connection {
    std::string host;
    int port;
    Connection(std::string h, int p) : host(std::move(h)), port(p) {}
};

auto args = std::make_tuple(std::string("localhost"), 8080);
auto conn = std::make_from_tuple<Connection>(args);
```
**Example**: [make_from_tuple.cpp](../examples/C++17/make_from_tuple.cpp)

### std::has_unique_object_representations
**Explanation**: A type trait that checks whether a type's value representation uses all of its object representation bits (no padding). Types satisfying this can be safely compared byte-by-byte using `memcmp` and hashed with `memcpy`-based hash functions.
**Real-World Scenario**: Enable a fast byte-level hash for types that are guaranteed to have no padding, in a high-performance hash map.
**Snippet**:
```cpp
#include <type_traits>

struct Packed { int x; int y; };
struct Padded { char a; int b; };  // likely has padding

static_assert(std::has_unique_object_representations_v<int>);
// Padded may or may not satisfy this -- implementation-defined
```
**Example**: [has_unique_object_representations.cpp](../examples/C++17/has_unique_object_representations.cpp)

### std::is_aggregate
**Explanation**: A type trait that checks whether a type is an aggregate (an array or a class with no user-declared constructors, no private/protected non-static data members, no virtual functions, and no virtual base classes). Useful for enabling aggregate-specific initialization logic in generic code.
**Real-World Scenario**: Dispatch to aggregate initialization or constructor-based initialization in a generic deserialization framework.
**Snippet**:
```cpp
#include <type_traits>

struct Agg { int x; double y; };
class NonAgg { int x; public: NonAgg(int v) : x(v) {} };

static_assert(std::is_aggregate_v<Agg>);
static_assert(!std::is_aggregate_v<NonAgg>);
```
**Example**: [is_aggregate.cpp](../examples/C++17/is_aggregate.cpp)

### hardware_destructive_interference_size / hardware_constructive_interference_size
**Explanation**: Compile-time constants representing the minimum offset to avoid false sharing (`hardware_destructive_interference_size`, typically a cache line size) and the maximum size for promoting true sharing (`hardware_constructive_interference_size`). These allow writing portable, cache-friendly concurrent data structures.
**Real-World Scenario**: Align per-thread counters to avoid false sharing in a high-throughput concurrent counter array.
**Snippet**:
```cpp
#include <new>

struct alignas(std::hardware_destructive_interference_size) AlignedCounter {
    std::atomic<int> value{0};
};

// Array of counters, each on its own cache line to avoid false sharing
AlignedCounter perThreadCounters[8];
```
**Example**: [interference_sizes.cpp](../examples/C++17/interference_sizes.cpp)

## Polymorphic Memory Resources (PMR)

### std::pmr::memory_resource
**Explanation**: An abstract base class defining the interface for custom memory allocators. It provides `allocate()`, `deallocate()`, and `is_equal()` virtual functions, decoupling allocation strategy from container types and enabling runtime-configurable allocators.
**Real-World Scenario**: Define a logging allocator that tracks every allocation for debugging memory usage in a server application.
**Snippet**:
```cpp
#include <memory_resource>

class LoggingResource : public std::pmr::memory_resource {
    void* do_allocate(size_t bytes, size_t align) override {
        std::cout << "Allocating " << bytes << " bytes\n";
        return std::pmr::get_default_resource()->allocate(bytes, align);
    }
    void do_deallocate(void* p, size_t bytes, size_t align) override {
        std::pmr::get_default_resource()->deallocate(p, bytes, align);
    }
    bool do_is_equal(const memory_resource& other) const noexcept override {
        return this == &other;
    }
};
```
**Example**: [memory_resource.cpp](../examples/C++17/memory_resource.cpp)

### std::pmr::polymorphic_allocator
**Explanation**: A type-erased allocator that wraps a `memory_resource` pointer, allowing different containers to use different allocation strategies without changing their type. All `std::pmr::` containers use this allocator.
**Real-World Scenario**: Pass different memory resources to the same vector type in a game engine, using arena allocation for frames and heap allocation for persistent data.
**Snippet**:
```cpp
#include <memory_resource>
#include <vector>

std::pmr::monotonic_buffer_resource pool;
std::pmr::vector<int> frameData(&pool);     // arena-allocated
std::pmr::vector<int> persistentData;        // default-allocated

frameData.push_back(42);
```
**Example**: [polymorphic_allocator.cpp](../examples/C++17/polymorphic_allocator.cpp)

### std::pmr::monotonic_buffer_resource
**Explanation**: A fast memory resource that allocates from a contiguous buffer and never frees individual allocations. Memory is released all at once when the resource is destroyed. This is ideal for short-lived, bump-allocator workloads.
**Real-World Scenario**: Allocate all temporary objects for a single frame in a game engine, then discard them all at frame end.
**Snippet**:
```cpp
#include <memory_resource>
#include <vector>

char buffer[4096];
std::pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));
std::pmr::vector<std::string> names(&pool);
names.emplace_back("Alice");
names.emplace_back("Bob");
// All memory freed when 'pool' goes out of scope
```
**Example**: [monotonic_buffer_resource.cpp](../examples/C++17/monotonic_buffer_resource.cpp)

### std::pmr::unsynchronized_pool_resource
**Explanation**: A pool-based memory resource optimized for single-threaded use. It maintains pools of different block sizes and can reuse freed blocks, providing a good balance between allocation speed and memory reuse without synchronization overhead.
**Real-World Scenario**: Manage frequent allocations and deallocations of variable-sized objects in a single-threaded event processing loop.
**Snippet**:
```cpp
#include <memory_resource>
#include <list>

std::pmr::unsynchronized_pool_resource pool;
std::pmr::list<int> events(&pool);
events.push_back(1);
events.push_back(2);
events.pop_front();  // block is returned to the pool for reuse
events.push_back(3); // may reuse the freed block
```
**Example**: [unsynchronized_pool_resource.cpp](../examples/C++17/unsynchronized_pool_resource.cpp)

### std::pmr::synchronized_pool_resource
**Explanation**: A thread-safe variant of `unsynchronized_pool_resource` that uses internal synchronization to allow concurrent allocations from multiple threads. It provides pool-based allocation with per-thread caching for reduced contention.
**Real-World Scenario**: Share a pool allocator across worker threads in a multi-threaded request handler.
**Snippet**:
```cpp
#include <memory_resource>
#include <vector>
#include <thread>

std::pmr::synchronized_pool_resource pool;

void worker() {
    std::pmr::vector<int> data(&pool);
    for (int i = 0; i < 1000; ++i) data.push_back(i);
}

std::thread t1(worker), t2(worker);
t1.join(); t2.join();
```
**Example**: [synchronized_pool_resource.cpp](../examples/C++17/synchronized_pool_resource.cpp)

## Container Improvements

### std::map::try_emplace / insert_or_assign
**Explanation**: `try_emplace` constructs a value in-place only if the key does not already exist, avoiding unnecessary construction and move operations. `insert_or_assign` inserts a new element or updates an existing one, always assigning the value regardless of whether the key was present.
**Real-World Scenario**: Maintain a user session cache where new sessions are created on first visit and existing sessions are updated on subsequent visits.
**Snippet**:
```cpp
#include <map>
#include <string>

std::map<int, std::string> sessions;

// Only constructs the string if key 1 doesn't exist
sessions.try_emplace(1, "new_session_token");

// Inserts or updates -- always sets the value
sessions.insert_or_assign(1, "refreshed_token");
```
**Example**: [map_try_emplace.cpp](../examples/C++17/map_try_emplace.cpp)

### std::unordered_map::try_emplace / insert_or_assign
**Explanation**: The same `try_emplace` and `insert_or_assign` operations available for `std::unordered_map`, providing efficient in-place construction and unconditional assignment for hash-based containers.
**Real-World Scenario**: Manage a DNS cache where lookups insert new entries or refresh existing ones.
**Snippet**:
```cpp
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> dnsCache;

dnsCache.try_emplace("example.com", "93.184.216.34");
dnsCache.insert_or_assign("example.com", "93.184.216.35");
```
**Example**: [unordered_map_try_emplace.cpp](../examples/C++17/unordered_map_try_emplace.cpp)

### Node Handle API
**Explanation**: Provides the ability to extract, modify, and reinsert nodes from associative and unordered containers without copying or moving the element's value. The `extract()` method returns an owning node handle, and `insert()` accepts node handles from compatible containers.
**Real-World Scenario**: Transfer user records between an active-users map and an archived-users map without copying large value objects.
**Snippet**:
```cpp
#include <map>
#include <string>

std::map<int, std::string> active = {{1, "Alice"}, {2, "Bob"}};
std::map<int, std::string> archived;

// Move node from active to archived without copying the string
auto node = active.extract(1);
archived.insert(std::move(node));
// active: {2, "Bob"}, archived: {1, "Alice"}
```
**Example**: [node_handle.cpp](../examples/C++17/node_handle.cpp)

## Threading

### std::shared_mutex
**Explanation**: A mutex that supports both exclusive (write) and shared (read) locking. Multiple threads can hold a shared lock simultaneously for read access, but exclusive locks block all other access. This enables the classic readers-writer lock pattern.
**Real-World Scenario**: Protect a configuration store that is read frequently by many threads but updated rarely by an admin thread.
**Snippet**:
```cpp
#include <shared_mutex>
#include <map>
#include <string>

std::shared_mutex rwMutex;
std::map<std::string, int> config;

void readConfig(const std::string& key) {
    std::shared_lock lock(rwMutex);  // shared (read) access
    auto it = config.find(key);
}

void writeConfig(const std::string& key, int value) {
    std::unique_lock lock(rwMutex);  // exclusive (write) access
    config[key] = value;
}
```
**Example**: [shared_mutex.cpp](../examples/C++17/shared_mutex.cpp)

### std::scoped_lock
**Explanation**: Locks one or more mutexes simultaneously using a deadlock-avoidance algorithm, and releases them all when destroyed. It is a variadic improvement over `std::lock_guard` that eliminates the need to manually call `std::lock` followed by adopting lock guards.
**Real-World Scenario**: Transfer funds between two bank accounts, locking both account mutexes without risk of deadlock.
**Snippet**:
```cpp
#include <mutex>

struct Account {
    std::mutex mtx;
    double balance = 0.0;
};

void transfer(Account& from, Account& to, double amount) {
    std::scoped_lock lock(from.mtx, to.mtx);  // deadlock-free
    from.balance -= amount;
    to.balance += amount;
}
```
**Example**: [scoped_lock.cpp](../examples/C++17/scoped_lock.cpp)
