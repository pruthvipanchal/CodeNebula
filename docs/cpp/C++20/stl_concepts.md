# C++20 STL Concepts

This document covers new or evolved C++20 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++20/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17 are included.

## Containers
### std::span (C++20 Addition)

**Explanation**: Non-owning view over a contiguous sequence of elements, providing bounds-safe access without ownership semantics. Replaces the error-prone pattern of passing a pointer and a size as separate parameters.

**Real-World Scenario**: Pass a subset of a vertex buffer to a rendering function in a game engine without copying data or losing size information.

**Snippet**:
```cpp
#include <span>
#include <vector>

void render(std::span<const float> vertices) {
    for (float v : vertices) { /* process vertex */ }
}

std::vector<float> buffer = {1.0f, 2.0f, 3.0f, 4.0f};
render(buffer);                          // entire buffer
render(std::span{buffer}.subspan(0, 2)); // first two elements
```

**Example**: [span.cpp](../../examples/C++20/span.cpp)

## Concepts Library
### std::same_as (C++20 Addition)

**Explanation**: Concept that checks whether two types are exactly the same (symmetric: `same_as<A, B>` implies `same_as<B, A>`). Fundamental building block for constraining templates to accept only specific types.

**Real-World Scenario**: Constrain a serialization function to accept only `std::string`, preventing accidental implicit conversions from string literals or string views.

**Snippet**:
```cpp
#include <concepts>

template<std::same_as<std::string> T>
void serialize(const T& data) {
    // Only std::string accepted, not const char* or string_view
}
```

**Example**: [same_as.cpp](../../examples/C++20/same_as.cpp)

### std::derived_from (C++20 Addition)

**Explanation**: Concept that checks if a type is publicly and unambiguously derived from a base type. Unlike `std::is_base_of`, it enforces public inheritance, preventing accidental use of privately derived types.

**Real-World Scenario**: Constrain a plugin registration system to accept only classes derived from a `Plugin` base class.

**Snippet**:
```cpp
#include <concepts>

struct Plugin { virtual void execute() = 0; };
struct AudioPlugin : Plugin { void execute() override {} };

template<std::derived_from<Plugin> T>
void register_plugin(T& plugin) {
    plugin.execute();
}
```

**Example**: [derived_from.cpp](../../examples/C++20/derived_from.cpp)

### std::convertible_to (C++20 Addition)

**Explanation**: Concept that checks if a type can be both implicitly and explicitly converted to another type. Stricter than `std::is_convertible` as it also verifies explicit `static_cast` works.

**Real-World Scenario**: Ensure a function accepts any type that can safely convert to `double` in a scientific computation library.

**Snippet**:
```cpp
#include <concepts>

template<std::convertible_to<double> T>
double to_celsius(T fahrenheit) {
    return (static_cast<double>(fahrenheit) - 32.0) * 5.0 / 9.0;
}
```

**Example**: [convertible_to.cpp](../../examples/C++20/convertible_to.cpp)

### std::integral (C++20 Addition)

**Explanation**: Concept that constrains a type to be an integral type (bool, char, int, long, etc.). Replaces verbose `std::enable_if_t<std::is_integral_v<T>>` patterns with a clean, readable constraint.

**Real-World Scenario**: Implement a bit manipulation utility that only accepts integer types, preventing floating-point arguments at compile time.

**Snippet**:
```cpp
#include <concepts>

template<std::integral T>
T set_bit(T value, int pos) {
    return value | (T{1} << pos);
}
```

**Example**: [integral.cpp](../../examples/C++20/integral.cpp)

### std::floating_point (C++20 Addition)

**Explanation**: Concept that constrains a type to be a floating-point type (float, double, long double). Provides clean syntax for numeric functions that require real-number arithmetic.

**Real-World Scenario**: Build a physics engine's force calculator that only accepts floating-point types to ensure correct continuous math.

**Snippet**:
```cpp
#include <concepts>
#include <cmath>

template<std::floating_point T>
T gravitational_force(T m1, T m2, T distance) {
    constexpr T G = T(6.674e-11);
    return G * m1 * m2 / (distance * distance);
}
```

**Example**: [floating_point.cpp](../../examples/C++20/floating_point.cpp)

### std::signed_integral / std::unsigned_integral (C++20 Addition)

**Explanation**: Concepts that refine `std::integral` to distinguish signed and unsigned integer types. `signed_integral` matches types where `std::is_signed_v` is true; `unsigned_integral` matches the complement. Prevents subtle bugs from signed/unsigned mixing.

**Real-World Scenario**: Implement a safe subtraction function that only operates on signed integers, avoiding undefined behavior from unsigned underflow.

**Snippet**:
```cpp
#include <concepts>
#include <stdexcept>

template<std::signed_integral T>
T safe_subtract(T a, T b) {
    if (b > 0 && a < std::numeric_limits<T>::min() + b)
        throw std::overflow_error("underflow");
    return a - b;
}

template<std::unsigned_integral T>
T safe_add(T a, T b) {
    if (a > std::numeric_limits<T>::max() - b)
        throw std::overflow_error("overflow");
    return a + b;
}
```

**Example**: [signed_unsigned_integral.cpp](../../examples/C++20/signed_unsigned_integral.cpp)

### std::common_reference_with (C++20 Addition)

**Explanation**: Concept that checks whether two types share a common reference type to which both can be converted. Essential for range and iterator concepts where comparing iterators of different types requires a shared reference.

**Real-World Scenario**: Write a generic merge function that works with iterators from different container types as long as they share a common element reference.

**Snippet**:
```cpp
#include <concepts>
#include <vector>
#include <list>

template<typename T, typename U>
    requires std::common_reference_with<T, U>
auto select(bool cond, T&& a, U&& b) -> std::common_reference_t<T, U> {
    return cond ? std::forward<T>(a) : std::forward<U>(b);
}
```

**Example**: [common_reference_with.cpp](../../examples/C++20/common_reference_with.cpp)

### std::common_with (C++20 Addition)

**Explanation**: Concept that checks if two types share a common type to which both can be converted. Unlike `common_reference_with`, this deals with value types rather than references. Used extensively in the ranges library to determine result types.

**Real-World Scenario**: Build a generic `clamp` utility that works across mixed numeric types (e.g., int and double) by deducing the common result type.

**Snippet**:
```cpp
#include <concepts>

template<typename T, typename U>
    requires std::common_with<T, U>
auto safe_max(T a, U b) -> std::common_type_t<T, U> {
    return a > b ? a : b;
}

// safe_max(3, 4.5) returns double
```

**Example**: [common_with.cpp](../../examples/C++20/common_with.cpp)

### std::assignable_from (C++20 Addition)

**Explanation**: Concept that verifies a type can be assigned from another type via the assignment operator. Checks that the assignment expression is valid and returns the correct reference type.

**Real-World Scenario**: Constrain a generic `fill` algorithm to only accept output types that can actually be assigned from the given value type.

**Snippet**:
```cpp
#include <concepts>

template<typename Container, typename Value>
    requires std::assignable_from<
        std::ranges::range_reference_t<Container>, const Value&>
void fill_container(Container& c, const Value& val) {
    for (auto& elem : c) elem = val;
}
```

**Example**: [assignable_from.cpp](../../examples/C++20/assignable_from.cpp)

### std::swappable (C++20 Addition)

**Explanation**: Concept that checks if a type (or pair of types with `swappable_with`) can be swapped using `std::ranges::swap`. Accounts for both member swap and ADL-found swap overloads.

**Real-World Scenario**: Implement a generic sorting algorithm that requires its elements to be swappable.

**Snippet**:
```cpp
#include <concepts>

template<std::swappable T>
void bubble_sort(std::vector<T>& vec) {
    for (std::size_t i = 0; i < vec.size(); ++i)
        for (std::size_t j = i + 1; j < vec.size(); ++j)
            if (vec[j] < vec[i])
                std::ranges::swap(vec[i], vec[j]);
}
```

**Example**: [swappable.cpp](../../examples/C++20/swappable.cpp)

### std::destructible (C++20 Addition)

**Explanation**: Concept that checks if a type can be destroyed (its destructor is noexcept and callable). A foundational concept required by most other object concepts.

**Real-World Scenario**: Constrain an object pool to only manage types that can be safely destroyed during cleanup.

**Snippet**:
```cpp
#include <concepts>

template<std::destructible T>
class ObjectPool {
    std::vector<T> pool;
public:
    void clear() { pool.clear(); }  // safe: T is guaranteed destructible
};
```

**Example**: [destructible.cpp](../../examples/C++20/destructible.cpp)

### std::constructible_from (C++20 Addition)

**Explanation**: Concept that checks if a type can be constructed from a given set of argument types. Combines `destructible` with a check that the constructor expression is valid.

**Real-World Scenario**: Build a factory function that constructs objects only when the given arguments match a valid constructor signature.

**Snippet**:
```cpp
#include <concepts>

template<typename T, typename... Args>
    requires std::constructible_from<T, Args...>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

auto s = make<std::string>(5, 'a');  // "aaaaa"
```

**Example**: [constructible_from.cpp](../../examples/C++20/constructible_from.cpp)

### std::default_initializable (C++20 Addition)

**Explanation**: Concept that checks if a type can be default-constructed, value-initialized, and default-initialized. Stricter than just checking for a default constructor.

**Real-World Scenario**: Implement a generic container that resizes by default-constructing new elements, requiring the element type to be default-initializable.

**Snippet**:
```cpp
#include <concepts>

template<std::default_initializable T>
class ResizableBuffer {
    std::vector<T> data;
public:
    void resize(std::size_t n) { data.resize(n); }  // requires default construction
};
```

**Example**: [default_initializable.cpp](../../examples/C++20/default_initializable.cpp)

### std::move_constructible (C++20 Addition)

**Explanation**: Concept that checks if a type can be constructed from an rvalue of itself. Essential for types that participate in move semantics, enabling efficient transfer of resources.

**Real-World Scenario**: Constrain a task queue to only accept task types that can be moved into the queue, ensuring efficient ownership transfer.

**Snippet**:
```cpp
#include <concepts>
#include <queue>

template<std::move_constructible Task>
class TaskQueue {
    std::queue<Task> tasks;
public:
    void enqueue(Task task) { tasks.push(std::move(task)); }
};
```

**Example**: [move_constructible.cpp](../../examples/C++20/move_constructible.cpp)

### std::copy_constructible (C++20 Addition)

**Explanation**: Concept that checks if a type can be copy-constructed from an lvalue. Refines `move_constructible` by also requiring copies from `const T&` and `T&` to work.

**Real-World Scenario**: Implement a snapshot system that clones the current state, requiring all components to be copyable.

**Snippet**:
```cpp
#include <concepts>

template<std::copy_constructible State>
class Snapshotter {
    std::vector<State> history;
public:
    void snapshot(const State& current) {
        history.push_back(current);  // requires copy construction
    }
};
```

**Example**: [copy_constructible.cpp](../../examples/C++20/copy_constructible.cpp)

### std::equality_comparable (C++20 Addition)

**Explanation**: Concept that checks if a type supports `==` and `!=` operators with boolean results. The two-type variant `equality_comparable_with` checks cross-type equality.

