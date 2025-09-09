# C++23 STL Concepts

This document covers new or evolved C++23 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++23/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17/C++20 are included.

## Containers
### std::flat_map (C++23 Addition)
**Explanation**: A sorted, contiguous key-value container with flat storage for efficiency.  
**Real-World Scenario**: Store game settings with fast lookup in a performance-critical system.  
**Snippet**:  
```cpp
#include <flat_map> std::flat_map<int, std::string> fm = {{1, "one"}};
```
**Example**: [flat_map.cpp](../examples/C++23/flat_map.cpp)

### std::flat_set (C++23 Addition)
**Explanation**: A sorted, contiguous set container for efficient storage and lookup.  
**Real-World Scenario**: Store unique player IDs in a game with minimal memory overhead.  
**Snippet**:  
```cpp
#include <flat_set> std::flat_set<int> fs = {1, 2, 3};
```
**Example**: [flat_set.cpp](../examples/C++23/flat_set.cpp)

### std::mdspan (C++23 Addition)
**Explanation**: Multidimensional array view for accessing data with dynamic extents.  
**Real-World Scenario**: Process a 2D grid in a scientific simulation without copying.  
**Snippet**:  
```cpp
#include <mdspan> std::mdspan<int, std::extents<size_t, 2, 2>> ms(data);
```
**Example**: [mdspan.cpp](../examples/C++23/mdspan.cpp)

### std::generator (C++23 Addition)
**Explanation**: Coroutine-based range for lazy generation of sequences.  
**Real-World Scenario**: Generate game events on-demand in a simulation.  
**Snippet**:  
```cpp
#include <generator> std::generator<int> gen() { for (int i = 0; i < 5; ++i) co_yield i; }
```
**Example**: [generator.cpp](../examples/C++23/generator.cpp)

## Range Views
### std::ranges::zip_view (C++23 Addition)
**Explanation**: View that combines multiple ranges into tuples of corresponding elements.  
**Real-World Scenario**: Pair player names and scores in a leaderboard.  
**Snippet**:  
```cpp
#include <ranges> auto zv = std::ranges::zip_view(names, scores);
```
**Example**: [ranges_zip_view.cpp](../examples/C++23/ranges_zip_view.cpp)

### std::ranges::zip_transform_view (C++23 Addition)
**Explanation**: View that applies a function to zipped range elements.  
**Real-World Scenario**: Compute weighted scores from paired data in a game.  
**Snippet**:  
```cpp
#include <ranges> auto ztv = std::ranges::zip_transform_view([](int x, int y) { return x + y; }, vec1, vec2);
```
**Example**: [ranges_zip_transform_view.cpp](../examples/C++23/ranges_zip_transform_view.cpp)

### std::ranges::adjacent_view (C++23 Addition)
**Explanation**: View that yields adjacent element pairs from a range.  
**Real-World Scenario**: Process consecutive frames in a video stream.  
**Snippet**:  
```cpp
#include <ranges> auto av = std::ranges::adjacent_view<2>(vec);
```
**Example**: [ranges_adjacent_view.cpp](../examples/C++23/ranges_adjacent_view.cpp)

### std::ranges::adjacent_transform_view (C++23 Addition)
**Explanation**: View that applies a function to adjacent element pairs.  
**Real-World Scenario**: Compute differences between consecutive sensor readings.  
**Snippet**:  
```cpp
#include <ranges> auto atv = std::ranges::adjacent_transform_view<2>(vec, [](int a, int b) { return b - a; });
```
**Example**: [ranges_adjacent_transform_view.cpp](../examples/C++23/ranges_adjacent_transform_view.cpp)

### std::ranges::chunk_view (C++23 Addition)
**Explanation**: View that splits a range into chunks of fixed size.  
**Real-World Scenario**: Process data in fixed-size batches for a network packet.  
**Snippet**:  
```cpp
#include <ranges> auto cv = std::ranges::chunk_view(vec, 3);
```
**Example**: [ranges_chunk_view.cpp](../examples/C++23/ranges_chunk_view.cpp)

