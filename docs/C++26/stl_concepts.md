# C++26 STL Concepts

This document covers new or evolved C++26 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++26/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17/C++20/C++23 are included.

## Containers
### std::mdspan Improvements (C++26 Evolution)
**Explanation**: Adds support for `dynamic_extent` in `std::mdspan` for flexible multidimensional views.  
**Real-World Scenario**: Process variable-sized image data in a graphics renderer.  
**Snippet**:  
```cpp
#include <mdspan> std::mdspan<int, std::dynamic_extent, std::dynamic_extent> ms(data, rows, cols);
```
**Example**: [mdspan_improvements.cpp](../examples/C++26/mdspan_improvements.cpp)

### std::flat_map Improvements (C++26 Evolution)
**Explanation**: Enhanced performance and usability for `std::flat_map` (e.g., better insertion).  
**Real-World Scenario**: Optimize key-value lookups in a game’s settings manager.  
**Snippet**:  
```cpp
#include <flat_map> std::flat_map<int, std::string> fm; fm.insert({1, "one"});
```
**Example**: [flat_map_improvements.cpp](../examples/C++26/flat_map_improvements.cpp)

### std::flat_set Improvements (C++26 Evolution)
**Explanation**: Enhanced performance and usability for `std::flat_set` (e.g., faster searches).  
**Real-World Scenario**: Store unique entity IDs in a game with improved lookup speed.  
**Snippet**:  
```cpp
#include <flat_set> std::flat_set<int> fs; fs.insert(42);
```
**Example**: [flat_set_improvements.cpp](../examples/C++26/flat_set_improvements.cpp)

## Utilities
### std::text_encoding (C++26 Addition)
**Explanation**: Provides facilities for handling text encodings (e.g., UTF-8, UTF-16).  
**Real-World Scenario**: Process multilingual text in a globalized application.  
**Snippet**:  
```cpp
#include <text_encoding> auto enc = std::text_encoding::utf8();
```
**Example**: [text_encoding.cpp](../examples/C++26/text_encoding.cpp)

### std::spanstream (C++26 Addition)
**Explanation**: Stream interface for `std::span` to read/write contiguous data.  
**Real-World Scenario**: Serialize game data to a memory buffer efficiently.  
**Snippet**:  
```cpp
#include <spanstream> std::spanstream ss(span); ss << "data";
```
**Example**: [spanstream.cpp](../examples/C++26/spanstream.cpp)

### std::out_ptr, std::inout_ptr (C++26 Addition)
**Explanation**: Smart pointers for interoperating with C-style output parameters.  
**Real-World Scenario**: Interface with legacy C APIs in a graphics library.  
**Snippet**:  
```cpp
#include <out_ptr> void c_api(int** p); std::unique_ptr<int> ptr; c_api(std::out_ptr(ptr));
```
**Example**: [out_ptr.cpp](../examples/C++26/out_ptr.cpp)

### std::format Improvements (C++26 Evolution)
**Explanation**: Adds range formatting support to `std::format`.  
**Real-World Scenario**: Format a vector of scores in a game’s leaderboard.  
**Snippet**:  
```cpp
#include <format> auto s = std::format("Scores: {}", std::vector{1, 2, 3});
```
**Example**: [format_improvements.cpp](../examples/C++26/format_improvements.cpp)

### std::print Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::print` with better formatting and stream support.  
**Real-World Scenario**: Print formatted logs with ranges in a console application.  
**Snippet**:  
```cpp
#include <print> std::print("Values: {}\n", std::vector{1, 2, 3});
```
**Example**: [print_improvements.cpp](../examples/C++26/print_improvements.cpp)

### std::bit_int (C++26 Addition)
**Explanation**: Arbitrary-precision integer type for bit manipulation.  
**Real-World Scenario**: Handle large bitmasks in a permissions system.  
**Snippet**:  
```cpp
#include <bit_int> std::bit_int<128> mask = 1;
```
**Example**: [bit_int.cpp](../examples/C++26/bit_int.cpp)