**Real-World Scenario**: Constrain a deduplication algorithm to types that can be compared for equality.

**Snippet**:
```cpp
#include <concepts>
#include <vector>
#include <algorithm>

template<std::equality_comparable T>
std::vector<T> deduplicate(std::vector<T> items) {
    std::vector<T> result;
    for (auto& item : items)
        if (std::ranges::find(result, item) == result.end())
            result.push_back(std::move(item));
    return result;
}
```

**Example**: [equality_comparable.cpp](../../examples/C++20/equality_comparable.cpp)

### std::totally_ordered (C++20 Addition)

**Explanation**: Concept that checks if a type supports all six comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) and that the ordering is consistent (a total order). Enables use in sorting and ordered containers.

**Real-World Scenario**: Constrain a priority queue to only accept types with a total ordering, guaranteeing deterministic sorting behavior.

**Snippet**:
```cpp
#include <concepts>

template<std::totally_ordered T>
class PriorityQueue {
    std::vector<T> heap;
public:
    void push(T value) {
        heap.push_back(std::move(value));
        std::ranges::push_heap(heap);
    }
    T pop() {
        std::ranges::pop_heap(heap);
        T top = std::move(heap.back());
        heap.pop_back();
        return top;
    }
};
```

**Example**: [totally_ordered.cpp](../../examples/C++20/totally_ordered.cpp)

### std::regular (C++20 Addition)

**Explanation**: Concept combining `semiregular` and `equality_comparable`. A regular type behaves like a built-in value type: it can be default-constructed, copied, moved, assigned, swapped, and compared for equality.

**Real-World Scenario**: Constrain elements of a generic value-semantic container to types that behave like proper values, enabling predictable copy and comparison semantics.

**Snippet**:
```cpp
#include <concepts>

template<std::regular T>
class ValueStore {
    std::vector<T> items;
public:
    bool contains(const T& value) const {
        return std::ranges::find(items, value) != items.end();
    }
    void add(T value) { items.push_back(std::move(value)); }
};
```

**Example**: [regular.cpp](../../examples/C++20/regular.cpp)

### std::semiregular (C++20 Addition)

**Explanation**: Concept requiring a type to be default-initializable, copyable, movable, assignable, and swappable -- everything a `regular` type needs except equality comparison. Models types that are "value-like" but lack `==`.

**Real-World Scenario**: Constrain a function object wrapper that stores callable objects which may not support equality comparison but must be copyable and default-constructible.

**Snippet**:
```cpp
#include <concepts>

template<std::semiregular Func>
class CallbackHolder {
    Func callback{};
public:
    CallbackHolder() = default;
    CallbackHolder(Func f) : callback(std::move(f)) {}
    void invoke() { callback(); }
};
```

**Example**: [semiregular.cpp](../../examples/C++20/semiregular.cpp)

### std::invocable / std::regular_invocable (C++20 Addition)

**Explanation**: Concept that checks if a callable can be invoked with the given argument types using `std::invoke`. `regular_invocable` adds the semantic requirement that calling it does not modify the callable or its arguments (equality-preserving).

**Real-World Scenario**: Constrain a generic event system's handler registration to accept only callables with the correct signature.

**Snippet**:
```cpp
#include <concepts>
#include <functional>

template<std::invocable<int, int> F>
int apply_operation(F&& func, int a, int b) {
    return std::invoke(std::forward<F>(func), a, b);
}

auto result = apply_operation(std::plus<>{}, 3, 4);  // 7
```

**Example**: [invocable.cpp](../../examples/C++20/invocable.cpp)

### std::predicate (C++20 Addition)

**Explanation**: Concept that refines `regular_invocable` to require the return type to be convertible to `bool`. Models functions that answer a yes/no question about their arguments.

**Real-World Scenario**: Constrain a filter function to only accept callables that return a boolean result.

**Snippet**:
```cpp
#include <concepts>
#include <vector>

template<typename T, std::predicate<const T&> Pred>
std::vector<T> filter(const std::vector<T>& items, Pred pred) {
    std::vector<T> result;
    for (auto& item : items)
        if (pred(item)) result.push_back(item);
    return result;
}

auto positives = filter(numbers, [](int n) { return n > 0; });
```

**Example**: [predicate.cpp](../../examples/C++20/predicate.cpp)

### std::relation (C++20 Addition)

**Explanation**: Concept that checks if a callable defines a binary relation over two types -- it must be a predicate that accepts two arguments (possibly of different types). Used to constrain comparators in algorithms.

**Real-World Scenario**: Constrain a generic merge function's comparator to be a valid relation over the element types.

**Snippet**:
```cpp
#include <concepts>
#include <functional>

template<typename T, std::relation<T, T> Compare = std::less<T>>
T select_min(T a, T b, Compare comp = {}) {
    return comp(a, b) ? a : b;
}

auto m = select_min(5, 3);  // 3
```

**Example**: [relation.cpp](../../examples/C++20/relation.cpp)

## Ranges Library
### std::ranges::range (C++20 Addition)

**Explanation**: The fundamental concept for types supporting range operations -- any type where `std::ranges::begin()` and `std::ranges::end()` produce a valid iterator-sentinel pair.

**Real-World Scenario**: Write a generic algorithm that works with any container, C-array, or custom range in a data processing pipeline.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

template<std::ranges::range R>
void process(R&& r) {
    for (auto&& elem : r) { /* process element */ }
}
```

**Example**: [ranges_range.cpp](../../examples/C++20/ranges_range.cpp)

### std::ranges::input_range (C++20 Addition)

**Explanation**: Concept for ranges that support at least single-pass input iteration. The weakest range concept that still allows reading elements.

**Real-World Scenario**: Process a stream of sensor readings where data can only be consumed once (e.g., from a network socket adapter).

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::input_range R>
auto sum(R&& r) {
    std::ranges::range_value_t<R> total{};
    for (auto&& elem : r) total += elem;
    return total;
}
```

**Example**: [ranges_input_range.cpp](../../examples/C++20/ranges_input_range.cpp)

### std::ranges::output_range (C++20 Addition)

**Explanation**: Concept for ranges that support writing values of a specific type through their iterators. Parameterized on both the range type and the value type being written.

**Real-World Scenario**: Write processed results to an output buffer in a signal processing pipeline.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::output_range<int> R>
void fill_with_zeros(R&& r) {
    for (auto&& elem : r) elem = 0;
}
```

**Example**: [ranges_output_range.cpp](../../examples/C++20/ranges_output_range.cpp)

### std::ranges::forward_range (C++20 Addition)

**Explanation**: Concept for ranges supporting multi-pass forward iteration. Iterators can be copied and independently advanced, enabling algorithms that need multiple passes over data.

**Real-World Scenario**: Implement a pattern-matching algorithm on a linked list of tokens that requires looking ahead and backtracking.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::forward_range R>
bool has_duplicates(R&& r) {
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it)
        for (auto jt = std::next(it); jt != std::ranges::end(r); ++jt)
            if (*it == *jt) return true;
    return false;
}
```

**Example**: [ranges_forward_range.cpp](../../examples/C++20/ranges_forward_range.cpp)

### std::ranges::bidirectional_range (C++20 Addition)

**Explanation**: Concept for ranges whose iterators can move both forward and backward. Required by algorithms like `reverse` and `partition` that need to traverse from both ends.

**Real-World Scenario**: Traverse a playlist forward and backward in a media player's queue system.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::bidirectional_range R>
void reverse_in_place(R&& r) {
    auto first = std::ranges::begin(r);
    auto last = std::ranges::end(r);
    while (first != last && first != --last)
        std::ranges::iter_swap(first++, last);
}
```

**Example**: [ranges_bidirectional_range.cpp](../../examples/C++20/ranges_bidirectional_range.cpp)

### std::ranges::random_access_range (C++20 Addition)

**Explanation**: Concept for ranges supporting constant-time indexed access and arbitrary iterator jumps. Enables O(1) element access and efficient sorting.

**Real-World Scenario**: Implement a binary search on a sorted leaderboard stored in a random-access container.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::random_access_range R>
auto binary_search(R&& r, const std::ranges::range_value_t<R>& val) {
    auto lo = std::ranges::begin(r);
    auto hi = std::ranges::end(r);
    while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (*mid < val) lo = mid + 1; else hi = mid;
    }
    return lo;
}
```

**Example**: [ranges_random_access_range.cpp](../../examples/C++20/ranges_random_access_range.cpp)

### std::ranges::contiguous_range (C++20 Addition)

**Explanation**: Concept for ranges whose elements are stored in contiguous memory, allowing direct pointer access via `std::ranges::data()`. The strongest range concept.

**Real-World Scenario**: Pass pixel data directly to a GPU upload function that requires a raw pointer to contiguous memory.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::contiguous_range R>
void upload_to_gpu(R&& r) {
    const auto* ptr = std::ranges::data(r);
    auto size = std::ranges::size(r);
    // gpu_upload(ptr, size * sizeof(std::ranges::range_value_t<R>));
}
```

**Example**: [ranges_contiguous_range.cpp](../../examples/C++20/ranges_contiguous_range.cpp)

### std::ranges::sized_range (C++20 Addition)

**Explanation**: Concept for ranges that can report their size in constant time via `std::ranges::size()`. Not all ranges know their size (e.g., filtered views), so this concept lets algorithms optimize when size is available.

**Real-World Scenario**: Pre-allocate an output buffer to the exact size of an input range before processing.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

template<std::ranges::sized_range R>
auto to_vector(R&& r) {
    std::vector<std::ranges::range_value_t<R>> result;
    result.reserve(std::ranges::size(r));
    for (auto&& elem : r) result.push_back(elem);
    return result;
}
```

**Example**: [ranges_sized_range.cpp](../../examples/C++20/ranges_sized_range.cpp)

### std::ranges::view (C++20 Addition)

**Explanation**: Concept for lightweight, non-owning range types that are cheap to copy and move. Views do not own their elements and are the building blocks of range pipelines.

**Real-World Scenario**: Chain lazy transformations in a data pipeline without materializing intermediate collections.

**Snippet**:
```cpp
#include <ranges>

template<std::ranges::view V>
void consume_view(V v) {
    for (auto&& elem : v) { /* process */ }
}

auto v = std::views::iota(1, 100) | std::views::filter([](int n) { return n % 2 == 0; });
consume_view(v);
```

**Example**: [ranges_view.cpp](../../examples/C++20/ranges_view.cpp)

### std::ranges::viewable_range (C++20 Addition)

**Explanation**: Concept for ranges that can be converted to a view using `std::views::all`. This includes views themselves, lvalue references to ranges, and movable ranges. It is the gateway concept for pipe syntax.

**Real-World Scenario**: Accept any container or view as input to a pipeline entry point.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

template<std::ranges::viewable_range R>
auto make_pipeline(R&& r) {
    return std::views::all(std::forward<R>(r))
         | std::views::take(10);
}
```

**Example**: [ranges_viewable_range.cpp](../../examples/C++20/ranges_viewable_range.cpp)

### std::ranges::borrowed_range (C++20 Addition)

**Explanation**: Concept for ranges whose iterators remain valid even after the range object is destroyed. Prevents dangling iterators when algorithms return iterators into temporary ranges.

**Real-World Scenario**: Safely return an iterator from a function that takes a temporary span or string_view.

**Snippet**:
```cpp
#include <ranges>
#include <span>