### std::ranges::chunk_by_view (C++23 Addition)
**Explanation**: View that splits a range into chunks based on a predicate.  
**Real-World Scenario**: Group log entries by timestamp in a logger.  
**Snippet**:  
```cpp
#include <ranges> auto cbv = std::ranges::chunk_by_view(vec, [](int a, int b) { return a <= b; });
```
**Example**: [ranges_chunk_by_view.cpp](../examples/C++23/ranges_chunk_by_view.cpp)

### std::ranges::slide_view (C++23 Addition)
**Explanation**: View that yields sliding windows of a fixed size from a range.  
**Real-World Scenario**: Compute moving averages in a financial dataset.  
**Snippet**:  
```cpp
#include <ranges> auto sv = std::ranges::slide_view(vec, 3);
```
**Example**: [ranges_slide_view.cpp](../examples/C++23/ranges_slide_view.cpp)

### std::ranges::stride_view (C++23 Addition)
**Explanation**: View that yields every nth element from a range.  
**Real-World Scenario**: Sample every nth frame in a video analysis.  
**Snippet**:  
```cpp
#include <ranges> auto sv = std::ranges::stride_view(vec, 2);
```
**Example**: [ranges_stride_view.cpp](../examples/C++23/ranges_stride_view.cpp)

### std::ranges::cartesian_product_view (C++23 Addition)
**Explanation**: View that yields the Cartesian product of multiple ranges.  
**Real-World Scenario**: Generate all possible coordinate pairs in a grid-based game.  
**Snippet**:  
```cpp
#include <ranges> auto cpv = std::ranges::cartesian_product_view(vec1, vec2);
```
**Example**: [ranges_cartesian_product_view.cpp](../examples/C++23/ranges_cartesian_product_view.cpp)

## Range Adaptors
### std::ranges::views::zip, zip_transform, adjacent, adjacent_transform, chunk, chunk_by, slide, stride, cartesian_product (C++23 Addition)
**Explanation**: Adaptors for creating corresponding range views with specific transformations.  
**Real-World Scenario**: Chain operations to process paired data in a pipeline (e.g., zip and transform).  
**Snippet**:  
```cpp
#include <ranges> auto v = vec | std::views::zip(vec2) | std::views::transform([](auto p) { return std::get<0>(p) + std::get<1>(p); });
```
**Example**: [ranges_adaptors.cpp](../examples/C++23/ranges_adaptors.cpp)

## Range Algorithms
### std::ranges::fold_left, fold_right, fold_left_first, fold_right_last (C++23 Addition)
**Explanation**: Algorithms to fold a range left or right, with or without the first/last element.  
**Real-World Scenario**: Compute cumulative scores in a game with custom operations.  
**Snippet**:  
```cpp
#include <ranges> auto sum = std::ranges::fold_left(vec, 0, std::plus{});
```
**Example**: [ranges_fold.cpp](../examples/C++23/ranges_fold.cpp)

### std::ranges::find_last, find_last_if, find_last_if_not (C++23 Addition)
**Explanation**: Algorithms to find the last occurrence of a value or matching a predicate.  
**Real-World Scenario**: Find the last error entry in a log file.  
**Snippet**:  
```cpp
#include <ranges> auto it = std::ranges::find_last(vec, 42);
```
**Example**: [ranges_find_last.cpp](../examples/C++23/ranges_find_last.cpp)

### std::ranges::contains, starts_with, ends_with (C++23 Evolution)
**Explanation**: Range-based versions of `contains`, `starts_with`, and `ends_with`, moved to `std::ranges`.  
**Real-World Scenario**: Check if a command sequence starts with a prefix in a parser.  
**Snippet**:  
```cpp
#include <ranges> bool starts = std::ranges::starts_with(vec, subvec);
```
**Example**: [ranges_contains_starts_ends.cpp](../examples/C++23/ranges_contains_starts_ends.cpp)

### std::ranges::to (C++23 Addition)
**Explanation**: Converts a range to a container or another range type.  
**Real-World Scenario**: Convert a filtered view to a vector in a data processor.  
**Snippet**:  
```cpp
#include <ranges> auto vec = std::ranges::to<std::vector<int>>(view);
```
**Example**: [ranges_to.cpp](../examples/C++23/ranges_to.cpp)

