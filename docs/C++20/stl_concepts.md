# C++20 STL Concepts

This document covers new or evolved C++20 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++20/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17 are included.

## Containers
### std::span (C++20 Addition)
**Explanation**: Non-owning view over a contiguous sequence, safer than raw pointers.  
**Real-World Scenario**: Pass a subset of an array to a rendering function in a game.  
**Snippet**:  
```cpp
#include <span> std::span<int> s(array, 5);
```
**Example**: [span.cpp](../examples/C++20/span.cpp)

### std::string (C++20 Evolution)
**Explanation**: Adds `starts_with` and `ends_with` for substring checks.  
**Real-World Scenario**: Check if a log message starts with an error prefix in a logger.  
**Snippet**:  
```cpp
#include <string> bool starts = std::string("error: log").starts_with("error");
```
**Example**: [string.cpp](../examples/C++20/string.cpp)

### std::string_view (C++20 Evolution)
**Explanation**: Adds `starts_with` and `ends_with` for efficient substring checks.  
**Real-World Scenario**: Validate a configuration string prefix without copying.  
**Snippet**:  
```cpp
#include <string_view> bool starts = std::string_view("config").starts_with("con");
```
**Example**: [string_view.cpp](../examples/C++20/string_view.cpp)

### std::bitset (C++20 Evolution)
**Explanation**: Adds spaceship operator (`<=>`) for comparisons.  
**Real-World Scenario**: Compare bitmasks in a permissions system.  
**Snippet**:  
```cpp
#include <bitset> auto result = std::bitset<4>("1010") <=> std::bitset<4>("1100");
```
**Example**: [bitset.cpp](../examples/C++20/bitset.cpp)

## Ranges Library
### std::ranges::range (C++20 Addition)
**Explanation**: Concept for types supporting range operations (e.g., `begin`, `end`).  
**Real-World Scenario**: Write a generic algorithm for any container in a data processor.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::range R> void process(R& r) {}
```
**Example**: [ranges_range.cpp](../examples/C++20/ranges_range.cpp)

### std::ranges::input_range (C++20 Addition)
**Explanation**: Concept for ranges supporting single-pass input iteration.  
**Real-World Scenario**: Process a stream of sensor data in a single pass.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::input_range R> void read(R& r) {}
```
**Example**: [ranges_input_range.cpp](../examples/C++20/ranges_input_range.cpp)

### std::ranges::output_range (C++20 Addition)
**Explanation**: Concept for ranges supporting output iteration.  
**Real-World Scenario**: Write data to an output buffer in a logging system.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::output_range<int> R> void write(R& r) {}
```
**Example**: [ranges_output_range.cpp](../examples/C++20/ranges_output_range.cpp)

### std::ranges::forward_range (C++20 Addition)
**Explanation**: Concept for ranges supporting multi-pass forward iteration.  
**Real-World Scenario**: Iterate over a list of game entities multiple times.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::forward_range R> void process(R& r) {}
```
**Example**: [ranges_forward_range.cpp](../examples/C++20/ranges_forward_range.cpp)

### std::ranges::bidirectional_range (C++20 Addition)
**Explanation**: Concept for ranges supporting bidirectional iteration.  
**Real-World Scenario**: Traverse a playlist forward and backward in a media player.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::bidirectional_range R> void traverse(R& r) {}
```
**Example**: [ranges_bidirectional_range.cpp](../examples/C++20/ranges_bidirectional_range.cpp)

### std::ranges::random_access_range (C++20 Addition)
**Explanation**: Concept for ranges supporting random access iteration.  
**Real-World Scenario**: Access elements directly in a game’s grid-based map.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::random_access_range R> void access(R& r) {}
```
**Example**: [ranges_random_access_range.cpp](../examples/C++20/ranges_random_access_range.cpp)

### std::ranges::contiguous_range (C++20 Addition)
**Explanation**: Concept for ranges with contiguous memory (e.g., arrays).  
**Real-World Scenario**: Process contiguous pixel data in a graphics renderer.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::contiguous_range R> void render(R& r) {}
```
**Example**: [ranges_contiguous_range.cpp](../examples/C++20/ranges_contiguous_range.cpp)

### std::ranges::sized_range (C++20 Addition)
**Explanation**: Concept for ranges with known size.  
**Real-World Scenario**: Check the size of a container in a memory manager.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::sized_range R> auto size(R& r) { return std::ranges::size(r); }
```
**Example**: [ranges_sized_range.cpp](../examples/C++20/ranges_sized_range.cpp)

