# C++17 STL Concepts

This document covers new or evolved C++17 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++17/). Only additions or evolutions from C++98/C++03/C++11/C++14 are included.

## Containers
### std::optional (C++17 Addition)
**Explanation**: Represents a value that may or may not exist, avoiding null pointers.  
**Real-World Scenario**: Store optional user preferences in a configuration system.  
**Snippet**:  
```cpp
#include <optional> std::optional<int> opt = 42;
```
**Example**: [optional.cpp](../examples/C++17/optional.cpp)

### std::variant (C++17 Addition)
**Explanation**: Stores one of several types, providing type-safe union-like functionality.  
**Real-World Scenario**: Represent different event types in a game’s event system.  
**Snippet**:  
```cpp
#include <variant> std::variant<int, std::string> v = "event";
```
**Example**: [variant.cpp](../examples/C++17/variant.cpp)

### std::any (C++17 Addition)
**Explanation**: Stores any type with type-safe retrieval, replacing type-unsafe solutions.  
**Real-World Scenario**: Store heterogeneous data in a dynamic configuration parser.  
**Snippet**:  
```cpp
#include <any> std::any a = 42;
```
**Example**: [any.cpp](../examples/C++17/any.cpp)

### std::string_view (C++17 Addition)
**Explanation**: Non-owning view of a string, improving performance for read-only access.  
**Real-World Scenario**: Parse log messages without copying strings in a logger.  
**Snippet**:  
```cpp
#include <string_view> std::string_view sv = "hello";
```
**Example**: [string_view.cpp](../examples/C++17/string_view.cpp)

### std::vector (C++17 Evolution)
**Explanation**: Adds `try_emplace` and `insert`/`emplace` with bounds checking.  
**Real-World Scenario**: Safely insert complex objects into a chat message list.  
**Snippet**:  
```cpp
#include <vector> std::vector<int> vec; vec.try_emplace(vec.end(), 42);
```
**Example**: [vector.cpp](../examples/C++17/vector.cpp)

### std::map/std::unordered_map (C++17 Evolution)
**Explanation**: Adds `try_emplace` and `insert_or_assign` for efficient key-value operations.  
**Real-World Scenario**: Update user settings by ID without redundant constructions.  
**Snippet**:  
```cpp
#include <map> std::map<int, std::string> m; m.try_emplace(1, "value");
```
**Example**: [map.cpp](../examples/C++17/map.cpp)

## Algorithms
### std::for_each_n (C++17 Addition)
**Explanation**: Applies a function to the first n elements of a range.  
**Real-World Scenario**: Process the first n items in a shopping cart.  
**Snippet**:  
```cpp
#include <algorithm> std::for_each_n(vec.begin(), 3, print);
```
**Example**: [for_each_n.cpp](../examples/C++17/for_each_n.cpp)

### std::sample (C++17 Addition)
**Explanation**: Randomly selects n elements from a range into a destination.  
**Real-World Scenario**: Select a random subset of users for a survey.  
**Snippet**:  
```cpp
#include <algorithm> std::sample(vec.begin(), vec.end(), dest.begin(), 3, std::mt19937{});
```
**Example**: [sample.cpp](../examples/C++17/sample.cpp)

### std::reduce (C++17 Addition)
**Explanation**: Generalized sum over a range, supporting parallel execution.  
**Real-World Scenario**: Compute total sales in a store with parallel processing.  
**Snippet**:  
```cpp
#include <numeric> auto sum = std::reduce(vec.begin(), vec.end());
```
**Example**: [reduce.cpp](../examples/C++17/reduce.cpp)

### std::transform_reduce (C++17 Addition)
**Explanation**: Applies a transformation and reduces the result, supporting parallel execution.  
**Real-World Scenario**: Calculate total transformed values (e.g., squared sales) in parallel.  
**Snippet**:  
```cpp
#include <numeric> auto result = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>{}, square);
```
**Example**: [transform_reduce.cpp](../examples/C++17/transform_reduce.cpp)

### std::exclusive_scan (C++17 Addition)
**Explanation**: Computes partial sums excluding the current element, supporting parallel execution.  
**Real-World Scenario**: Calculate running totals for a financial report.  
**Snippet**:  
```cpp
#include <numeric> std::exclusive_scan(vec.begin(), vec.end(), dest.begin(), 0);
```
**Example**: [exclusive_scan.cpp](../examples/C++17/exclusive_scan.cpp)