## Utilities
### std::expected (C++23 Addition)
**Explanation**: Represents a value or an error, safer than exceptions for error handling.  
**Real-World Scenario**: Handle file operation results in a file manager.  
**Snippet**:  
```cpp
#include <expected> std::expected<int, std::string> result = 42;
```
**Example**: [expected.cpp](../examples/C++23/expected.cpp)

### std::print, std::println (C++23 Addition)
**Explanation**: Type-safe, efficient printing to streams with formatting.  
**Real-World Scenario**: Print formatted logs in a console application.  
**Snippet**:  
```cpp
#include <print> std::print("Value: {}\n", 42);
```
**Example**: [print.cpp](../examples/C++23/print.cpp)

### std::stacktrace, std::stacktrace_entry, std::basic_stacktrace (C++23 Addition)
**Explanation**: Capture and manipulate stack traces for debugging.  
**Real-World Scenario**: Log stack traces on errors in a server application.  
**Snippet**:  
```cpp
#include <stacktrace> auto trace = std::stacktrace::current();
```
**Example**: [stacktrace.cpp](../examples/C++23/stacktrace.cpp)

### std::to_underlying (C++23 Addition)
**Explanation**: Converts an enum to its underlying type.  
**Real-World Scenario**: Convert an enum to an integer for serialization in a game.  
**Snippet**:  
```cpp
#include <utility> enum class E { A = 1 }; auto val = std::to_underlying(E::A);
```
**Example**: [to_underlying.cpp](../examples/C++23/to_underlying.cpp)

### std::byteswap (C++23 Addition)
**Explanation**: Reverses the byte order of an integral value.  
**Real-World Scenario**: Handle endianness in a network protocol.  
**Snippet**:  
```cpp
#include <bit> auto swapped = std::byteswap(0x1234);
```
**Example**: [byteswap.cpp](../examples/C++23/byteswap.cpp)

### std::assume_aligned (C++23 Addition)
**Explanation**: Informs the compiler of pointer alignment for optimization.  
**Real-World Scenario**: Optimize memory access in a graphics renderer.  
**Snippet**:  
```cpp
#include <memory> int* p = std::assume_aligned<alignof(int)>(ptr);
```
**Example**: [assume_aligned.cpp](../examples/C++23/assume_aligned.cpp)

### std::unreachable (C++23 Addition)
**Explanation**: Marks code as unreachable, triggering undefined behavior if executed.  
**Real-World Scenario**: Indicate impossible cases in a state machine.  
**Snippet**:  
```cpp
#include <utility> if (false) std::unreachable();
```
**Example**: [unreachable.cpp](../examples/C++23/unreachable.cpp)

### std::invoke_r (C++23 Addition)
**Explanation**: Invokes a callable with a specified return type.  
**Real-World Scenario**: Call a function with type-safe return in an event system.  
**Snippet**:  
```cpp
#include <functional> auto result = std::invoke_r<int>(func, args...);
```
**Example**: [invoke_r.cpp](../examples/C++23/invoke_r.cpp)

### std::forward_like (C++23 Addition)
**Explanation**: Forwards arguments with the same value category as a reference.  
**Real-World Scenario**: Preserve value category in a generic forwarding function.  
**Snippet**:  
```cpp
#include <utility> auto x = std::forward_like<T>(arg);
```
**Example**: [forward_like.cpp](../examples/C++23/forward_like.cpp)

### std::move_only_function (C++23 Addition)
**Explanation**: Function wrapper for move-only callables (e.g., lambdas with unique_ptr).  
**Real-World Scenario**: Store move-only callbacks in an event queue.  
**Snippet**:  
```cpp
#include <functional> std::move_only_function<void()> f = []{ /* action */ };
```
**Example**: [move_only_function.cpp](../examples/C++23/move_only_function.cpp)

## Container Improvements
### std::string constexpr Support (C++23 Evolution)
**Explanation**: Enhanced `constexpr` support for `std::string` operations.  
**Real-World Scenario**: Generate compile-time strings for a configuration parser.  
**Snippet**:  
```cpp
constexpr std::string s = "hello"; constexpr auto len = s.size();
```
**Example**: [constexpr_string.cpp](../examples/C++23/constexpr_string.cpp)