### std::ranges::view (C++20 Addition)
**Explanation**: Concept for lightweight, non-owning ranges (e.g., views).  
**Real-World Scenario**: Apply a filter to a dataset without copying in a data processor.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::view V> void process(V v) {}
```
**Example**: [ranges_view.cpp](../examples/C++20/ranges_view.cpp)

### std::ranges::viewable_range (C++20 Addition)
**Explanation**: Concept for ranges that can be converted to views.  
**Real-World Scenario**: Convert a container to a view for processing in a pipeline.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::viewable_range R> void process(R& r) {}
```
**Example**: [ranges_viewable_range.cpp](../examples/C++20/ranges_viewable_range.cpp)

### std::ranges::borrowed_range (C++20 Addition)
**Explanation**: Concept for ranges safe to use after their iterator is invalidated.  
**Real-World Scenario**: Process a temporary range in a function without lifetime issues.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::borrowed_range R> void process(R& r) {}
```
**Example**: [ranges_borrowed_range.cpp](../examples/C++20/ranges_borrowed_range.cpp)

### std::ranges::common_range (C++20 Addition)
**Explanation**: Concept for ranges with identical iterator and sentinel types.  
**Real-World Scenario**: Simplify iteration over a container in a generic algorithm.  
**Snippet**:  
```cpp
#include <ranges> template<std::ranges::common_range R> void process(R& r) {}
```
**Example**: [ranges_common_range.cpp](../examples/C++20/ranges_common_range.cpp)

### std::ranges::range_value_t, range_reference_t, range_difference_t, range_size_t (C++20 Addition)
**Explanation**: Type traits for ranges (value type, reference type, difference type, size type).  
**Real-World Scenario**: Query range properties in a generic data processor.  
**Snippet**:  
```cpp
#include <ranges> using ValueT = std::ranges::range_value_t<std::vector<int>>;
```
**Example**: [ranges_traits.cpp](../examples/C++20/ranges_traits.cpp)

### std::ranges::begin, end, cbegin, cend, rbegin, rend, crbegin, crend (C++20 Addition)
**Explanation**: Range-based iterator access functions, including const and reverse variants.  
**Real-World Scenario**: Iterate over a container in a generic algorithm.  
**Snippet**:  
```cpp
#include <ranges> auto it = std::ranges::begin(vec);
```
**Example**: [ranges_iterators.cpp](../examples/C++20/ranges_iterators.cpp)

### std::ranges::size, ssize, empty, data, cdata (C++20 Addition)
**Explanation**: Functions to query range size, emptiness, or access raw data.  
**Real-World Scenario**: Check container properties in a memory manager.  
**Snippet**:  
```cpp
#include <ranges> auto s = std::ranges::size(vec); bool e = std::ranges::empty(vec);
```
**Example**: [ranges_utils.cpp](../examples/C++20/ranges_utils.cpp)

## Range Views
### std::ranges::all_view (C++20 Addition)
**Explanation**: View that includes all elements of a range.  
**Real-World Scenario**: Process an entire dataset in a pipeline.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::all_view{vec};
```
**Example**: [ranges_all_view.cpp](../examples/C++20/ranges_all_view.cpp)

### std::ranges::ref_view (C++20 Addition)
**Explanation**: Non-owning view of a range, referencing its elements.  
**Real-World Scenario**: Reference a container’s data without copying in a processor.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::ref_view{vec};
```
**Example**: [ranges_ref_view.cpp](../examples/C++20/ranges_ref_view.cpp)

### std::ranges::owning_view (C++20 Addition)
**Explanation**: Owning view that takes ownership of a range.  
**Real-World Scenario**: Manage a temporary container in a pipeline.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::owning_view{std::vector<int>{1, 2, 3}};
```
**Example**: [ranges_owning_view.cpp](../examples/C++20/ranges_owning_view.cpp)