// std::span is a borrowed_range, so this is safe:
auto find_in_span(std::span<const int> data, int val) {
    return std::ranges::find(data, val);  // iterator remains valid
}
```

**Example**: [ranges_borrowed_range.cpp](../../examples/C++20/ranges_borrowed_range.cpp)

### std::ranges::common_range (C++20 Addition)

**Explanation**: Concept for ranges where the iterator and sentinel types are the same. Required for interoperability with legacy algorithms that expect matching begin/end types.

**Real-World Scenario**: Adapt a sentinel-based range to work with a legacy algorithm that requires identical iterator types.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>

template<std::ranges::common_range R>
void legacy_sort(R& r) {
    std::sort(std::ranges::begin(r), std::ranges::end(r));
}
```

**Example**: [ranges_common_range.cpp](../../examples/C++20/ranges_common_range.cpp)

### Range Type Traits: range_value_t, range_reference_t, range_difference_t, range_size_t (C++20 Addition)

**Explanation**: Type aliases that extract associated types from ranges: `range_value_t` gives the element value type, `range_reference_t` the reference type when dereferencing, `range_difference_t` the distance type, and `range_size_t` the unsigned size type.

**Real-World Scenario**: Deduce the accumulator type in a generic reduce function based on the range's value type.

**Snippet**:
```cpp
#include <ranges>
#include <numeric>

template<std::ranges::range R>
auto reduce(R&& r) -> std::ranges::range_value_t<R> {
    std::ranges::range_value_t<R> sum{};
    for (auto&& elem : r) sum += elem;
    return sum;
}
```

**Example**: [ranges_traits.cpp](../../examples/C++20/ranges_traits.cpp)

### Range Access CPOs: std::ranges::begin / end / cbegin / cend / rbegin / rend / crbegin / crend (C++20 Addition)

**Explanation**: Customization point objects (CPOs) that provide uniform access to a range's iterators. Unlike the free functions `std::begin`/`std::end`, CPOs perform concept checks and ADL correctly, and work with sentinel types.

**Real-World Scenario**: Write a generic algorithm library that obtains iterators through CPOs for maximum compatibility across containers, arrays, and custom ranges.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

template<std::ranges::range R>
void print_all(R&& r) {
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it)
        std::cout << *it << ' ';
}
```

**Example**: [ranges_iterators.cpp](../../examples/C++20/ranges_iterators.cpp)

### Range Query CPOs: std::ranges::size / ssize / empty / data / cdata (C++20 Addition)

**Explanation**: CPOs for querying range properties. `size` returns the number of elements, `ssize` returns a signed size, `empty` checks for emptiness, and `data`/`cdata` obtain a pointer to contiguous storage.

**Real-World Scenario**: Implement a buffer upload function that queries size and raw data pointer portably across std::vector, std::array, and std::span.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

template<std::ranges::contiguous_range R>
void upload(R&& r) {
    if (std::ranges::empty(r)) return;
    auto* ptr = std::ranges::data(r);
    auto count = std::ranges::ssize(r);
    // transmit(ptr, count);
}
```

**Example**: [ranges_utils.cpp](../../examples/C++20/ranges_utils.cpp)

## Range Views
### std::views::all / std::ranges::ref_view / std::ranges::owning_view (C++20 Addition)

**Explanation**: `views::all` converts a range into a view: it produces a `ref_view` for lvalue ranges (non-owning reference) or an `owning_view` for rvalue ranges (takes ownership). This is the entry point for creating view pipelines from containers.

**Real-World Scenario**: Start a pipeline from a container without worrying about ownership -- `views::all` automatically selects the right wrapper.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 5};
auto ref = std::views::all(data);           // ref_view: references data
auto own = std::views::all(std::vector{1, 2, 3}); // owning_view: owns the vector

for (int x : ref | std::views::take(3)) { /* 1, 2, 3 */ }
```

**Example**: [ranges_all_view.cpp](../../examples/C++20/ranges_all_view.cpp)

### std::views::filter / std::ranges::filter_view (C++20 Addition)

**Explanation**: Lazily filters elements from a range, yielding only those that satisfy a predicate. Elements are evaluated on demand as the view is iterated, with zero intermediate storage.

**Real-World Scenario**: Filter active users from a user database view without creating a temporary filtered copy.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> scores = {85, 42, 91, 67, 73, 55};
auto passing = scores | std::views::filter([](int s) { return s >= 70; });
// Iterating yields: 85, 91, 73
```

**Example**: [ranges_filter_view.cpp](../../examples/C++20/ranges_filter_view.cpp)

### std::views::transform / std::ranges::transform_view (C++20 Addition)

**Explanation**: Lazily applies a transformation function to each element of a range. The projection is applied on-the-fly during iteration, producing a new view of transformed elements.

**Real-World Scenario**: Convert raw sensor readings (voltages) into calibrated temperature values without allocating a new container.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<double> voltages = {0.5, 1.2, 0.8, 1.5};
auto temperatures = voltages
    | std::views::transform([](double v) { return v * 100.0 - 50.0; });
// Yields: 0.0, 70.0, 30.0, 100.0
```

**Example**: [ranges_transform_view.cpp](../../examples/C++20/ranges_transform_view.cpp)

### std::views::take / std::ranges::take_view (C++20 Addition)

**Explanation**: Creates a view of the first N elements from a range. If the range has fewer than N elements, takes all of them. Works lazily with infinite ranges.

**Real-World Scenario**: Display only the top 10 results from a search query without processing the entire result set.

**Snippet**:
```cpp
#include <ranges>

auto first_ten = std::views::iota(1)  // infinite: 1, 2, 3, ...
    | std::views::take(10);            // first 10: 1..10
```

**Example**: [ranges_take_view.cpp](../../examples/C++20/ranges_take_view.cpp)

### std::views::take_while / std::ranges::take_while_view (C++20 Addition)

**Explanation**: Creates a view that yields elements from the beginning of a range as long as a predicate holds true. Stops at the first element that fails the predicate.

**Real-World Scenario**: Read log entries from a time-sorted log until the timestamp exceeds a cutoff, processing only the relevant window.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {2, 4, 6, 7, 8, 10};
auto evens_prefix = data
    | std::views::take_while([](int n) { return n % 2 == 0; });
// Yields: 2, 4, 6 (stops at 7)
```

**Example**: [ranges_take_while_view.cpp](../../examples/C++20/ranges_take_while_view.cpp)

### std::views::drop / std::ranges::drop_view (C++20 Addition)

**Explanation**: Creates a view that skips the first N elements and yields the remainder. Useful for pagination or skipping headers.

**Real-World Scenario**: Skip the CSV header row and process only data rows from a parsed file.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<std::string> lines = {"Name,Age", "Alice,30", "Bob,25"};
auto data_rows = lines | std::views::drop(1);
// Yields: "Alice,30", "Bob,25"
```

**Example**: [ranges_drop_view.cpp](../../examples/C++20/ranges_drop_view.cpp)

### std::views::drop_while / std::ranges::drop_while_view (C++20 Addition)

**Explanation**: Creates a view that skips leading elements while a predicate is true, then yields the remainder. The predicate is evaluated only for the prefix.

**Real-World Scenario**: Skip leading whitespace lines in a text document before processing content.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {-3, -1, 0, 2, -5, 4};
auto from_non_negative = data
    | std::views::drop_while([](int n) { return n < 0; });
// Yields: 0, 2, -5, 4
```

**Example**: [ranges_drop_while_view.cpp](../../examples/C++20/ranges_drop_while_view.cpp)

### std::views::join / std::ranges::join_view (C++20 Addition)

**Explanation**: Flattens a range of ranges into a single contiguous sequence. Each inner range is iterated in order, producing one flat stream of elements.

**Real-World Scenario**: Flatten a matrix (vector of vectors) into a single sequence for serialization or linear processing.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<std::vector<int>> matrix = {{1, 2}, {3, 4}, {5, 6}};
auto flat = matrix | std::views::join;
// Yields: 1, 2, 3, 4, 5, 6
```

**Example**: [ranges_join_view.cpp](../../examples/C++20/ranges_join_view.cpp)

### std::views::split / std::ranges::split_view (C++20 Addition)

**Explanation**: Splits a range into subranges delimited by a pattern (a single value or a range). Each subrange is a view of the elements between delimiters.

**Real-World Scenario**: Parse a comma-separated configuration string into individual key-value tokens.

**Snippet**:
```cpp
#include <ranges>
#include <string_view>

std::string_view csv = "name,age,city";
for (auto token : csv | std::views::split(',')) {
    std::string_view word(token.begin(), token.end());
    // Yields: "name", "age", "city"
}
```

**Example**: [ranges_split_view.cpp](../../examples/C++20/ranges_split_view.cpp)

### std::views::counted (C++20 Addition)

**Explanation**: Creates a view of exactly N elements starting from an iterator. Unlike `take`, it works with raw iterators rather than ranges, producing a `std::span` or `subrange`.

**Real-World Scenario**: Process a fixed-size chunk from a raw data buffer obtained from a C API.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {10, 20, 30, 40, 50};
auto chunk = std::views::counted(data.begin() + 1, 3);
// Yields: 20, 30, 40
```

**Example**: [ranges_counted_view.cpp](../../examples/C++20/ranges_counted_view.cpp)

### std::views::common / std::ranges::common_view (C++20 Addition)

**Explanation**: Adapts a range with different iterator and sentinel types into one where both are the same type. Required for passing ranges to legacy algorithms that expect matching begin/end types.

**Real-World Scenario**: Use a sentinel-terminated range (like a null-terminated string view) with a legacy C++ algorithm that requires `begin()` and `end()` to return the same type.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

auto nums = std::views::iota(1, 10);
auto common_nums = nums | std::views::common;
std::vector<int> vec(std::ranges::begin(common_nums),
                     std::ranges::end(common_nums));
```

**Example**: [ranges_common_view.cpp](../../examples/C++20/ranges_common_view.cpp)

### std::views::reverse / std::ranges::reverse_view (C++20 Addition)

**Explanation**: Creates a view that iterates over a bidirectional range in reverse order. No data is moved or copied -- the view simply reverses the traversal direction.

**Real-World Scenario**: Display recent log entries in reverse chronological order for a monitoring dashboard.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 5};
for (int x : data | std::views::reverse) {
    // Yields: 5, 4, 3, 2, 1
}
```

**Example**: [ranges_reverse_view.cpp](../../examples/C++20/ranges_reverse_view.cpp)

### std::views::elements / std::ranges::elements_view (C++20 Addition)

**Explanation**: Creates a view that extracts the Nth element from each tuple-like object in a range. Generalizes `keys_view` (element 0) and `values_view` (element 1).

**Real-World Scenario**: Extract just the scores (third column) from a range of (name, id, score) tuples in a grading system.

**Snippet**:
```cpp
#include <ranges>
#include <tuple>
#include <vector>

std::vector<std::tuple<std::string, int, double>> students = {
    {"Alice", 1, 95.5}, {"Bob", 2, 87.3}
};
auto scores = students | std::views::elements<2>;
// Yields: 95.5, 87.3
```