### std::vector constexpr Support (C++23 Evolution)
**Explanation**: Enhanced `constexpr` support for `std::vector` operations.  
**Real-World Scenario**: Create compile-time lookup tables in a data processor.  
**Snippet**:  
```cpp
constexpr std::vector<int> vec = {1, 2, 3};
```
**Example**: [constexpr_vector.cpp](../examples/C++23/constexpr_vector.cpp)

### std::optional Monadic Operations (C++23 Addition)
**Explanation**: Adds `and_then`, `transform`, and `or_else` for monadic-style operations.  
**Real-World Scenario**: Chain optional operations in a configuration parser.  
**Snippet**:  
```cpp
#include <optional> auto result = opt.transform([](int x) { return x * x; });
```
**Example**: [optional_monadic.cpp](../examples/C++23/optional_monadic.cpp)

### std::variant Monadic Operations (C++23 Addition)
**Explanation**: Adds `and_then` and `transform` for monadic-style operations on variants.  
**Real-World Scenario**: Transform variant data in a game’s event system.  
**Snippet**:  
```cpp
#include <variant> auto result = var.transform([](int x) { return x * x; });
```
**Example**: [variant_monadic.cpp](../examples/C++23/variant_monadic.cpp)

### std::span subspan, as_bytes, as_writable_bytes (C++23 Evolution)
**Explanation**: Adds methods for creating subviews and accessing bytes of a `std::span`.  
**Real-World Scenario**: Process a subset of pixel data in a renderer.  
**Snippet**:  
```cpp
#include <span> auto sub = span.subspan(1, 2);
```
**Example**: [span_enhancements.cpp](../examples/C++23/span_enhancements.cpp)

### std::reference_wrapper Improvements (C++23 Evolution)
**Explanation**: Adds conversion to underlying type and better functor support.  
**Real-World Scenario**: Use `std::reference_wrapper` in a generic algorithm with type conversion.  
**Snippet**:  
```cpp
#include <functional> std::reference_wrapper<int> ref(x); int val = ref;
```
**Example**: [reference_wrapper.cpp](../examples/C++23/reference_wrapper.cpp)

## Filesystem Improvements
### std::filesystem::recursive_directory_iterator Improvements (C++23 Evolution)
**Explanation**: Enhanced performance and usability for recursive directory iteration.  
**Real-World Scenario**: Traverse a directory tree efficiently in a file explorer.  
**Snippet**:  
```cpp
#include <filesystem> for (auto& p : std::filesystem::recursive_directory_iterator("dir")) {}
```
**Example**: [filesystem_recursive.cpp](../examples/C++23/filesystem_recursive.cpp)

## Chrono Improvements
### std::chrono::parse, std::chrono::format (C++23 Addition)
**Explanation**: Parse and format time points and durations with string patterns.  
**Real-World Scenario**: Parse user-input dates in a calendar application.  
**Snippet**:  
```cpp
#include <chrono> auto tp = std::chrono::parse("%Y-%m-%d", "2025-09-09");
```
**Example**: [chrono_parse_format.cpp](../examples/C++23/chrono_parse_format.cpp)

### std::chrono::zoned_traits, std::chrono::choose, std::chrono::leap_second (C++23 Addition)
**Explanation**: Enhances time zone support and leap second handling.  
**Real-World Scenario**: Handle time zones and leap seconds in a global scheduler.  
**Snippet**:  
```cpp
#include <chrono> auto zt = std::chrono::zoned_time{"UTC", std::chrono::system_clock::now()};
```
**Example**: [chrono_zoned_leap.cpp](../examples/C++23/chrono_zoned_leap.cpp)

## Modules
### import std (Standard Library Module) (C++23 Addition)
**Explanation**: Imports the entire C++ standard library as a module.  
**Real-World Scenario**: Simplify standard library usage in a modular game engine.  
**Snippet**:  
```cpp
import std; std::vector<int> vec = {1, 2, 3};
```
**Example**: [import_std.cpp](../examples/C++23/import_std.cpp)