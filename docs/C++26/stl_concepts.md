# C++26 STL Concepts

This document covers new or evolved C++26 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++26/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17/C++20/C++23 are included.

## Containers
### std::inplace_vector (C++26 Addition)
**Explanation**: A fixed-capacity, variable-size container that stores elements inline (no heap allocation). Combines the performance of `std::array` with the flexibility of `std::vector` for cases where the maximum size is known at compile time.
**Real-World Scenario**: Store a bounded list of active projectiles in a game engine without any dynamic memory allocation, ideal for real-time systems with strict allocation budgets.
**Snippet**:
```cpp
#include <inplace_vector>

std::inplace_vector<int, 16> iv; // Capacity of 16, stored on the stack
iv.push_back(1);
iv.push_back(2);
iv.push_back(3);
// iv.size() == 3, iv.capacity() == 16, no heap allocation
```
**Example**: [inplace_vector.cpp](../examples/C++26/inplace_vector.cpp)

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

### std::copyable_function (C++26 Addition)
**Explanation**: A type-erased callable wrapper similar to `std::function` but with a `const`-correct call operator. Unlike `std::function`, invoking a `const std::copyable_function` only calls the stored callable as `const`, preventing surprising mutations through a `const` reference.
**Real-World Scenario**: Store callback handlers in an event system where the callback registry is shared across threads via `const` reference, ensuring thread-safe invocation.
**Snippet**:
```cpp
#include <functional>

std::copyable_function<int(int) const> fn = [factor = 2](int x) { return x * factor; };
const auto& ref = fn;
int result = ref(21); // Safe: const-correct invocation, result == 42
```
**Example**: [copyable_function.cpp](../examples/C++26/copyable_function.cpp)

### std::function_ref (C++26 Addition)
**Explanation**: A lightweight, non-owning reference to a callable. Unlike `std::function`, it never allocates and never copies the callable, making it ideal for passing callbacks to functions that do not need to store them beyond the call.
**Real-World Scenario**: Pass a sorting comparator to a library function without the overhead of type-erased heap allocation.
**Snippet**:
```cpp
#include <functional>

void apply(std::function_ref<int(int)> fn, int value) {
    std::println("Result: {}", fn(value));
}

auto square = [](int x) { return x * x; };
apply(square, 5); // No allocation, no copy -- just a reference
```
**Example**: [function_ref.cpp](../examples/C++26/function_ref.cpp)

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

## Saturation Arithmetic
### std::add_sat, std::sub_sat, std::mul_sat, std::div_sat (C++26 Addition)
**Explanation**: Saturating arithmetic functions that clamp results to the representable range of the type instead of wrapping around on overflow or underflow. Prevents silent integer overflow bugs that plague conventional arithmetic.
**Real-World Scenario**: Calculate audio sample levels where values must remain within the valid range (e.g., 0-255 for 8-bit audio) without clipping artifacts caused by integer wrap-around.
**Snippet**:
```cpp
#include <numeric>

unsigned char a = 200;
unsigned char b = 100;
auto result = std::add_sat(a, b);  // 255 (clamped), not 44 (wrapped)
auto diff   = std::sub_sat<unsigned char>(50, 100); // 0 (clamped), not 206 (wrapped)
auto prod   = std::mul_sat<unsigned char>(20, 20);  // 255 (clamped), not 144 (wrapped)
```
**Example**: [saturation_arithmetic.cpp](../examples/C++26/saturation_arithmetic.cpp)

### std::saturate_cast (C++26 Addition)
**Explanation**: Casts a value to a narrower or different integer type with saturation semantics, clamping the value to the destination type's range instead of truncating or producing undefined behavior.
**Real-World Scenario**: Convert a 32-bit sensor reading to a 16-bit register value in an embedded system, ensuring out-of-range values are clamped rather than corrupted.
**Snippet**:
```cpp
#include <numeric>

int large = 100000;
auto small = std::saturate_cast<short>(large);       // 32767 (SHORT_MAX, clamped)
auto byte  = std::saturate_cast<unsigned char>(-10);  // 0 (clamped, not wrapped)
```
**Example**: [saturate_cast.cpp](../examples/C++26/saturate_cast.cpp)

## Compile-Time Utilities
### std::is_within_lifetime (C++26 Addition)
**Explanation**: A compile-time utility that checks whether a given pointer or reference refers to an object that is within its lifetime. Enables safer `constexpr` code by allowing compile-time validation of object lifetimes, particularly useful for union-like types and type punning.
**Real-World Scenario**: Implement a `constexpr`-compatible tagged union that validates at compile time which member is currently active before accessing it.
**Snippet**:
```cpp
#include <type_traits>

union FloatInt {
    float f;
    int i;
};

constexpr int test() {
    FloatInt fi;
    fi.i = 42;
    if constexpr (std::is_within_lifetime(&fi.i)) {
        return fi.i; // Safe: i is the active member
    }
    return -1;
}

static_assert(test() == 42);
```
**Example**: [is_within_lifetime.cpp](../examples/C++26/is_within_lifetime.cpp)

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
**Explanation**: Provides a portable, type-safe interface for SIMD (Single Instruction, Multiple Data) operations. Abstracts hardware-specific vector instructions behind a standard API, enabling parallel computation on multiple data elements with a single operation.
**Real-World Scenario**: Optimize per-vertex transformations in a 3D graphics engine by processing four floats simultaneously.
**Snippet**:
```cpp
#include <simd>

std::simd<float> a = {1.0f, 2.0f, 3.0f, 4.0f};
std::simd<float> b = {5.0f, 6.0f, 7.0f, 8.0f};
auto c = a + b; // Element-wise addition: {6.0f, 8.0f, 10.0f, 12.0f}
auto d = a * b; // Element-wise multiplication: {5.0f, 12.0f, 21.0f, 32.0f}
```
**Example**: [simd.cpp](../examples/C++26/simd.cpp)