**Example**: [ranges_elements_view.cpp](../../examples/C++20/ranges_elements_view.cpp)

### std::views::keys / std::ranges::keys_view (C++20 Addition)

**Explanation**: Shorthand for `elements_view<0>`, extracting the first element (key) from each pair or tuple in a range. Works with maps, vectors of pairs, and any range of tuple-like elements.

**Real-World Scenario**: Extract all configuration key names from a settings map for display in a preferences UI.

**Snippet**:
```cpp
#include <ranges>
#include <map>

std::map<std::string, int> config = {{"width", 1920}, {"height", 1080}};
for (const auto& key : config | std::views::keys) {
    // Yields: "height", "width"
}
```

**Example**: [ranges_keys_view.cpp](../../examples/C++20/ranges_keys_view.cpp)

### std::views::values / std::ranges::values_view (C++20 Addition)

**Explanation**: Shorthand for `elements_view<1>`, extracting the second element (value) from each pair or tuple in a range. The complement of `keys_view`.

**Real-World Scenario**: Sum all values in a price map to compute a shopping cart total.

**Snippet**:
```cpp
#include <ranges>
#include <map>
#include <numeric>

std::map<std::string, double> prices = {{"apple", 1.50}, {"bread", 2.99}};
auto vals = prices | std::views::values;
// Iterate to sum: 1.50 + 2.99 = 4.49
```

**Example**: [ranges_values_view.cpp](../../examples/C++20/ranges_values_view.cpp)

### std::views::iota / std::ranges::iota_view (C++20 Addition)

**Explanation**: Generates a sequence of incrementing values starting from an initial value, either bounded (with an end value) or unbounded (infinite). Replaces manual index loops with a range-friendly generator.

**Real-World Scenario**: Generate sequential IDs for newly created entities in a game without maintaining a separate counter variable.

**Snippet**:
```cpp
#include <ranges>

// Bounded: generates 0, 1, 2, ..., 99
for (int i : std::views::iota(0, 100)) { /* use i */ }

// Unbounded: infinite sequence starting at 1
auto naturals = std::views::iota(1);
auto first_five = naturals | std::views::take(5);  // 1, 2, 3, 4, 5
```

**Example**: [ranges_iota_view.cpp](../../examples/C++20/ranges_iota_view.cpp)

### std::views::empty / std::ranges::empty_view (C++20 Addition)

**Explanation**: A view that contains zero elements of a given type. Useful as a default/sentinel value in APIs that return views, or as the base case in recursive range algorithms.

**Real-World Scenario**: Return an empty view from a search function when no results are found, avoiding nullable return types.

**Snippet**:
```cpp
#include <ranges>

auto no_results() -> std::ranges::empty_view<int> {
    return {};
}

for (int x : no_results()) { /* never executes */ }
```

**Example**: [ranges_empty_view.cpp](../../examples/C++20/ranges_empty_view.cpp)

### std::views::single / std::ranges::single_view (C++20 Addition)

**Explanation**: A view containing exactly one element. Useful for constructing a one-element range from a value, enabling uniform range-based processing.

**Real-World Scenario**: Wrap a single fallback value as a range to concatenate with other ranges in a configuration system.

**Snippet**:
```cpp
#include <ranges>

auto default_config = std::views::single(std::string("default=true"));
// Can be joined with other ranges in a pipeline
```

**Example**: [ranges_single_view.cpp](../../examples/C++20/ranges_single_view.cpp)

## Range Adaptors
### std::views::filter (pipe syntax) (C++20 Addition)

**Explanation**: Range adaptor that creates a `filter_view` when used with pipe syntax (`|`). The adaptor closure object captures the predicate and can be composed with other adaptors.

**Real-World Scenario**: Build a reusable "active items only" filter that can be plugged into any data pipeline.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

auto is_positive = std::views::filter([](int n) { return n > 0; });

std::vector<int> data = {-2, 5, -1, 8, 0, 3};
for (int x : data | is_positive) { /* 5, 8, 3 */ }
```

**Example**: [ranges_adaptor_filter.cpp](../../examples/C++20/ranges_adaptor_filter.cpp)

### std::views::transform (pipe syntax) (C++20 Addition)

**Explanation**: Range adaptor that creates a `transform_view` via pipe syntax. Captures a projection function and lazily applies it to each element during iteration.

**Real-World Scenario**: Create a reusable "to uppercase" transformation for string processing pipelines.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

auto doubled = std::views::transform([](int n) { return n * 2; });
std::vector<int> data = {1, 2, 3};
for (int x : data | doubled) { /* 2, 4, 6 */ }
```

**Example**: [ranges_adaptor_transform.cpp](../../examples/C++20/ranges_adaptor_transform.cpp)

### std::views::take / take_while / drop / drop_while (pipe syntax) (C++20 Addition)

**Explanation**: Range adaptors for slicing ranges by count or predicate. `take(n)` keeps the first n elements, `take_while(pred)` keeps leading elements satisfying a predicate, and `drop`/`drop_while` are their complements. All compose via pipe syntax.

**Real-World Scenario**: Build a pagination pipeline: drop the first N items (previous pages), then take M items (current page).

**Snippet**:
```cpp
#include <ranges>
#include <vector>

std::vector<int> data = {10, 20, 30, 40, 50, 60, 70, 80};
int page = 2, page_size = 3;
auto current_page = data
    | std::views::drop((page - 1) * page_size)
    | std::views::take(page_size);
// Yields: 40, 50, 60
```

**Example**: [ranges_adaptor_slice.cpp](../../examples/C++20/ranges_adaptor_slice.cpp)

### std::views::join / split / common / reverse (pipe syntax) (C++20 Addition)

**Explanation**: Range adaptors for structural transformations. `join` flattens nested ranges, `split` divides by delimiter, `common` normalizes iterator/sentinel types, and `reverse` reverses traversal order. All work with pipe syntax for composability.

**Real-World Scenario**: Parse a multi-line CSV string by splitting on newlines, then splitting each line on commas, joining results into a flat token stream.

**Snippet**:
```cpp
#include <ranges>
#include <string_view>

std::string_view text = "hello world foo bar";
auto words = text | std::views::split(' ');
for (auto word : words) {
    // Each word is a subrange
}

std::vector<int> data = {1, 2, 3};
auto rev = data | std::views::reverse;  // 3, 2, 1
```

**Example**: [ranges_adaptor_structural.cpp](../../examples/C++20/ranges_adaptor_structural.cpp)

### std::views::elements / keys / values (pipe syntax) (C++20 Addition)

**Explanation**: Range adaptors for extracting components from tuple-like elements. `elements<N>` extracts the Nth element, `keys` is shorthand for `elements<0>`, and `values` is shorthand for `elements<1>`.

**Real-World Scenario**: Extract and process only the values from a map in a pipeline without unpacking pairs manually.

**Snippet**:
```cpp
#include <ranges>
#include <map>

std::map<std::string, int> inventory = {{"sword", 3}, {"shield", 1}, {"potion", 10}};

auto item_counts = inventory | std::views::values;
// Yields: 1, 10, 3 (map-ordered values)

auto item_names = inventory | std::views::keys;
// Yields: "potion", "shield", "sword"
```

**Example**: [ranges_adaptor_elements.cpp](../../examples/C++20/ranges_adaptor_elements.cpp)

### std::views::iota / empty / single (factory adaptors) (C++20 Addition)

**Explanation**: Factory adaptors that generate ranges from scratch rather than adapting existing ones. `iota` produces incrementing sequences, `empty` produces zero-element ranges, and `single` produces one-element ranges. These serve as source nodes in pipelines.

**Real-World Scenario**: Generate test data or placeholder ranges in unit tests without creating actual containers.

**Snippet**:
```cpp
#include <ranges>

// Generate indices
auto indices = std::views::iota(0, 100);

// Compose: even numbers from 0 to 98
auto evens = std::views::iota(0, 100)
    | std::views::filter([](int n) { return n % 2 == 0; });

// Default empty result
auto no_data = std::views::empty<int>;
```

**Example**: [ranges_adaptor_factories.cpp](../../examples/C++20/ranges_adaptor_factories.cpp)

### Composing Range Adaptors with Pipe Syntax (C++20 Addition)

**Explanation**: Range adaptors compose using the `|` operator, creating complex data transformation pipelines from simple building blocks. Each adaptor in the chain is evaluated lazily, with elements flowing through only as they are consumed.

**Real-World Scenario**: Build an ETL (Extract, Transform, Load) pipeline that filters, transforms, and limits data in a single readable expression.

**Snippet**:
```cpp
#include <ranges>
#include <vector>

struct Employee { std::string name; int age; double salary; };
std::vector<Employee> employees = { /* ... */ };

auto senior_salaries = employees
    | std::views::filter([](const Employee& e) { return e.age >= 50; })
    | std::views::transform([](const Employee& e) { return e.salary; })
    | std::views::take(5);
// Top 5 salaries of senior employees, lazily computed
```

**Example**: [ranges_adaptor_compose.cpp](../../examples/C++20/ranges_adaptor_compose.cpp)

## Range Algorithms

### std::ranges::for_each / for_each_n (C++20 Addition)

**Explanation**: Applies a function to each element of a range (or the first N elements). Supports projections, allowing transformation of elements before the function is applied.

**Real-World Scenario**: Apply a discount to each product's price in an e-commerce catalog.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

struct Product { std::string name; double price; };
std::vector<Product> catalog = {{"Widget", 9.99}, {"Gadget", 19.99}};

std::ranges::for_each(catalog, [](double& p) { p *= 0.9; }, &Product::price);
```

**Example**: [ranges_for_each.cpp](../../examples/C++20/ranges_for_each.cpp)

### std::ranges::find / find_if / find_if_not (C++20 Addition)

**Explanation**: Searches for an element matching a value or predicate. Returns an iterator to the first match or the end sentinel. Projections allow searching by a member or transformed value.

**Real-World Scenario**: Find a user by username in a collection of user records.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

struct User { int id; std::string name; };
std::vector<User> users = {{1, "Alice"}, {2, "Bob"}};

auto it = std::ranges::find(users, "Bob", &User::name);
auto admin = std::ranges::find_if(users, [](int id) { return id == 1; }, &User::id);
```

**Example**: [ranges_find.cpp](../../examples/C++20/ranges_find.cpp)

### std::ranges::find_end / find_first_of / adjacent_find (C++20 Addition)

**Explanation**: `find_end` locates the last occurrence of a subsequence. `find_first_of` finds the first element matching any in a set. `adjacent_find` locates adjacent equal (or predicate-matching) elements.

**Real-World Scenario**: Detect duplicate entries in a sorted transaction log by finding adjacent equal timestamps.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 2, 3, 4};
std::vector<int> pattern = {2, 3};

auto [first, last] = std::ranges::find_end(data, pattern);
auto adj = std::ranges::adjacent_find(data);
```

**Example**: [ranges_find_advanced.cpp](../../examples/C++20/ranges_find_advanced.cpp)

### std::ranges::count / count_if (C++20 Addition)

**Explanation**: Counts elements matching a value or predicate. Supports projections for counting based on a member or transformed value.

**Real-World Scenario**: Count the number of failed tests in a test suite by checking each test result's status flag.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

struct TestResult { std::string name; bool passed; };
std::vector<TestResult> results = {{"test1", true}, {"test2", false}, {"test3", true}};

auto failures = std::ranges::count(results, false, &TestResult::passed);
// failures == 1
```