## Range Algorithms
### std::ranges::inplace_transform (C++26 Addition)
**Explanation**: Transforms a range in-place with a given function.  
**Real-World Scenario**: Modify game entity positions directly in a container.  
**Snippet**:  
```cpp
#include <ranges> std::ranges::inplace_transform(vec, [](int x) { return x * 2; });
```
**Example**: [ranges_inplace_transform.cpp](../examples/C++26/ranges_inplace_transform.cpp)

### std::ranges::inplace_sort (C++26 Addition)
**Explanation**: Sorts a range in-place with a comparator or projection.  
**Real-World Scenario**: Sort a leaderboard’s scores directly in memory.  
**Snippet**:  
```cpp
#include <ranges> std::ranges::inplace_sort(vec, std::less{});
```
**Example**: [ranges_inplace_sort.cpp](../examples/C++26/ranges_inplace_sort.cpp)

### std::ranges::inplace_merge (C++26 Addition)
**Explanation**: Merges two sorted subranges in-place within a range.  
**Real-World Scenario**: Merge sorted player lists in a game server.  
**Snippet**:  
```cpp
#include <ranges> std::ranges::inplace_merge(vec, vec.begin() + 5, std::less{});
```
**Example**: [ranges_inplace_merge.cpp](../examples/C++26/ranges_inplace_merge.cpp)

## Container Improvements
### std::string_view Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::string_view` with additional methods or performance tweaks.  
**Real-World Scenario**: Parse configuration strings with improved efficiency.  
**Snippet**:  
```cpp
#include <string_view> std::string_view sv = "config"; // Enhanced operations
```
**Example**: [string_view_improvements.cpp](../examples/C++26/string_view_improvements.cpp)

### std::u8string_view (C++26 Addition)
**Explanation**: UTF-8 string view for efficient Unicode handling.  
**Real-World Scenario**: Process UTF-8 text in a multilingual UI.  
**Snippet**:  
```cpp
#include <string> std::u8string_view sv = u8"hello";
```
**Example**: [u8string_view.cpp](../examples/C++26/u8string_view.cpp)

### std::u8string Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::u8string` for better UTF-8 string manipulation.  
**Real-World Scenario**: Store and manipulate UTF-8 text in a text editor.  
**Snippet**:  
```cpp
#include <string> std::u8string s = u8"hello"; // Improved operations
```
**Example**: [u8string_improvements.cpp](../examples/C++26/u8string_improvements.cpp)

### std::optional::and_then (C++26 Evolution)
**Explanation**: Enhanced `and_then` for `std::optional` with better chaining support.  
**Real-World Scenario**: Chain optional computations in a configuration parser.  
**Snippet**:  
```cpp
#include <optional> auto result = opt.and_then([](int x) { return std::optional{x * x}; });
```
**Example**: [optional_and_then.cpp](../examples/C++26/optional_and_then.cpp)

### std::variant::and_then (C++26 Evolution)
**Explanation**: Enhanced `and_then` for `std::variant` with improved chaining.  
**Real-World Scenario**: Transform variant data in a game’s event system.  
**Snippet**:  
```cpp
#include <variant> auto result = var.and_then([](int x) { return std::variant<int>{x * x}; });
```
**Example**: [variant_and_then.cpp](../examples/C++26/variant_and_then.cpp)

### std::expected Monadic Operations (C++26 Evolution)
**Explanation**: Adds `and_then`, `transform`, and `or_else` to `std::expected` for monadic operations.  
**Real-World Scenario**: Handle file operation results with chained error handling.  
**Snippet**:  
```cpp
#include <expected> auto result = exp.transform([](int x) { return x * x; });
```
**Example**: [expected_monadic.cpp](../examples/C++26/expected_monadic.cpp)