### std::inclusive_scan (C++17 Addition)
**Explanation**: Computes partial sums including the current element, supporting parallel execution.  
**Real-World Scenario**: Generate cumulative scores in a leaderboard.  
**Snippet**:  
```cpp
#include <numeric> std::inclusive_scan(vec.begin(), vec.end(), dest.begin());
```
**Example**: [inclusive_scan.cpp](../examples/C++17/inclusive_scan.cpp)

### std::transform_exclusive_scan (C++17 Addition)
**Explanation**: Transforms and computes exclusive partial sums, supporting parallel execution.  
**Real-World Scenario**: Compute running totals of squared values in a dataset.  
**Snippet**:  
```cpp
#include <numeric> std::transform_exclusive_scan(vec.begin(), vec.end(), dest.begin(), 0, std::plus<>{}, square);
```
**Example**: [transform_exclusive_scan.cpp](../examples/C++17/transform_exclusive_scan.cpp)

### std::transform_inclusive_scan (C++17 Addition)
**Explanation**: Transforms and computes inclusive partial sums, supporting parallel execution.  
**Real-World Scenario**: Calculate cumulative transformed values for a performance metric.  
**Snippet**:  
```cpp
#include <numeric> std::transform_inclusive_scan(vec.begin(), vec.end(), dest.begin(), std::plus<>{}, square);
```
**Example**: [transform_inclusive_scan.cpp](../examples/C++17/transform_inclusive_scan.cpp)

### Parallel Algorithms (C++17 Addition)
**Explanation**: Many STL algorithms (e.g., `std::sort`, `std::transform`) support parallel execution policies.  
**Real-World Scenario**: Sort a large dataset in a data analysis tool using multiple cores.  
**Snippet**:  
```cpp
#include <algorithm> #include <execution> std::sort(std::execution::par, vec.begin(), vec.end());
```
**Example**: [parallel_algorithms.cpp](../examples/C++17/parallel_algorithms.cpp)

## Utilities
### std::byte (C++17 Addition)
**Explanation**: Type for raw byte manipulation, safer than `char`.  
**Real-World Scenario**: Process raw binary data in a network protocol.  
**Snippet**:  
```cpp
#include <cstddef> std::byte b{0xFF};
```
**Example**: [byte.cpp](../examples/C++17/byte.cpp)

### std::invoke (C++17 Addition)
**Explanation**: Uniformly calls functions, member functions, or functors.  
**Real-World Scenario**: Generalize callback invocation in an event system.  
**Snippet**:  
```cpp
#include <functional> std::invoke(func, 42);
```
**Example**: [invoke.cpp](../examples/C++17/invoke.cpp)

### std::apply (C++17 Addition)
**Explanation**: Calls a function with tuple arguments unpacked.  
**Real-World Scenario**: Pass tuple data to a function in a game’s physics engine.  
**Snippet**:  
```cpp
#include <tuple> std::apply(func, std::make_tuple(1, 2));
```
**Example**: [apply.cpp](../examples/C++17/apply.cpp)

### std::make_from_tuple (C++17 Addition)
**Explanation**: Constructs an object from a tuple of arguments.  
**Real-World Scenario**: Create a game object from tuple data in a factory.  
**Snippet**:  
```cpp
#include <tuple> auto obj = std::make_from_tuple<MyClass>(std::make_tuple(1, "value"));
```
**Example**: [make_from_tuple.cpp](../examples/C++17/make_from_tuple.cpp)

### std::size, std::empty, std::data (C++17 Addition)
**Explanation**: Generic functions to get size, check emptiness, or access raw data of containers.  
**Real-World Scenario**: Query container properties in a generic data processor.  
**Snippet**:  
```cpp
#include <iterator> auto s = std::size(vec); bool e = std::empty(vec);
```
**Example**: [size_empty_data.cpp](../examples/C++17/size_empty_data.cpp)

## Filesystem Library (C++17 Addition)
**Explanation**: Provides operations for file and directory manipulation (e.g., `std::filesystem::path`).  
**Real-World Scenario**: Traverse directories in a file explorer application.  
**Snippet**:  
```cpp
#include <filesystem> auto path = std::filesystem::current_path();
```
**Example**: [filesystem.cpp](../examples/C++17/filesystem.cpp)

## String Conversion Enhancements (C++17 Evolution)
**Explanation**: `std::to_chars` and `std::from_chars` for efficient numeric-string conversions.  
**Real-World Scenario**: Convert numbers to strings in a high-performance logger.  
**Snippet**:  
```cpp
#include <charconv> char buf[10]; std::to_chars(buf, buf+10, 42);
```
**Example**: [string_conversion.cpp](../examples/C++17/string_conversion.cpp)