**Example**: [ranges_count.cpp](../../examples/C++20/ranges_count.cpp)

### std::ranges::mismatch / equal (C++20 Addition)

**Explanation**: `mismatch` finds the first position where two ranges differ, returning a pair of iterators. `equal` checks if two ranges are element-wise equal. Both support projections.

**Real-World Scenario**: Compare two firmware versions byte-by-byte to find the first differing offset during a delta update.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> v1 = {1, 2, 3, 4};
std::vector<int> v2 = {1, 2, 5, 4};

auto [it1, it2] = std::ranges::mismatch(v1, v2);
// *it1 == 3, *it2 == 5

bool same = std::ranges::equal(v1, v2);  // false
```

**Example**: [ranges_mismatch_equal.cpp](../../examples/C++20/ranges_mismatch_equal.cpp)

### std::ranges::search / search_n (C++20 Addition)

**Explanation**: `search` finds the first occurrence of a subsequence within a range. `search_n` finds the first run of N consecutive matching elements.

**Real-World Scenario**: Locate a specific byte pattern in a binary protocol stream.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 2, 3};
std::vector<int> pattern = {2, 3};

auto [first, last] = std::ranges::search(data, pattern);
auto run = std::ranges::search_n(data, 1, 2);  // first occurrence of one '2'
```

**Example**: [ranges_search.cpp](../../examples/C++20/ranges_search.cpp)

### std::ranges::copy / copy_if / copy_n / copy_backward (C++20 Addition)

**Explanation**: Copy algorithms for ranges. `copy` copies all elements, `copy_if` copies elements matching a predicate, `copy_n` copies exactly N elements, and `copy_backward` copies in reverse order preserving relative positions.

**Real-World Scenario**: Extract valid records from a dataset into a processing buffer, skipping corrupted entries.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> src = {1, -2, 3, -4, 5};
std::vector<int> dst;

std::ranges::copy_if(src, std::back_inserter(dst),
    [](int n) { return n > 0; });
// dst == {1, 3, 5}
```

**Example**: [ranges_copy.cpp](../../examples/C++20/ranges_copy.cpp)

### std::ranges::move / move_backward (C++20 Addition)

**Explanation**: Moves elements from one range to another, leaving source elements in a valid but unspecified state. `move_backward` moves in reverse order, useful when source and destination overlap.

**Real-World Scenario**: Transfer ownership of unique_ptr elements from a staging buffer to a final container.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>
#include <memory>

std::vector<std::unique_ptr<int>> src;
src.push_back(std::make_unique<int>(42));
std::vector<std::unique_ptr<int>> dst(src.size());

std::ranges::move(src, dst.begin());
// src[0] is now nullptr, dst[0] owns the int
```

**Example**: [ranges_move.cpp](../../examples/C++20/ranges_move.cpp)

### std::ranges::fill / fill_n / generate / generate_n (C++20 Addition)

**Explanation**: `fill`/`fill_n` set elements to a value. `generate`/`generate_n` set elements by calling a generator function repeatedly. All work with ranges and support sentinels.

**Real-World Scenario**: Initialize a game board with default cell values or generate random terrain heights.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>
#include <random>

std::vector<int> grid(100);
std::ranges::fill(grid, 0);

std::mt19937 rng{42};
std::ranges::generate(grid, [&]() { return rng() % 10; });
```

**Example**: [ranges_fill_generate.cpp](../../examples/C++20/ranges_fill_generate.cpp)

### std::ranges::transform (algorithm) (C++20 Addition)

**Explanation**: Range-based transform that applies a unary or binary function to elements, writing results to an output iterator. Supports projections on both input ranges for the binary version.

**Real-World Scenario**: Compute the element-wise sum of two signal arrays in a digital signal processor.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> a = {1, 2, 3}, b = {10, 20, 30};
std::vector<int> result(3);

std::ranges::transform(a, b, result.begin(), std::plus{});
// result == {11, 22, 33}
```

**Example**: [ranges_transform_algo.cpp](../../examples/C++20/ranges_transform_algo.cpp)

### std::ranges::remove / remove_if (C++20 Addition)

**Explanation**: Reorders elements so that those not matching a value/predicate are moved to the front, returning a subrange of "removed" elements at the end. Does not change container size -- use with `erase` for actual removal.

**Real-World Scenario**: Remove expired session tokens from a session list in a web server.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 2, 4};
auto [new_end, old_end] = std::ranges::remove(data, 2);
data.erase(new_end, old_end);
// data == {1, 3, 4}
```

**Example**: [ranges_remove.cpp](../../examples/C++20/ranges_remove.cpp)

### std::ranges::replace / replace_if (C++20 Addition)

**Explanation**: Replaces elements matching a value or predicate with a new value, modifying the range in place. Supports projections.

**Real-World Scenario**: Replace sentinel values (-1) with zero in a dataset before statistical analysis.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, -1, 3, -1, 5};
std::ranges::replace(data, -1, 0);
// data == {1, 0, 3, 0, 5}
```

**Example**: [ranges_replace.cpp](../../examples/C++20/ranges_replace.cpp)

### std::ranges::swap_ranges / reverse / reverse_copy (C++20 Addition)

**Explanation**: `swap_ranges` swaps elements between two ranges pairwise. `reverse` reverses elements in place. `reverse_copy` copies elements in reverse order to an output.

**Real-World Scenario**: Reverse the order of undo history entries when converting to a redo stack.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 5};
std::ranges::reverse(data);
// data == {5, 4, 3, 2, 1}

std::vector<int> reversed(5);
std::ranges::reverse_copy(data, reversed.begin());
```

**Example**: [ranges_reverse_algo.cpp](../../examples/C++20/ranges_reverse_algo.cpp)

### std::ranges::rotate / rotate_copy (C++20 Addition)

**Explanation**: `rotate` shifts elements so that a given middle element becomes the first, wrapping earlier elements to the end. `rotate_copy` performs the rotation into a separate output.

**Real-World Scenario**: Rotate a circular buffer of recent events so the oldest event appears first.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 5};
auto mid = std::ranges::next(data.begin(), 2);
std::ranges::rotate(data, mid);
// data == {3, 4, 5, 1, 2}
```

**Example**: [ranges_rotate.cpp](../../examples/C++20/ranges_rotate.cpp)

### std::ranges::unique / unique_copy (C++20 Addition)

**Explanation**: `unique` removes consecutive duplicates by moving them to the end and returning the new logical endpoint. `unique_copy` copies without consecutive duplicates to an output range.

**Real-World Scenario**: Deduplicate consecutive repeated sensor readings before storing them in a time-series database.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 1, 2, 3, 3, 3, 4};
auto [new_end, old_end] = std::ranges::unique(data);
data.erase(new_end, old_end);
// data == {1, 2, 3, 4}
```

**Example**: [ranges_unique.cpp](../../examples/C++20/ranges_unique.cpp)

### std::ranges::partition / stable_partition (C++20 Addition)

**Explanation**: `partition` reorders elements so those satisfying a predicate come before those that do not. `stable_partition` preserves relative order within each group.

**Real-World Scenario**: Separate pending orders from completed orders in an order management system while preserving chronological order.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {5, 1, 4, 2, 3};
auto pivot = std::ranges::stable_partition(data,
    [](int n) { return n <= 3; });
// data == {1, 2, 3, 5, 4} -- elements <= 3 first, order preserved
```

**Example**: [ranges_partition.cpp](../../examples/C++20/ranges_partition.cpp)

### std::ranges::sort / stable_sort (C++20 Addition)

**Explanation**: `sort` arranges elements in ascending order (or by a custom comparator). `stable_sort` preserves the relative order of equivalent elements. Both support projections for sorting by a member.

**Real-World Scenario**: Sort a leaderboard by score in descending order, with stable sort preserving the signup order for tied scores.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

struct Player { std::string name; int score; };
std::vector<Player> board = {{"Alice", 100}, {"Bob", 95}, {"Carol", 100}};

std::ranges::stable_sort(board, std::greater{}, &Player::score);
// Alice(100), Carol(100), Bob(95) -- Alice before Carol (stable)
```

**Example**: [ranges_sort.cpp](../../examples/C++20/ranges_sort.cpp)

### std::ranges::partial_sort / partial_sort_copy / nth_element (C++20 Addition)

**Explanation**: `partial_sort` sorts only the first N elements into their final positions. `partial_sort_copy` copies the smallest N elements in sorted order. `nth_element` places the Nth element at its sorted position, partitioning around it.

**Real-World Scenario**: Find the top 10 highest-scoring players without fully sorting a million-entry leaderboard.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> scores = {50, 90, 30, 80, 70, 60, 40, 100};

std::ranges::partial_sort(scores, scores.begin() + 3, std::greater{});
// First 3 elements are 100, 90, 80 in order; rest unspecified

std::ranges::nth_element(scores, scores.begin() + 4);
// scores[4] is the 5th smallest; elements before are <= it
```

**Example**: [ranges_partial_sort.cpp](../../examples/C++20/ranges_partial_sort.cpp)

### std::ranges::merge / inplace_merge (C++20 Addition)

**Explanation**: `merge` combines two sorted ranges into a single sorted output range. `inplace_merge` merges two consecutive sorted subranges within a single range.

**Real-World Scenario**: Merge two pre-sorted streams of timestamped events into a unified timeline.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> a = {1, 3, 5}, b = {2, 4, 6};
std::vector<int> merged(6);

std::ranges::merge(a, b, merged.begin());
// merged == {1, 2, 3, 4, 5, 6}
```

**Example**: [ranges_merge.cpp](../../examples/C++20/ranges_merge.cpp)

### std::ranges::includes / set_union / set_intersection / set_difference / set_symmetric_difference (C++20 Addition)

**Explanation**: Set operations on sorted ranges. `includes` checks subset relation. `set_union` produces all unique elements from both. `set_intersection` produces common elements. `set_difference` and `set_symmetric_difference` produce elements in one but not the other, or in exactly one of the two.

**Real-World Scenario**: Compute the intersection of two users' friend lists to show mutual friends.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> friends_a = {1, 3, 5, 7, 9};
std::vector<int> friends_b = {2, 3, 5, 8, 9};
std::vector<int> mutual;

std::ranges::set_intersection(friends_a, friends_b, std::back_inserter(mutual));
// mutual == {3, 5, 9}
```

**Example**: [ranges_set_operations.cpp](../../examples/C++20/ranges_set_operations.cpp)

### std::ranges::push_heap / pop_heap / make_heap / sort_heap (C++20 Addition)

**Explanation**: Heap operations on ranges. `make_heap` arranges elements into a max-heap. `push_heap`/`pop_heap` maintain the heap property after insertion/removal. `sort_heap` sorts a heap into ascending order.

**Real-World Scenario**: Implement a priority queue for a task scheduler using heap operations on a flat vector.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> tasks = {3, 1, 4, 1, 5};
std::ranges::make_heap(tasks);

tasks.push_back(9);
std::ranges::push_heap(tasks);