## Chrono Extensions
### std::chrono::tai_clock Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::chrono::tai_clock` for better TAI time handling.  
**Real-World Scenario**: Track precise time in a scientific application.  
**Snippet**:  
```cpp
#include <chrono> auto now = std::chrono::tai_clock::now();
```
**Example**: [tai_clock_improvements.cpp](../examples/C++26/tai_clock_improvements.cpp)

### std::chrono::gps_clock Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::chrono::gps_clock` for better GPS time handling.  
**Real-World Scenario**: Synchronize events in a navigation system.  
**Snippet**:  
```cpp
#include <chrono> auto now = std::chrono::gps_clock::now();
```
**Example**: [gps_clock_improvements.cpp](../examples/C++26/gps_clock_improvements.cpp)

### std::chrono::leap_second Support (C++26 Evolution)
**Explanation**: Improved support for leap seconds in chrono types.  
**Real-World Scenario**: Handle leap seconds in a global time scheduler.  
**Snippet**:  
```cpp
#include <chrono> auto ls = std::chrono::leap_second::list();
```
**Example**: [leap_second_support.cpp](../examples/C++26/leap_second_support.cpp)

## Math Functions
### std::frexp, std::modf, std::remquo (C++26 Addition)
**Explanation**: Math functions for extracting mantissa/exponent, fractional/integer parts, and quotient/remainder.  
**Real-World Scenario**: Perform precise floating-point calculations in a physics engine.  
**Snippet**:  
```cpp
#include <cmath> auto [mant, exp] = std::frexp(3.14);
```
**Example**: [math_functions.cpp](../examples/C++26/math_functions.cpp)

### std::lerp Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::lerp` for better precision or overloads.  
**Real-World Scenario**: Interpolate positions in a game’s animation system.  
**Snippet**:  
```cpp
#include <cmath> auto pos = std::lerp(0.0f, 100.0f, 0.5f);
```
**Example**: [lerp_improvements.cpp](../examples/C++26/lerp_improvements.cpp)

### std::complex Improvements (C++26 Evolution)
**Explanation**: Enhanced `std::complex` with better operations or performance.  
**Real-World Scenario**: Optimize complex number calculations in a signal processor.  
**Snippet**:  
```cpp
#include <complex> std::complex<float> c(1.0f, 2.0f); // Improved operations
```
**Example**: [complex_improvements.cpp](../examples/C++26/complex_improvements.cpp)

## SIMD Support
### std::simd (C++26 Addition)
**Explanation**: Provides SIMD (Single Instruction, Multiple Data) operations for parallel computation.  
**Real-World Scenario**: Optimize matrix operations in a graphics engine.  
**Snippet**:  
```cpp
#include <simd> std::simd<float> vec = {1.0f, 2.0f, 3.0f, 4.0f};
```
**Example**: [simd.cpp](../examples/C++26/simd.cpp)

## Threading
### std::hazard_pointer (C++26 Addition)
**Explanation**: Memory reclamation for concurrent data structures using hazard pointers.  
**Real-World Scenario**: Implement lock-free data structures in a game server.  
**Snippet**:  
```cpp
#include <hazard_pointer> std::hazard_pointer hp; auto ptr = hp.protect(raw_ptr);
```
**Example**: [hazard_pointer.cpp](../examples/C++26/hazard_pointer.cpp)

### std::rcu (Reader-Copy-Update) (C++26 Addition)
**Explanation**: Synchronization mechanism for read-heavy concurrent data structures.  
**Real-World Scenario**: Update shared game state with minimal reader disruption.  
**Snippet**:  
```cpp
#include <rcu> std::rcu::synchronize(); // Wait for readers
```
**Example**: [rcu.cpp](../examples/C++26/rcu.cpp)

### std::execution (Executors for Parallelism) (C++26 Addition)
**Explanation**: Framework for parallel execution policies and executors.  
**Real-World Scenario**: Parallelize physics calculations in a game engine.  
**Snippet**:  
```cpp
#include <execution> std::for_each(std::execution::par, vec.begin(), vec.end(), fn);
```
**Example**: [execution.cpp](../examples/C++26/execution.cpp)