### std::ranges::filter_view (C++20 Addition)
**Explanation**: View that filters elements based on a predicate.  
**Real-World Scenario**: Filter positive scores in a game’s leaderboard.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::filter_view(vec, [](int x) { return x > 0; });
```
**Example**: [ranges_filter_view.cpp](../examples/C++20/ranges_filter_view.cpp)

### std::ranges::transform_view (C++20 Addition)
**Explanation**: View that applies a transformation to each element.  
**Real-World Scenario**: Square all values in a dataset for analysis.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::transform_view(vec, [](int x) { return x * x; });
```
**Example**: [ranges_transform_view.cpp](../examples/C++20/ranges_transform_view.cpp)

### std::ranges::take_view (C++20 Addition)
**Explanation**: View that takes the first n elements of a range.  
**Real-World Scenario**: Process the first n items in a log.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::take_view(vec, 3);
```
**Example**: [ranges_take_view.cpp](../examples/C++20/ranges_take_view.cpp)

### std::ranges::take_while_view (C++20 Addition)
**Explanation**: View that takes elements while a predicate is true.  
**Real-World Scenario**: Process log entries until an error is found.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::take_while_view(vec, [](int x) { return x > 0; });
```
**Example**: [ranges_take_while_view.cpp](../examples/C++20/ranges_take_while_view.cpp)

### std::ranges::drop_view (C++20 Addition)
**Explanation**: View that skips the first n elements of a range.  
**Real-World Scenario**: Skip header lines in a data file.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::drop_view(vec, 2);
```
**Example**: [ranges_drop_view.cpp](../examples/C++20/ranges_drop_view.cpp)

### std::ranges::drop_while_view (C++20 Addition)
**Explanation**: View that skips elements while a predicate is true.  
**Real-World Scenario**: Skip invalid entries in a dataset.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::drop_while_view(vec, [](int x) { return x < 0; });
```
**Example**: [ranges_drop_while_view.cpp](../examples/C++20/ranges_drop_while_view.cpp)

### std::ranges::join_view (C++20 Addition)
**Explanation**: View that flattens a range of ranges into a single range.  
**Real-World Scenario**: Flatten a list of lists in a data aggregator.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::join_view(vec_of_vecs);
```
**Example**: [ranges_join_view.cpp](../examples/C++20/ranges_join_view.cpp)

### std::ranges::split_view (C++20 Addition)
**Explanation**: View that splits a range into subranges based on a delimiter.  
**Real-World Scenario**: Split a string into tokens in a parser.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::split_view(str, ',');
```
**Example**: [ranges_split_view.cpp](../examples/C++20/ranges_split_view.cpp)

### std::ranges::counted_view (C++20 Addition)
**Explanation**: View that represents a counted range of elements.  
**Real-World Scenario**: Process a fixed number of elements from an iterator.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::counted_view(vec.begin(), 3);
```
**Example**: [ranges_counted_view.cpp](../examples/C++20/ranges_counted_view.cpp)

### std::ranges::common_view (C++20 Addition)
**Explanation**: View that ensures a common iterator and sentinel type.  
**Real-World Scenario**: Simplify iteration in a generic algorithm.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::common_view{vec};
```
**Example**: [ranges_common_view.cpp](../examples/C++20/ranges_common_view.cpp)

### std::ranges::reverse_view (C++20 Addition)
**Explanation**: View that reverses the order of a range’s elements.  
**Real-World Scenario**: Process a log in reverse order for debugging.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::reverse_view{vec};
```
**Example**: [ranges_reverse_view.cpp](../examples/C++20/ranges_reverse_view.cpp)

### std::ranges::elements_view (C++20 Addition)
**Explanation**: View that extracts elements from tuples or pairs in a range.  
**Real-World Scenario**: Extract keys from a range of key-value pairs.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::elements_view<0>{vec_of_pairs};
```
**Example**: [ranges_elements_view.cpp](../examples/C++20/ranges_elements_view.cpp)

### std::ranges::keys_view (C++20 Addition)
**Explanation**: View that extracts keys from a range of key-value pairs.  
**Real-World Scenario**: Process only keys from a map in a configuration system.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::keys_view{map};
```
**Example**: [ranges_keys_view.cpp](../examples/C++20/ranges_keys_view.cpp)

### std::ranges::values_view (C++20 Addition)
**Explanation**: View that extracts values from a range of key-value pairs.  
**Real-World Scenario**: Process values from a map in a data processor.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::values_view{map};
```
**Example**: [ranges_values_view.cpp](../examples/C++20/ranges_values_view.cpp)