std::ranges::pop_heap(tasks);
int highest = tasks.back();  // 9
tasks.pop_back();
```

**Example**: [ranges_heap.cpp](../../examples/C++20/ranges_heap.cpp)

### std::ranges::min / max / minmax (C++20 Addition)

**Explanation**: Return the minimum, maximum, or both from a range or initializer list. Support projections and custom comparators.

**Real-World Scenario**: Find the cheapest and most expensive items in a product catalog in a single pass.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

struct Product { std::string name; double price; };
std::vector<Product> catalog = {{"A", 9.99}, {"B", 4.99}, {"C", 14.99}};

auto [cheapest, priciest] = std::ranges::minmax(catalog, {}, &Product::price);
// cheapest.name == "B", priciest.name == "C"
```

**Example**: [ranges_min_max.cpp](../../examples/C++20/ranges_min_max.cpp)

### std::ranges::min_element / max_element / minmax_element (C++20 Addition)

**Explanation**: Return iterators to the minimum, maximum, or both extreme elements in a range. Unlike `min`/`max`, these return iterators for in-place modification or position tracking.

**Real-World Scenario**: Find the position of the hottest temperature reading in a sensor array to highlight it on a dashboard.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<double> temps = {22.5, 31.2, 18.7, 29.8};
auto hottest = std::ranges::max_element(temps);
auto index = std::distance(temps.begin(), hottest);
// index == 1 (31.2 degrees)
```

**Example**: [ranges_min_max_element.cpp](../../examples/C++20/ranges_min_max_element.cpp)

### std::ranges::lexicographical_compare (C++20 Addition)

**Explanation**: Compares two ranges lexicographically (dictionary order). Returns true if the first range is less than the second. Supports projections and custom comparators.

**Real-World Scenario**: Sort filenames in a file manager using natural lexicographic ordering.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> a = {1, 2, 3};
std::vector<int> b = {1, 2, 4};

bool a_less = std::ranges::lexicographical_compare(a, b);  // true
```

**Example**: [ranges_lexicographical.cpp](../../examples/C++20/ranges_lexicographical.cpp)

### std::ranges::next_permutation / prev_permutation (C++20 Addition)

**Explanation**: Rearranges elements into the next or previous lexicographic permutation. Returns a struct indicating whether the permutation wrapped around.

**Real-World Scenario**: Generate all possible orderings of a small set of test inputs for exhaustive testing.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3};
do {
    // Process permutation: {1,2,3}, {1,3,2}, {2,1,3}, ...
} while (std::ranges::next_permutation(data).found);
```

**Example**: [ranges_permutation.cpp](../../examples/C++20/ranges_permutation.cpp)

### std::ranges::all_of / any_of / none_of (C++20 Addition)

**Explanation**: Boolean query algorithms. `all_of` returns true if every element satisfies a predicate. `any_of` returns true if at least one does. `none_of` returns true if none do.

**Real-World Scenario**: Validate that all configuration values in a settings map are within acceptable bounds.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> ages = {25, 30, 17, 42};
bool all_adult = std::ranges::all_of(ages, [](int a) { return a >= 18; });  // false
bool any_minor = std::ranges::any_of(ages, [](int a) { return a < 18; });   // true
```

**Example**: [ranges_all_any_none.cpp](../../examples/C++20/ranges_all_any_none.cpp)

### std::ranges::is_sorted / is_sorted_until (C++20 Addition)

**Explanation**: `is_sorted` checks if an entire range is sorted. `is_sorted_until` finds the first element that breaks the sorted order.

**Real-World Scenario**: Validate that a database index is in sorted order before performing binary search operations.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 3, 5, 4, 6};
bool sorted = std::ranges::is_sorted(data);            // false
auto it = std::ranges::is_sorted_until(data);           // points to 4
```

**Example**: [ranges_is_sorted.cpp](../../examples/C++20/ranges_is_sorted.cpp)

### std::ranges::is_permutation (C++20 Addition)

**Explanation**: Checks if one range is a permutation (rearrangement) of another. Both ranges must contain the same elements with the same multiplicities.

**Real-World Scenario**: Verify that a shuffled deck of cards contains exactly the same cards as a standard deck.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> original = {1, 2, 3, 4};
std::vector<int> shuffled = {3, 1, 4, 2};

bool valid = std::ranges::is_permutation(original, shuffled);  // true
```

**Example**: [ranges_is_permutation.cpp](../../examples/C++20/ranges_is_permutation.cpp)

### std::ranges::is_heap / is_heap_until (C++20 Addition)

**Explanation**: `is_heap` checks if a range satisfies the max-heap property. `is_heap_until` returns an iterator to the first element that violates the heap property.

**Real-World Scenario**: Assert heap invariants in a priority queue implementation during debug builds.

**Snippet**:
```cpp
#include <ranges>
#include <algorithm>
#include <vector>

std::vector<int> data = {9, 5, 7, 1, 3};
bool is_valid_heap = std::ranges::is_heap(data);  // true

data.push_back(10);  // breaks heap
auto it = std::ranges::is_heap_until(data);  // points to 10
```

**Example**: [ranges_is_heap.cpp](../../examples/C++20/ranges_is_heap.cpp)

## Algorithms
### std::shift_left / std::shift_right (C++20 Addition)

**Explanation**: Shifts elements in a range left or right by a given number of positions. Elements shifted out are lost; the vacated positions are left in a moved-from state.

**Real-World Scenario**: Rotate elements in a circular buffer or shift a timeline window in a data visualization.

**Snippet**:
```cpp
#include <algorithm>
#include <vector>

std::vector<int> data = {1, 2, 3, 4, 5};
std::shift_left(data.begin(), data.end(), 2);
// data == {3, 4, 5, ?, ?} -- first two positions shifted out
```

**Example**: [shift.cpp](../../examples/C++20/shift.cpp)

### std::ranges::starts_with / std::ranges::ends_with (C++20 Addition)

**Explanation**: Checks if a range starts or ends with a given subrange. Works with any range types, not just strings.

**Real-World Scenario**: Verify that a command packet begins with the correct header sequence in a protocol parser.

**Snippet**:
```cpp
#include <algorithm>
#include <vector>

std::vector<int> data = {0xDE, 0xAD, 0xBE, 0xEF, 0x01};
std::vector<int> header = {0xDE, 0xAD};

bool valid = std::ranges::starts_with(data, header);  // true
```

**Example**: [starts_ends_with.cpp](../../examples/C++20/starts_ends_with.cpp)

### std::ranges::contains (C++20 Addition)

**Explanation**: Checks if a range contains a specific value or subrange. A convenient shorthand for `find() != end()`.

**Real-World Scenario**: Check whether a user ID exists in a permissions whitelist.

**Snippet**:
```cpp
#include <algorithm>
#include <vector>

std::vector<int> allowed_ids = {101, 202, 303, 404};
bool permitted = std::ranges::contains(allowed_ids, 202);  // true
```

**Example**: [contains.cpp](../../examples/C++20/contains.cpp)

### std::erase / std::erase_if (C++20 Addition)

**Explanation**: Uniform container erasure functions that combine the erase-remove idiom into a single call. Work with vector, deque, list, string, set, map, and other standard containers.

**Real-World Scenario**: Remove all expired cache entries from a cache container in one clean statement.

**Snippet**:
```cpp
#include <vector>
#include <string>

std::vector<int> data = {1, -2, 3, -4, 5};
std::erase_if(data, [](int n) { return n < 0; });
// data == {1, 3, 5}

std::string text = "Hello, World!";
std::erase(text, ',');
// text == "Hello World!"
```

**Example**: [erase.cpp](../../examples/C++20/erase.cpp)

## Utilities
### std::bit_cast (C++20 Addition)

**Explanation**: Reinterprets the bits of one type as another type in a type-safe, constexpr-friendly way. Replaces dangerous `reinterpret_cast` and `memcpy` patterns for type punning with a well-defined operation.

**Real-World Scenario**: Convert a float to its IEEE 754 bit representation for serialization or hashing.

**Snippet**:
```cpp
#include <bit>
#include <cstdint>

constexpr auto bits = std::bit_cast<std::uint32_t>(3.14f);
constexpr auto back = std::bit_cast<float>(bits);
// back == 3.14f -- round-trip preserves the value
```

**Example**: [bit_cast.cpp](../../examples/C++20/bit_cast.cpp)

### std::format / std::format_to / std::format_to_n / std::formatted_size / std::vformat / std::make_format_args (C++20 Addition)

**Explanation**: Type-safe string formatting library inspired by Python's format strings. `format` returns a formatted string. `format_to` writes to an output iterator. `format_to_n` writes at most N characters. `formatted_size` computes the output size without writing. `vformat` uses type-erased arguments. `make_format_args` creates argument stores for runtime format strings.

**Real-World Scenario**: Build a logging system that formats structured messages with type safety, avoiding the pitfalls of printf-style variadic functions.

**Snippet**:
```cpp
#include <format>
#include <string>

auto msg = std::format("User {} scored {:.1f}%", "Alice", 95.678);
// msg == "User Alice scored 95.7%"

std::string buffer;
std::format_to(std::back_inserter(buffer), "{:>10}", 42);
// buffer == "        42"

auto size = std::formatted_size("Hello, {}!", "World");
// size == 13
```

**Example**: [format.cpp](../../examples/C++20/format.cpp)

### std::syncbuf / std::osyncstream (C++20 Addition)

**Explanation**: Synchronized output stream wrappers that buffer output and flush atomically, preventing interleaved output from multiple threads. `syncbuf` is the buffer; `osyncstream` is the stream wrapper.

**Real-World Scenario**: Log diagnostic messages from multiple worker threads to stdout without garbled interleaving.

**Snippet**:
```cpp
#include <syncstream>
#include <iostream>
#include <thread>

void worker(int id) {
    std::osyncstream(std::cout) << "Worker " << id << " started\n";
    // Entire line is flushed atomically
}
```

**Example**: [syncstream.cpp](../../examples/C++20/syncstream.cpp)

### std::bind_front (C++20 Addition)

**Explanation**: Binds the first N arguments of a callable, producing a new callable that accepts the remaining arguments. Simpler and more efficient than `std::bind` for the common case of partial application from the left.

**Real-World Scenario**: Pre-bind a logger's severity level to create convenience functions like `log_error` and `log_info`.

**Snippet**:
```cpp
#include <functional>
#include <iostream>

void log(const std::string& level, const std::string& msg) {
    std::cout << "[" << level << "] " << msg << "\n";
}

auto log_error = std::bind_front(log, "ERROR");
auto log_info  = std::bind_front(log, "INFO");
log_error("Connection failed");  // [ERROR] Connection failed
```

**Example**: [bind_front.cpp](../../examples/C++20/bind_front.cpp)

### std::identity (C++20 Addition)

**Explanation**: A transparent function object that returns its argument unchanged. Serves as the default projection for range algorithms, enabling clean default parameter values.

**Real-World Scenario**: Use as a default no-op projection when writing a generic algorithm that optionally projects elements.

**Snippet**:
```cpp
#include <functional>
#include <algorithm>
#include <ranges>
#include <vector>

template<std::ranges::range R, typename Proj = std::identity>
void print_sorted(R&& r, Proj proj = {}) {
    std::vector<std::ranges::range_value_t<R>> copy(std::ranges::begin(r), std::ranges::end(r));
    std::ranges::sort(copy, {}, proj);
}
```