### std::simd_mask (C++26 Addition)
**Explanation**: A companion type to `std::simd` that represents a vector of boolean values. Used for conditional SIMD operations, enabling element-wise selection and masked computation without branching.
**Real-World Scenario**: In a particle system, filter out particles that have expired (lifetime <= 0) and only update the active ones, all in a single vectorized pass.
**Snippet**:
```cpp
#include <simd>

std::simd<float> values = {1.0f, -2.0f, 3.0f, -4.0f};
std::simd_mask<float> positive = values > 0.0f; // {true, false, true, false}
auto clamped = std::simd::where(positive, values); // Keeps only positive elements
```
**Example**: [simd_mask.cpp](../examples/C++26/simd_mask.cpp)

### std::simd::reduce (C++26 Addition)
**Explanation**: Reduces all elements of a SIMD vector into a single scalar value using a specified binary operation (e.g., addition, multiplication, min, max). Enables efficient horizontal reductions across vector lanes.
**Real-World Scenario**: Compute the sum of all elements in a vectorized dot product or find the maximum value across a batch of distance calculations.
**Snippet**:
```cpp
#include <simd>

std::simd<float> values = {1.0f, 2.0f, 3.0f, 4.0f};
float sum = std::reduce(values);                    // 10.0f (default: addition)
float product = std::reduce(values, std::multiplies{}); // 24.0f
```
**Example**: [simd_reduce.cpp](../examples/C++26/simd_reduce.cpp)

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

## Execution Framework
### std::execution (Senders/Receivers) (C++26 Addition)
**Explanation**: A structured asynchronous programming framework based on the senders/receivers model. Provides composable building blocks for expressing asynchronous workflows with clear ownership semantics, cancellation support, and error propagation. Replaces ad-hoc callback and future-based patterns with a unified, type-safe approach.
**Real-World Scenario**: Build a pipelined data processing system where stages (fetch, decode, transform, store) execute asynchronously and are composed declaratively.
**Snippet**:
```cpp
#include <execution>
namespace ex = std::execution;

// Compose an async pipeline: schedule -> compute -> transform
auto work = ex::schedule(my_scheduler)
          | ex::then([] { return fetch_data(); })
          | ex::then([](auto data) { return process(data); });

// Execute synchronously for demonstration
auto result = ex::sync_wait(std::move(work));
```
**Example**: [execution.cpp](../examples/C++26/execution.cpp)

### std::execution::scheduler, sender, receiver (C++26 Addition)
**Explanation**: Core concepts of the execution framework. A `scheduler` represents an execution context (e.g., a thread pool). A `sender` describes an asynchronous operation that will produce values. A `receiver` consumes those values (or errors/cancellation). Together they form a type-safe, composable async model.
**Real-World Scenario**: Define a thread pool scheduler that distributes work items across worker threads in a game server.
**Snippet**:
```cpp
#include <execution>
namespace ex = std::execution;

// A scheduler produces senders via schedule()
ex::scheduler auto sched = get_thread_pool().get_scheduler();
ex::sender auto work = ex::schedule(sched); // A sender representing "start on this scheduler"
// A receiver would be connected to consume the result
```
**Example**: [execution_concepts.cpp](../examples/C++26/execution_concepts.cpp)

### std::execution::then, when_all, let_value (C++26 Addition)
**Explanation**: Sender adaptors for composing asynchronous operations. `then` chains a continuation. `when_all` waits for multiple senders to complete. `let_value` creates a new sender based on the result of a previous one, enabling dynamic async composition.
**Real-World Scenario**: Fetch data from multiple services concurrently, then combine the results once all are available.
**Snippet**:
```cpp
#include <execution>
namespace ex = std::execution;

auto fetch_a = ex::schedule(sched) | ex::then([] { return fetch_service_a(); });
auto fetch_b = ex::schedule(sched) | ex::then([] { return fetch_service_b(); });

// Wait for both, then combine
auto combined = ex::when_all(std::move(fetch_a), std::move(fetch_b))
              | ex::then([](auto a, auto b) { return merge(a, b); });

// Dynamic composition with let_value
auto dynamic = ex::just(42) | ex::let_value([](int x) {
    return ex::just(x * 2); // Create a new sender based on the value
});
```
**Example**: [execution_adaptors.cpp](../examples/C++26/execution_adaptors.cpp)

### std::execution::bulk, split, ensure_started (C++26 Addition)
**Explanation**: Advanced sender adaptors. `bulk` executes a function over an index range in parallel. `split` allows a sender to be consumed by multiple receivers. `ensure_started` eagerly starts an async operation so it runs in the background.
**Real-World Scenario**: Process a large array of game entities in parallel using `bulk`, share computation results across multiple consumers with `split`, and pre-warm a cache with `ensure_started`.
**Snippet**:
```cpp
#include <execution>
namespace ex = std::execution;

// Parallel bulk operation over 1000 elements
auto work = ex::just(std::vector<float>(1000))
          | ex::bulk(1000, [](int idx, auto& vec) {
                vec[idx] = compute(idx);
            });

// Split: share a sender across multiple consumers
auto shared = ex::schedule(sched) | ex::then([] { return load_config(); }) | ex::split();
auto consumer1 = shared | ex::then([](auto cfg) { return init_graphics(cfg); });
auto consumer2 = shared | ex::then([](auto cfg) { return init_audio(cfg); });

// Ensure started: begin work eagerly
auto background = ex::schedule(sched)
                | ex::then([] { return precompute_data(); })
                | ex::ensure_started();
```
**Example**: [execution_advanced.cpp](../examples/C++26/execution_advanced.cpp)