### std::ranges::iota_view (C++20 Addition)
**Explanation**: View that generates a sequence of incrementing values.  
**Real-World Scenario**: Generate indices for a loop in a game engine.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::iota_view(0, 10);
```
**Example**: [ranges_iota_view.cpp](../examples/C++20/ranges_iota_view.cpp)

### std::ranges::empty_view (C++20 Addition)
**Explanation**: View representing an empty range.  
**Real-World Scenario**: Provide a default empty range in a data pipeline.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::empty_view<int>{};
```
**Example**: [ranges_empty_view.cpp](../examples/C++20/ranges_empty_view.cpp)

### std::ranges::single_view (C++20 Addition)
**Explanation**: View containing a single element.  
**Real-World Scenario**: Wrap a single value in a range for generic processing.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::single_view{42};
```
**Example**: [ranges_single_view.cpp](../examples/C++20/ranges_single_view.cpp)

### std::ranges::repeat_view (C++20 Addition)
**Explanation**: View that repeats a value indefinitely or a specified number of times.  
**Real-World Scenario**: Generate a constant stream of default values for testing.  
**Snippet**:  
```cpp
#include <ranges> auto v = std::ranges::repeat_view{42, 5};
```
**Example**: [ranges_repeat_view.cpp](../examples/C++20/ranges_repeat_view.cpp)

## Range Adaptors
### std::ranges::views::all, filter, transform, take, take_while, drop, drop_while, join, split, common, reverse, elements, keys, values, iota, empty, single, repeat (C++20 Addition)
**Explanation**: Adaptors for creating views with specific transformations or selections.  
**Real-World Scenario**: Chain transformations to process a dataset in a pipeline (e.g., filter, transform, take).  
**Snippet**:  
```cpp
#include <ranges> auto v = vec | std::views::filter([](int x) { return x > 0; }) | std::views::transform([](int x) { return x * x; });
```
**Example**: [ranges_adaptors.cpp](../examples/C++20/ranges_adaptors.cpp)

## Range Algorithms
### std::ranges::for_each, for_each_n, find, find_if, find_if_not, find_end, find_first_of, adjacent_find, count, count_if, mismatch, equal, search, search_n, copy, copy_if, copy_n, copy_backward, move, move_backward, fill, fill_n, transform, generate, generate_n, remove, remove_if, replace, replace_if, swap_ranges, reverse, reverse_copy, rotate, rotate_copy, unique, unique_copy, partition, stable_partition, sort, stable_sort, partial_sort, partial_sort_copy, nth_element, merge, inplace_merge, includes, set_union, set_intersection, set_difference, set_symmetric_difference, push_heap, pop_heap, make_heap, sort_heap, min, max, minmax, min_element, max_element, minmax_element, lexicographical_compare, next_permutation, prev_permutation, all_of, any_of, none_of, is_sorted, is_sorted_until, is_permutation, is_heap, is_heap_until (C++20 Addition)
**Explanation**: Range-based versions of STL algorithms, supporting ranges and projections.  
**Real-World Scenario**: Sort a leaderboard’s scores using a range-based algorithm with a custom projection.  
**Snippet**:  
```cpp
#include <ranges> std::ranges::sort(vec, {}, &Score::value);
```
**Example**: [ranges_algorithms.cpp](../examples/C++20/ranges_algorithms.cpp)

## Algorithms
### std::shift_left, std::shift_right (C++20 Addition)
**Explanation**: Shifts elements in a range left or right, filling with default values.  
**Real-World Scenario**: Rotate elements in a game’s inventory array.  
**Snippet**:  
```cpp
#include <algorithm> std::shift_left(vec.begin(), vec.end(), 2);
```
**Example**: [shift.cpp](../examples/C++20/shift.cpp)

### std::starts_with, std::ends_with (C++20 Addition)
**Explanation**: Checks if a range starts or ends with a subrange.  
**Real-World Scenario**: Verify a command sequence in a protocol parser.  
**Snippet**:  
```cpp
#include <algorithm> bool starts = std::ranges::starts_with(vec, subvec);
```
**Example**: [starts_ends_with.cpp](../examples/C++20/starts_ends_with.cpp)

### std::contains (C++20 Addition)
**Explanation**: Checks if a range contains a specific value (via `std::ranges`).  
**Real-World Scenario**: Check if a user ID exists in a membership list.  
**Snippet**:  
```cpp
#include <algorithm> bool has = std::ranges::contains(vec, 42);
```
**Example**: [contains.cpp](../examples/C++20/contains.cpp)

### std::erase, std::erase_if (C++20 Addition)
**Explanation**: Removes elements from containers directly, simplifying erasure.  
**Real-World Scenario**: Remove invalid entries from a game’s entity list.  
**Snippet**:  
```cpp
#include <vector> std::erase_if(vec, [](int x) { return x < 0; });
```
**Example**: [erase.cpp](../examples/C++20/erase.cpp)

## Utilities
### std::bit_cast (C++20 Addition)
**Explanation**: Reinterprets bits of one type as another, type-safe.  
**Real-World Scenario**: Convert a float to its raw bits in a serialization system.  
**Snippet**:  
```cpp
#include <bit> auto bits = std::bit_cast<std::uint32_t>(3.14f);
```
**Example**: [bit_cast.cpp](../examples/C++20/bit_cast.cpp)

### std::format (C++20 Addition)
**Explanation**: Type-safe string formatting with Python-like syntax.  
**Real-World Scenario**: Format log messages in a logging system.  
**Snippet**:  
```cpp
#include <format> auto s = std::format("Value: {}", 42);
```
**Example**: [format.cpp](../examples/C++20/format.cpp)

### std::syncbuf, std::osyncstream (C++20 Addition)
**Explanation**: Synchronized output streams for thread-safe logging.  
**Real-World Scenario**: Log messages from multiple threads in a server.  
**Snippet**:  
```cpp
#include <syncstream> std::osyncstream(std::cout) << "Thread-safe log";
```
**Example**: [syncstream.cpp](../examples/C++20/syncstream.cpp)

### std::bind_front (C++20 Addition)
**Explanation**: Binds arguments to the front of a callable, simpler than `std::bind`.  
**Real-World Scenario**: Pre-bind a logger’s prefix in a logging system.  
**Snippet**:  
```cpp
#include <functional> auto bound = std::bind_front(func, "log");
```
**Example**: [bind_front.cpp](../examples/C++20/bind_front.cpp)

### std::identity (C++20 Addition)
**Explanation**: Transparent function object that returns its argument unchanged.  
**Real-World Scenario**: Use as a default projection in a range algorithm.  
**Snippet**:  
```cpp
#include <functional> std::ranges::sort(vec, {}, std::identity{});
```
**Example**: [identity.cpp](../examples/C++20/identity.cpp)

### std::unwrap_reference, std::unwrap_ref_decay (C++20 Addition)
**Explanation**: Utilities to unwrap reference wrappers in templates.  
**Real-World Scenario**: Handle reference-wrapped types in a generic function.  
**Snippet**:  
```cpp
#include <functional> using T = std::unwrap_reference_t<std::reference_wrapper<int>>;
```
**Example**: [unwrap_reference.cpp](../examples/C++20/unwrap_reference.cpp)

### std::midpoint (C++20 Addition)
**Explanation**: Computes the midpoint of two values, avoiding overflow.  
**Real-World Scenario**: Calculate the middle index of a range in a search algorithm.  
**Snippet**:  
```cpp
#include <numeric> auto mid = std::midpoint(0, 100);
```
**Example**: [midpoint.cpp](../examples/C++20/midpoint.cpp)

### std::lerp (C++20 Addition)
**Explanation**: Linear interpolation between two values.  
**Real-World Scenario**: Interpolate positions in a game’s animation system.  
**Snippet**:  
```cpp
#include <cmath> float pos = std::lerp(0.0f, 100.0f, 0.5f);
```
**Example**: [lerp.cpp](../examples/C++20/lerp.cpp)

### std::to_array (C++20 Addition)
**Explanation**: Converts C-style arrays or initializer lists to `std::array`.  
**Real-World Scenario**: Convert a fixed-size input to a safe array in a game.  
**Snippet**:  
```cpp
#include <array> auto arr = std::to_array({1, 2, 3});
```
**Example**: [to_array.cpp](../examples/C++20/to_array.cpp)

## Bit Operations
### std::bit_ceil, bit_floor, bit_width, countl_zero, countl_one, countr_zero, countr_one, has_single_bit, popcount, rotl, rotr (C++20 Addition)
**Explanation**: Functions for bit manipulation (e.g., ceiling, counting zeros, rotation).  
**Real-World Scenario**: Optimize bit operations in a permissions system.  
**Snippet**:  
```cpp
#include <bit> auto ceil = std::bit_ceil(10); auto count = std::popcount(0b1010);
```
**Example**: [bit_operations.cpp](../examples/C++20/bit_operations.cpp)

## Chrono Extensions
### std::chrono::day, month, year, weekday, weekday_indexed, weekday_last, month_day, month_day_last, month_weekday, month_weekday_last, year_month, year_month_day, year_month_day_last, year_month_weekday, year_month_weekday_last (C++20 Addition)
**Explanation**: Calendar types for precise date manipulation.  
**Real-World Scenario**: Schedule events with specific dates in a calendar app.  
**Snippet**:  
```cpp
#include <chrono> auto date = std::chrono::year_month_day{std::chrono::year{2025}, std::chrono::month{9}, std::chrono::day{7}};
```
**Example**: [chrono_calendar.cpp](../examples/C++20/chrono_calendar.cpp)

### std::chrono::local_time, zoned_time, time_zone, sys_time, utc_clock, tai_clock, gps_clock, file_clock, local_days, local_seconds (C++20 Addition)
**Explanation**: Time zone and clock types for time manipulation.  
**Real-World Scenario**: Convert event times across time zones in a global app.  
**Snippet**:  
```cpp
#include <chrono> auto zt = std::chrono::zoned_time{"UTC", std::chrono::system_clock::now()};
```
**Example**: [chrono_timezones.cpp](../examples/C++20/chrono_timezones.cpp)

## Threading
### std::jthread (C++20 Addition)
**Explanation**: Thread type with automatic joining and cancellation support.  
**Real-World Scenario**: Run a background task in a server with clean shutdown.  
**Snippet**:  
```cpp
#include <thread> std::jthread t([]{ /* work */ });
```
**Example**: [jthread.cpp](../examples/C++20/jthread.cpp)

### std::stop_token, std::stop_source (C++20 Addition)
**Explanation**: Mechanisms for cooperative thread cancellation.  
**Real-World Scenario**: Cancel a long-running task in a server application.  
**Snippet**:  
```cpp
#include <stop_token> void task(std::stop_token st) { if (st.stop_requested()) return; }
```
**Example**: [stop_token.cpp](../examples/C++20/stop_token.cpp)

### std::latch (C++20 Addition)
**Explanation**: Synchronization primitive for one-time event coordination.  
**Real-World Scenario**: Coordinate startup of multiple threads in a game engine.  
**Snippet**:  
```cpp
#include <latch> std::latch l(2); l.arrive_and_wait();
```
**Example**: [latch.cpp](../examples/C++20/latch.cpp)

### std::barrier (C++20 Addition)
**Explanation**: Synchronization primitive for repeated coordination of threads.  
**Real-World Scenario**: Synchronize phases in a parallel physics simulation.  
**Snippet**:  
```cpp
#include <barrier> std::barrier b(2); b.arrive_and_wait();
```
**Example**: [barrier.cpp](../examples/C++20/barrier.cpp)

### std::semaphore, std::counting_semaphore (C++20 Addition)
**Explanation**: Synchronization primitives for resource counting.  
**Real-World Scenario**: Limit concurrent access to a resource pool in a server.  
**Snippet**:  
```cpp
#include <semaphore> std::counting_semaphore<10> sem(5); sem.acquire();
```
**Example**: [semaphore.cpp](../examples/C++20/semaphore.cpp)

### std::atomic_ref (C++20 Addition)
**Explanation**: Atomic operations on non-atomic objects via references.  
**Real-World Scenario**: Perform atomic updates on shared data in a game.  
**Snippet**:  
```cpp
#include <atomic> int x; std::atomic_ref<int> ref(x); ref++;
```
**Example**: [atomic_ref.cpp](../examples/C++20/atomic_ref.cpp)

### std::atomic_flag Enhancements (C++20 Evolution)
**Explanation**: Adds `test`, `wait`, `notify_one`, and `notify_all` for `std::atomic_flag`.  
**Real-World Scenario**: Signal completion of tasks in a thread pool.  
**Snippet**:  
```cpp
#include <atomic> std::atomic_flag flag; flag.test_and_set();
```
**Example**: [atomic_flag.cpp](../examples/C++20/atomic_flag.cpp)