**Example**: [identity.cpp](../../examples/C++20/identity.cpp)

### std::unwrap_reference / std::unwrap_ref_decay (C++20 Addition)

**Explanation**: Type traits that unwrap `std::reference_wrapper<T>` to `T&`, and leave other types unchanged. `unwrap_ref_decay` first applies `std::decay_t` before unwrapping. Useful in generic code that stores or forwards arguments which might be reference-wrapped.

**Real-World Scenario**: Implement a `make_tuple`-like function that correctly handles `std::ref` arguments.

**Snippet**:
```cpp
#include <functional>
#include <type_traits>

template<typename T>
void store(T&& val) {
    using Stored = std::unwrap_ref_decay_t<T>;
    // If T is reference_wrapper<int>, Stored is int&
    // If T is int, Stored is int
}

int x = 42;
store(std::ref(x));  // Stored deduces to int&
store(42);           // Stored deduces to int
```

**Example**: [unwrap_reference.cpp](../../examples/C++20/unwrap_reference.cpp)

### std::midpoint (C++20 Addition)

**Explanation**: Computes the midpoint of two values (integers, floating-point, or pointers) without overflow. For integers, rounds toward the first argument when the result is not exact.

**Real-World Scenario**: Implement binary search with correct midpoint computation that avoids the classic integer overflow bug.

**Snippet**:
```cpp
#include <numeric>

auto mid = std::midpoint(0, 100);             // 50
auto fmid = std::midpoint(1.0, 3.0);          // 2.0

// Safe even for large values:
auto safe = std::midpoint(INT_MAX - 1, INT_MAX);  // no overflow
```

**Example**: [midpoint.cpp](../../examples/C++20/midpoint.cpp)

### std::lerp (C++20 Addition)

**Explanation**: Performs linear interpolation between two floating-point values: `lerp(a, b, t) = a + t*(b-a)`. Handles edge cases (t=0, t=1, NaN) correctly per IEEE 754.

**Real-World Scenario**: Smoothly interpolate between two positions in a game animation system.

**Snippet**:
```cpp
#include <cmath>

double start = 0.0, end = 100.0;
double quarter = std::lerp(start, end, 0.25);  // 25.0
double half    = std::lerp(start, end, 0.5);   // 50.0
double full    = std::lerp(start, end, 1.0);   // 100.0
```

**Example**: [lerp.cpp](../../examples/C++20/lerp.cpp)

### std::to_address (C++20 Addition)

**Explanation**: Obtains the raw pointer from a pointer-like type (fancy pointer, smart pointer, or raw pointer) without dereferencing it. Works even for pointers to incomplete types or types that overload `operator*`.

**Real-World Scenario**: Pass the underlying address from a custom allocator's fancy pointer to a C API that requires a raw pointer.

**Snippet**:
```cpp
#include <memory>
#include <vector>

std::vector<int> data = {1, 2, 3};
auto ptr = std::to_address(data.begin());  // int* to first element

auto sp = std::make_shared<int>(42);
int* raw = std::to_address(sp);  // raw pointer, no ref-count change
```

**Example**: [to_address.cpp](../../examples/C++20/to_address.cpp)

### std::assume_aligned (C++20 Addition)

**Explanation**: Informs the compiler that a pointer is aligned to at least N bytes, enabling SIMD and other alignment-dependent optimizations. Returns the same pointer with the alignment guarantee baked in.

**Real-World Scenario**: Optimize a SIMD-accelerated image processing kernel by asserting 32-byte alignment on pixel data.

**Snippet**:
```cpp
#include <memory>

void process_pixels(float* data, std::size_t n) {
    float* aligned = std::assume_aligned<32>(data);
    for (std::size_t i = 0; i < n; ++i)
        aligned[i] *= 2.0f;  // compiler can emit AVX instructions
}
```

**Example**: [assume_aligned.cpp](../../examples/C++20/assume_aligned.cpp)

### std::make_shared_for_overwrite / std::make_unique_for_overwrite (C++20 Addition)

**Explanation**: Create smart pointers with default-initialized (not value-initialized) storage. For trivial types, this leaves memory uninitialized, avoiding the cost of zeroing when you intend to overwrite the contents immediately.

**Real-World Scenario**: Allocate a large buffer for file I/O where the contents will be completely overwritten by a read operation, saving the cost of zero-initialization.

**Snippet**:
```cpp
#include <memory>

// Value-initialized (zeroed): expensive for large arrays
auto zeroed = std::make_unique<char[]>(1'000'000);

// Default-initialized (uninitialized): faster
auto buffer = std::make_unique_for_overwrite<char[]>(1'000'000);
// Fill buffer from file:
// file.read(buffer.get(), 1'000'000);

auto shared_buf = std::make_shared_for_overwrite<double[]>(1024);
```

**Example**: [make_for_overwrite.cpp](../../examples/C++20/make_for_overwrite.cpp)

## Mathematical Constants
### std::numbers::pi / std::numbers::pi_v (C++20 Addition)

**Explanation**: The mathematical constant pi (ratio of circumference to diameter) as a compile-time variable template. `pi` is `double`; `pi_v<T>` provides the value in any floating-point type.

**Real-World Scenario**: Compute the area of a circle in a CAD application with the correct precision for the target type.

**Snippet**:
```cpp
#include <numbers>

double area = std::numbers::pi * radius * radius;
float area_f = std::numbers::pi_v<float> * r * r;
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::e / std::numbers::e_v (C++20 Addition)

**Explanation**: Euler's number (base of the natural logarithm), approximately 2.71828. Available as both `double` and a variable template for other floating-point types.

**Real-World Scenario**: Model exponential growth or decay in a population simulation or financial compound interest calculator.

**Snippet**:
```cpp
#include <numbers>
#include <cmath>

double growth = std::pow(std::numbers::e, rate * time);
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::sqrt2 / std::numbers::sqrt3 (C++20 Addition)

**Explanation**: The square roots of 2 and 3 as compile-time constants. `sqrt2` is approximately 1.41421; `sqrt3` is approximately 1.73205. Avoids runtime computation of commonly used irrational constants.

**Real-World Scenario**: Compute diagonal distances in a grid-based game (sqrt2 for diagonal, sqrt3 for hexagonal grids).

**Snippet**:
```cpp
#include <numbers>

double diagonal = side_length * std::numbers::sqrt2;
double hex_height = side_length * std::numbers::sqrt3;
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::ln2 / std::numbers::ln10 (C++20 Addition)

**Explanation**: Natural logarithms of 2 and 10. `ln2` is approximately 0.69315; `ln10` is approximately 2.30259. Frequently used in information theory, signal processing, and logarithmic conversions.

**Real-World Scenario**: Convert between natural and base-2 logarithms in an entropy calculation for a compression algorithm.

**Snippet**:
```cpp
#include <numbers>
#include <cmath>

double entropy_bits = entropy_nats / std::numbers::ln2;
double decibels = 10.0 * std::log(power_ratio) / std::numbers::ln10;
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::log2e / std::numbers::log10e (C++20 Addition)

**Explanation**: Base-2 and base-10 logarithms of Euler's number e. `log2e` is approximately 1.4427; `log10e` is approximately 0.4343. The reciprocals of `ln2` and `ln10`.

**Real-World Scenario**: Convert natural logarithm results to base-2 for bit-width calculations in a codec.

**Snippet**:
```cpp
#include <numbers>
#include <cmath>

double log2_value = std::log(x) * std::numbers::log2e;
double log10_value = std::log(x) * std::numbers::log10e;
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::phi (C++20 Addition)

**Explanation**: The golden ratio, approximately 1.61803. Defined as `(1 + sqrt(5)) / 2`. Appears in nature, art, and algorithms (e.g., Fibonacci heaps, golden-section search).

**Real-World Scenario**: Implement a golden-section search optimization algorithm for single-variable function minimization.

**Snippet**:
```cpp
#include <numbers>

double golden_ratio = std::numbers::phi;
// Golden section: divide interval in ratio phi:1
double split = lower + (upper - lower) / std::numbers::phi;
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::inv_pi / std::numbers::inv_sqrtpi (C++20 Addition)

**Explanation**: The reciprocals `1/pi` and `1/sqrt(pi)`. Pre-computed inverses avoid division at runtime and are commonly used in probability distributions and physics normalization.

**Real-World Scenario**: Normalize a Gaussian distribution's probability density function efficiently.

**Snippet**:
```cpp
#include <numbers>
#include <cmath>

// Gaussian PDF normalization: 1 / sqrt(2*pi*sigma^2)
double norm = std::numbers::inv_sqrtpi * (1.0 / std::sqrt(2.0 * sigma * sigma));
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

### std::numbers::egamma (C++20 Addition)

**Explanation**: The Euler-Mascheroni constant, approximately 0.57722. Appears in number theory, the analysis of the harmonic series, and the gamma function.

**Real-World Scenario**: Estimate the Nth harmonic number in a performance analysis tool that models cache behavior.

**Snippet**:
```cpp
#include <numbers>
#include <cmath>

// Approximate Nth harmonic number: H(n) ~ ln(n) + gamma
double harmonic_approx(int n) {
    return std::log(n) + std::numbers::egamma;
}
```

**Example**: [math_constants.cpp](../../examples/C++20/math_constants.cpp)

## Chrono Extensions
### Calendar Types: day, month, year, weekday, weekday_indexed, weekday_last, month_day, month_day_last, month_weekday, month_weekday_last, year_month, year_month_day, year_month_day_last, year_month_weekday, year_month_weekday_last (C++20 Addition)

**Explanation**: A comprehensive calendar type system that models dates, months, years, weekdays, and their combinations with full type safety. These types support arithmetic, comparison, and validation (e.g., checking if a date is valid).

**Real-World Scenario**: Schedule recurring events on specific weekdays (e.g., "the second Tuesday of every month") in a calendar application.

**Snippet**:
```cpp
#include <chrono>
using namespace std::chrono;

auto today = year_month_day{year{2026}, month{3}, day{22}};
bool valid = today.ok();  // true

// Second Tuesday of March 2026
auto meeting = year{2026}/March/Tuesday[2];
auto meeting_date = year_month_day{sys_days{meeting}};
```

**Example**: [chrono_calendar.cpp](../../examples/C++20/chrono_calendar.cpp)

### Time Zone Support: local_time, zoned_time, time_zone, sys_time, utc_clock, tai_clock, gps_clock, file_clock, local_days, local_seconds (C++20 Addition)

**Explanation**: Full time zone support with IANA time zone database integration. `zoned_time` pairs a time point with a time zone for automatic conversions. Multiple clock types (`utc_clock`, `tai_clock`, `gps_clock`) model different time scales.

**Real-World Scenario**: Convert meeting times across global offices' time zones in a scheduling application, correctly handling DST transitions.

**Snippet**:
```cpp
#include <chrono>
using namespace std::chrono;

auto now = system_clock::now();
auto tokyo = zoned_time{"Asia/Tokyo", now};
auto nyc   = zoned_time{"America/New_York", now};

// Display local times
auto tokyo_local = tokyo.get_local_time();
auto nyc_local   = nyc.get_local_time();
```

**Example**: [chrono_timezones.cpp](../../examples/C++20/chrono_timezones.cpp)

## Bit Operations
### std::bit_ceil (C++20 Addition)

**Explanation**: Returns the smallest power of two that is greater than or equal to the given value. Useful for aligning buffer sizes to powers of two.

**Real-World Scenario**: Round up a memory allocation size to the next power of two for an allocator that uses power-of-two buckets.

**Snippet**:
```cpp
#include <bit>

auto size = std::bit_ceil(100u);   // 128
auto exact = std::bit_ceil(64u);   // 64 (already a power of two)
```

**Example**: [bit_ceil.cpp](../../examples/C++20/bit_ceil.cpp)

### std::bit_floor (C++20 Addition)

**Explanation**: Returns the largest power of two that is less than or equal to the given value. Returns zero for input zero.

**Real-World Scenario**: Determine the largest texture mipmap level that fits within a given resolution.

**Snippet**:
```cpp
#include <bit>

auto size = std::bit_floor(100u);  // 64
auto exact = std::bit_floor(64u);  // 64
auto zero = std::bit_floor(0u);    // 0
```

**Example**: [bit_floor.cpp](../../examples/C++20/bit_floor.cpp)

### std::bit_width (C++20 Addition)

**Explanation**: Returns the number of bits needed to represent a value (i.e., `1 + floor(log2(x))` for x > 0, or 0 for x == 0). Equivalent to the position of the highest set bit.

**Real-World Scenario**: Determine the minimum number of bits needed to encode a symbol in a variable-length encoding scheme.

**Snippet**:
```cpp
#include <bit>

auto w1 = std::bit_width(0u);    // 0
auto w2 = std::bit_width(1u);    // 1
auto w3 = std::bit_width(255u);  // 8
auto w4 = std::bit_width(256u);  // 9
```

**Example**: [bit_width.cpp](../../examples/C++20/bit_width.cpp)

### std::countl_zero / std::countl_one (C++20 Addition)

**Explanation**: `countl_zero` counts the number of consecutive zero bits starting from the most significant bit. `countl_one` counts consecutive one bits from the MSB. Useful for priority encoding and normalization.

**Real-World Scenario**: Implement a fast priority encoder that finds the highest-priority set bit in an interrupt status register.

**Snippet**:
```cpp
#include <bit>
#include <cstdint>

uint32_t flags = 0b00001000'00000000'00000000'00000000;
auto leading_zeros = std::countl_zero(flags);   // 4
auto leading_ones = std::countl_one(~flags);     // 4
```

**Example**: [countl.cpp](../../examples/C++20/countl.cpp)

### std::countr_zero / std::countr_one (C++20 Addition)

**Explanation**: `countr_zero` counts consecutive zero bits from the least significant bit. `countr_one` counts consecutive one bits from the LSB. The classic "find first set bit" operation.

**Real-World Scenario**: Find the lowest available slot in a bitmap allocator by counting trailing ones.

**Snippet**:
```cpp
#include <bit>
#include <cstdint>

uint32_t bitmap = 0b00000000'00000000'00000000'00010100;
auto trailing_zeros = std::countr_zero(bitmap);  // 2
auto trailing_ones = std::countr_one(bitmap >> 2); // 1
```

**Example**: [countr.cpp](../../examples/C++20/countr.cpp)

### std::has_single_bit (C++20 Addition)

**Explanation**: Returns true if the value is a power of two (exactly one bit set). Equivalent to `popcount(x) == 1` but more readable and potentially more efficient.

**Real-World Scenario**: Validate that a user-specified buffer size is a power of two, as required by a ring buffer implementation.

**Snippet**:
```cpp
#include <bit>

bool is_pot = std::has_single_bit(64u);   // true
bool not_pot = std::has_single_bit(100u); // false
bool zero = std::has_single_bit(0u);      // false
```

**Example**: [has_single_bit.cpp](../../examples/C++20/has_single_bit.cpp)

### std::popcount (C++20 Addition)

**Explanation**: Returns the number of set bits (1-bits) in an unsigned integer, also known as the population count or Hamming weight. Many CPUs have a dedicated instruction for this.

**Real-World Scenario**: Count the number of active permissions in a bitmask-based access control system.

**Snippet**:
```cpp
#include <bit>
#include <cstdint>

uint32_t permissions = 0b10110101;
auto count = std::popcount(permissions);  // 5 bits set
```

**Example**: [popcount.cpp](../../examples/C++20/popcount.cpp)

### std::rotl / std::rotr (C++20 Addition)

**Explanation**: Bitwise left and right rotation. Unlike shifts, bits that move past one end wrap around to the other. Essential for hash functions, cryptographic algorithms, and CRC computations.

**Real-World Scenario**: Implement a hash combining function that uses bit rotation to distribute entropy.

**Snippet**:
```cpp
#include <bit>
#include <cstdint>

uint32_t val = 0x12345678;
auto left  = std::rotl(val, 8);   // 0x34567812
auto right = std::rotr(val, 8);   // 0x78123456
```

**Example**: [rotl_rotr.cpp](../../examples/C++20/rotl_rotr.cpp)

## Threading
### std::jthread (C++20 Addition)

**Explanation**: A joining thread that automatically joins in its destructor and supports cooperative cancellation via stop tokens. Eliminates the common bug of forgetting to join or detach a `std::thread`.

**Real-World Scenario**: Run a background monitoring task that automatically stops and cleans up when the parent scope exits.

**Snippet**:
```cpp
#include <thread>
#include <iostream>

void monitor(std::stop_token st) {
    while (!st.stop_requested()) {
        // check system health
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

{
    std::jthread worker(monitor);
    // ... do work ...
}  // worker automatically stop-requested and joined here
```

**Example**: [jthread.cpp](../../examples/C++20/jthread.cpp)

### std::stop_token / std::stop_source (C++20 Addition)

**Explanation**: Cooperative cancellation mechanism. A `stop_source` can request a stop; associated `stop_token` objects can check whether a stop has been requested. `stop_callback` registers functions to run when stop is requested.

**Real-World Scenario**: Cancel a long-running database query from a UI thread when the user clicks "Cancel".

**Snippet**:
```cpp
#include <stop_token>
#include <thread>

void search(std::stop_token token, const std::string& query) {
    for (auto& page : database) {
        if (token.stop_requested()) return;  // cancelled
        // process page
    }
}

std::stop_source source;
std::jthread worker(search, source.get_token(), "SELECT *");
// Later: source.request_stop();
```

**Example**: [stop_token.cpp](../../examples/C++20/stop_token.cpp)

### std::latch (C++20 Addition)

**Explanation**: A single-use synchronization primitive with a counter that threads can decrement. Threads waiting on the latch block until the counter reaches zero. Cannot be reset once triggered.

**Real-World Scenario**: Wait for all worker threads to complete initialization before starting the main processing loop.

**Snippet**:
```cpp
#include <latch>
#include <thread>
#include <vector>

std::latch ready(3);

auto worker = [&](int id) {
    // initialize...
    ready.count_down();  // signal ready
};

std::vector<std::jthread> threads;
for (int i = 0; i < 3; ++i) threads.emplace_back(worker, i);
ready.wait();  // blocks until all 3 workers are ready
```

**Example**: [latch.cpp](../../examples/C++20/latch.cpp)

### std::barrier (C++20 Addition)

**Explanation**: A reusable synchronization primitive where a fixed number of threads repeatedly synchronize at a barrier point. Each phase can optionally invoke a completion function.

**Real-World Scenario**: Synchronize simulation steps in a parallel physics engine where all threads must finish one time step before any begins the next.

**Snippet**:
```cpp
#include <barrier>
#include <thread>
#include <vector>

auto on_phase_complete = []() noexcept { /* swap buffers */ };
std::barrier sync(4, on_phase_complete);

auto simulate = [&](int id) {
    for (int step = 0; step < 100; ++step) {
        compute_physics(id);
        sync.arrive_and_wait();  // wait for all 4 threads
    }
};
```

**Example**: [barrier.cpp](../../examples/C++20/barrier.cpp)

### std::counting_semaphore / std::binary_semaphore (C++20 Addition)

**Explanation**: Lightweight synchronization primitive that maintains a counter. `acquire()` blocks until the counter is positive, then decrements it. `release()` increments the counter. `binary_semaphore` is a specialization with max count of 1.

**Real-World Scenario**: Limit the number of concurrent database connections in a connection pool.

**Snippet**:
```cpp
#include <semaphore>
#include <thread>

std::counting_semaphore<10> pool(5);  // max 10, initial 5

void use_connection() {
    pool.acquire();  // blocks if no connections available
    // use database connection...
    pool.release();  // return connection to pool
}
```

**Example**: [semaphore.cpp](../../examples/C++20/semaphore.cpp)

### std::atomic_ref (C++20 Addition)

**Explanation**: Provides atomic operations on a non-atomic object through a reference. The referenced object must meet alignment requirements. Allows atomic access to data not originally declared as `std::atomic`.

**Real-World Scenario**: Perform atomic updates on elements of a plain array shared between threads, without paying the storage overhead of `std::atomic` per element.

**Snippet**:
```cpp
#include <atomic>
#include <thread>

int counters[4] = {};

void increment(int index) {
    std::atomic_ref<int> ref(counters[index]);
    ref.fetch_add(1, std::memory_order_relaxed);
}
```

**Example**: [atomic_ref.cpp](../../examples/C++20/atomic_ref.cpp)

### std::atomic_flag Enhancements (C++20 Evolution)

**Explanation**: `std::atomic_flag` gains `test()` (read without modify), `wait()` (block until value changes), `notify_one()`, and `notify_all()`. These additions make `atomic_flag` a complete synchronization primitive.

**Real-World Scenario**: Implement a lightweight spinlock with wait/notify for efficient thread signaling without busy-waiting.

**Snippet**:
```cpp
#include <atomic>
#include <thread>

std::atomic_flag ready{};

// Producer
void signal() {
    ready.test_and_set();
    ready.notify_one();
}

// Consumer
void wait_for_signal() {
    ready.wait(false);  // blocks until flag becomes true
}
```

**Example**: [atomic_flag.cpp](../../examples/C++20/atomic_flag.cpp)

### std::atomic::wait / std::atomic::notify_one / std::atomic::notify_all (C++20 Addition)

**Explanation**: Extends all `std::atomic` types with efficient blocking wait and notification. `wait(old)` blocks until the atomic value differs from `old`. `notify_one` wakes one waiting thread; `notify_all` wakes all. Replaces busy-wait polling with OS-level efficient waiting.

**Real-World Scenario**: Implement a producer-consumer queue where the consumer sleeps efficiently until new data is available, avoiding CPU-wasting spin loops.

**Snippet**:
```cpp
#include <atomic>
#include <thread>

std::atomic<int> mailbox{0};

void producer() {
    mailbox.store(42);
    mailbox.notify_one();  // wake consumer
}

void consumer() {
    mailbox.wait(0);       // sleep until mailbox != 0
    int value = mailbox.load();  // 42
}
```

**Example**: [atomic_wait_notify.cpp](../../examples/C++20/atomic_wait_notify.cpp)
