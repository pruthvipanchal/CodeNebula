# C++11 STL Concepts

This document covers new or evolved C++11 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++11/). Only additions or evolutions from C++98/C++03 are included.

## Containers
### std::array (C++11 Addition)
**Explanation**: Fixed-size array with STL-like interface, safer than C-style arrays.  
**Real-World Scenario**: Store fixed-size game board coordinates in a puzzle game.  
**Snippet**:  
```cpp
#include <array> std::array<int, 5> arr = {1, 2, 3, 4, 5};
```
**Example**: [array.cpp](../../examples/C++11/array.cpp)

### std::forward_list (C++11 Addition)
**Explanation**: Singly-linked list for efficient insertions at the front.  
**Real-World Scenario**: Implement a lightweight event log with frequent additions.  
**Snippet**:  
```cpp
#include <forward_list> std::forward_list<int> flist = {1, 2, 3};
```
**Example**: [forward_list.cpp](../../examples/C++11/forward_list.cpp)

### std::unordered_set (C++11 Addition)
**Explanation**: Hash-based container for unique elements, offering O(1) lookup.  
**Real-World Scenario**: Store unique user IDs in a fast-access membership system.  
**Snippet**:  
```cpp
#include <unordered_set> std::unordered_set<int> uset = {1, 2, 3};
```
**Example**: [unordered_set.cpp](../../examples/C++11/unordered_set.cpp)

### std::unordered_multiset (C++11 Addition)
**Explanation**: Hash-based container allowing duplicate elements.  
**Real-World Scenario**: Track multiple occurrences of event IDs in a log.  
**Snippet**:  
```cpp
#include <unordered_set> std::unordered_multiset<int> umset = {1, 1, 2};
```
**Example**: [unordered_multiset.cpp](../../examples/C++11/unordered_multiset.cpp)

### std::unordered_map (C++11 Addition)
**Explanation**: Hash-based key-value pairs with unique keys, O(1) lookup.  
**Real-World Scenario**: Store user settings by ID in a configuration system.  
**Snippet**:  
```cpp
#include <unordered_map> std::unordered_map<int, std::string> umap = {{1, "A"}};
```
**Example**: [unordered_map.cpp](../../examples/C++11/unordered_map.cpp)

### std::unordered_multimap (C++11 Addition)
**Explanation**: Hash-based key-value pairs allowing duplicate keys.  
**Real-World Scenario**: Store multiple phone numbers per contact in an address book.  
**Snippet**:  
```cpp
#include <unordered_map> std::unordered_multimap<int, std::string> ummap = {{1, "A"}};
```
**Example**: [unordered_multimap.cpp](../../examples/C++11/unordered_multimap.cpp)

### std::vector (C++11 Evolution)
**Explanation**: Dynamic array, now supports move semantics and `emplace_back`.  
**Real-World Scenario**: Efficiently add complex objects to a chat message list.  
**Snippet**:  
```cpp
#include <vector> std::vector<int> vec; vec.emplace_back(1);
```
**Example**: [vector.cpp](../../examples/C++11/vector.cpp)

### std::list (C++11 Evolution)
**Explanation**: Doubly-linked list, supports move semantics and `emplace`.  
**Real-World Scenario**: Efficiently insert objects into a playlist.  
**Snippet**:  
```cpp
#include <list> std::list<int> lst; lst.emplace_front(1);
```
**Example**: [list.cpp](../../examples/C++11/list.cpp)

### std::deque (C++11 Evolution)
**Explanation**: Double-ended queue, supports move semantics and `emplace`.  
**Real-World Scenario**: Add tasks to a scheduler queue efficiently.  
**Snippet**:  
```cpp
#include <deque> std::deque<int> dq; dq.emplace_back(1);
```
**Example**: [deque.cpp](../../examples/C++11/deque.cpp)

### std::set (C++11 Evolution)
**Explanation**: Sorted unique elements, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert unique IDs into a membership system efficiently.  
**Snippet**:  
```cpp
#include <set> std::set<int> s; s.emplace(1);
```
**Example**: [set.cpp](../../examples/C++11/set.cpp)

### std::map (C++11 Evolution)
**Explanation**: Sorted key-value pairs, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert student grades by ID efficiently.  
**Snippet**:  
```cpp
#include <map> std::map<int, std::string> m; m.emplace(1, "A");
```
**Example**: [map.cpp](../../examples/C++11/map.cpp)

### std::multiset (C++11 Evolution)
**Explanation**: Sorted collection with duplicates, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert multiple event timestamps in a log.  
**Snippet**:  
```cpp
#include <multiset> std::multiset<int> ms; ms.emplace(1);
```
**Example**: [multiset.cpp](../../examples/C++11/multiset.cpp)

### std::multimap (C++11 Evolution)
**Explanation**: Sorted key-value pairs with duplicates, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert multiple phone numbers per contact.  
**Snippet**:  
```cpp
#include <map> std::multimap<int, std::string> mm; mm.emplace(1, "A");
```
**Example**: [multimap.cpp](../../examples/C++11/multimap.cpp)

### std::stack (C++11 Evolution)
**Explanation**: LIFO container adaptor, supports move semantics and `emplace`.  
**Real-World Scenario**: Add undo operations to a text editor efficiently.  
**Snippet**:  
```cpp
#include <stack> std::stack<int> stk; stk.emplace(1);
```
**Example**: [stack.cpp](../../examples/C++11/stack.cpp)

### std::queue (C++11 Evolution)
**Explanation**: FIFO container adaptor, supports move semantics and `emplace`.  
**Real-World Scenario**: Add print jobs to a printer queue efficiently.  
**Snippet**:  
```cpp
#include <queue> std::queue<int> q; q.emplace(1);
```
**Example**: [queue.cpp](../../examples/C++11/queue.cpp)

### std::priority_queue (C++11 Evolution)
**Explanation**: Queue with largest element at top, supports move semantics and `emplace`.  
**Real-World Scenario**: Add tasks to a priority-based scheduler.  
**Snippet**:  
```cpp
#include <queue> std::priority_queue<int> pq; pq.emplace(1);
```
**Example**: [priority_queue.cpp](../../examples/C++11/priority_queue.cpp)

## Container Improvements
### Emplace Operations (C++11 Addition)
**Explanation**: All standard containers gained `emplace`, `emplace_back`, and `emplace_front` methods that construct elements in-place using perfect forwarding, avoiding unnecessary copies or moves.
**Real-World Scenario**: Insert complex objects like database records directly into a container without creating temporaries.
**Snippet**:
```cpp
#include <vector>
#include <map>
struct Record { std::string name; int id; Record(std::string n, int i) : name(std::move(n)), id(i) {} };
std::vector<Record> records;
records.emplace_back("Alice", 1); // constructed in-place
std::map<int, std::string> m;
m.emplace(1, "value"); // constructed in-place
```
**Example**: [emplace_operations.cpp](../../examples/C++11/emplace_operations.cpp)

### initializer_list Support (C++11 Addition)
**Explanation**: All standard containers now accept `std::initializer_list` for construction and assignment, enabling clean brace-enclosed initialization syntax.
**Real-World Scenario**: Initialize a collection of allowed HTTP status codes directly at declaration time.
**Snippet**:
```cpp
#include <vector>
#include <set>
std::vector<int> codes = {200, 301, 404, 500};
std::set<std::string> methods = {"GET", "POST", "PUT", "DELETE"};
```
**Example**: [initializer_list_support.cpp](../../examples/C++11/initializer_list_support.cpp)

## Iterators
### std::begin/end (C++11 Addition)
**Explanation**: Free functions that return iterators to the beginning and end of a container or C-style array, enabling generic code that works uniformly with both.
**Real-World Scenario**: Write a generic print function that works with both `std::vector` and raw arrays.
**Snippet**:
```cpp
#include <iterator>
int arr[] = {1, 2, 3};
auto first = std::begin(arr);
auto last = std::end(arr);
```
**Example**: [begin_end.cpp](../../examples/C++11/begin_end.cpp)

### std::cbegin/cend (C++11 Addition)
**Explanation**: Free functions returning const iterators, guaranteeing read-only access to container elements.
**Real-World Scenario**: Iterate over a configuration map in a read-only context to prevent accidental modifications.
**Snippet**:
```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {1, 2, 3};
auto it = std::cbegin(v); // const_iterator
```
**Example**: [cbegin_cend.cpp](../../examples/C++11/cbegin_cend.cpp)

### std::rbegin/rend (C++11 Addition)
**Explanation**: Free functions returning reverse iterators, enabling reverse traversal of containers and arrays uniformly.
**Real-World Scenario**: Process log entries in reverse chronological order.
**Snippet**:
```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {1, 2, 3};
for (auto it = std::rbegin(v); it != std::rend(v); ++it) {}
```
**Example**: [rbegin_rend.cpp](../../examples/C++11/rbegin_rend.cpp)

### std::crbegin/crend (C++11 Addition)
**Explanation**: Free functions returning const reverse iterators, combining read-only access with reverse traversal.
**Real-World Scenario**: Display the last N transactions from a read-only account history in reverse order.
**Snippet**:
```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {1, 2, 3};
auto it = std::crbegin(v); // const_reverse_iterator
```
**Example**: [crbegin_crend.cpp](../../examples/C++11/crbegin_crend.cpp)

### std::move_iterator (C++11 Addition)
**Explanation**: An iterator adaptor that dereferences to an rvalue reference, enabling move semantics when copying ranges of elements.
**Real-World Scenario**: Transfer ownership of a collection of unique resources from one container to another.
**Snippet**:
```cpp
#include <iterator>
#include <vector>
#include <string>
std::vector<std::string> src = {"hello", "world"};
std::vector<std::string> dst(std::make_move_iterator(src.begin()),
                             std::make_move_iterator(src.end()));
```
**Example**: [move_iterator.cpp](../../examples/C++11/move_iterator.cpp)

## Algorithms
### std::all_of (C++11 Addition)
**Explanation**: Checks if all elements in a range satisfy a predicate.  
**Real-World Scenario**: Verify all scores in a game are positive.  
**Snippet**:  
```cpp
#include <algorithm> std::all_of(vec.begin(), vec.end(), isPositive);
```
**Example**: [all_of.cpp](../../examples/C++11/all_of.cpp)

### std::any_of (C++11 Addition)
**Explanation**: Checks if any element in a range satisfies a predicate.  
**Real-World Scenario**: Check if any user input is invalid in a form.  
**Snippet**:  
```cpp
#include <algorithm> std::any_of(vec.begin(), vec.end(), isInvalid);
```
**Example**: [any_of.cpp](../../examples/C++11/any_of.cpp)

### std::none_of (C++11 Addition)
**Explanation**: Checks if no elements in a range satisfy a predicate.  
**Real-World Scenario**: Ensure no tasks in a queue are overdue.  
**Snippet**:  
```cpp
#include <algorithm> std::none_of(vec.begin(), vec.end(), isOverdue);
```
**Example**: [none_of.cpp](../../examples/C++11/none_of.cpp)

### std::find_if_not (C++11 Addition)
**Explanation**: Finds the first element not satisfying a predicate.  
**Real-World Scenario**: Find the first non-completed task in a to-do list.  
**Snippet**:  
```cpp
#include <algorithm> std::find_if_not(vec.begin(), vec.end(), isCompleted);
```
**Example**: [find_if_not.cpp](../../examples/C++11/find_if_not.cpp)

### std::copy_if (C++11 Addition)
**Explanation**: Copies elements satisfying a predicate to a destination.  
**Real-World Scenario**: Copy valid user inputs to a filtered list.  
**Snippet**:  
```cpp
#include <algorithm> std::copy_if(vec.begin(), vec.end(), dest.begin(), isValid);
```
**Example**: [copy_if.cpp](../../examples/C++11/copy_if.cpp)

### std::copy_n (C++11 Addition)
**Explanation**: Copies n elements from a range to a destination.  
**Real-World Scenario**: Copy the first n log entries to a report.  
**Snippet**:  
```cpp
#include <algorithm> std::copy_n(vec.begin(), 5, dest.begin());
```
**Example**: [copy_n.cpp](../../examples/C++11/copy_n.cpp)

### std::move (Algorithm, C++11 Evolution)
**Explanation**: Moves elements to a destination, leveraging move semantics.  
**Real-World Scenario**: Transfer large objects between buffers in a network app.  
**Snippet**:  
```cpp
#include <algorithm> std::move(vec.begin(), vec.end(), dest.begin());
```
**Example**: [move_algorithm.cpp](../../examples/C++11/move_algorithm.cpp)

### std::move_backward (C++11 Evolution)
**Explanation**: Moves elements in reverse order, leveraging move semantics.  
**Real-World Scenario**: Reverse-move data in a memory manager.  
**Snippet**:  
```cpp
#include <algorithm> std::move_backward(vec.begin(), vec.end(), dest.end());
```
**Example**: [move_backward.cpp](../../examples/C++11/move_backward.cpp)

### std::is_sorted (C++11 Addition)
**Explanation**: Checks if a range is sorted.  
**Real-World Scenario**: Verify a leaderboard is sorted by score.  
**Snippet**:  
```cpp
#include <algorithm> std::is_sorted(vec.begin(), vec.end());
```
**Example**: [is_sorted.cpp](../../examples/C++11/is_sorted.cpp)

### std::is_sorted_until (C++11 Addition)
**Explanation**: Finds the first unsorted element in a range.  
**Real-World Scenario**: Identify where sorting fails in a dataset.  
**Snippet**:  
```cpp
#include <algorithm> std::is_sorted_until(vec.begin(), vec.end());
```
**Example**: [is_sorted_until.cpp](../../examples/C++11/is_sorted_until.cpp)

### std::partition_copy (C++11 Addition)
**Explanation**: Copies elements to two destinations based on a predicate.  
**Real-World Scenario**: Separate completed and pending tasks in a scheduler.  
**Snippet**:  
```cpp
#include <algorithm> std::partition_copy(vec.begin(), vec.end(), dest1.begin(), dest2.begin(), isCompleted);
```
**Example**: [partition_copy.cpp](../../examples/C++11/partition_copy.cpp)

### std::partition_point (C++11 Addition)
**Explanation**: Finds the partition point in a partitioned range.  
**Real-World Scenario**: Locate the boundary between completed and pending tasks.  
**Snippet**:  
```cpp
#include <algorithm> std::partition_point(vec.begin(), vec.end(), isCompleted);
```
**Example**: [partition_point.cpp](../../examples/C++11/partition_point.cpp)

### std::shuffle (C++11 Addition)
**Explanation**: Randomly shuffles elements in a range using a random engine.  
**Real-World Scenario**: Shuffle a deck of cards in a game.  
**Snippet**:  
```cpp
#include <algorithm> #include <random> std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
```
**Example**: [shuffle.cpp](../../examples/C++11/shuffle.cpp)

### std::minmax (C++11 Addition)
**Explanation**: Returns both minimum and maximum of two values.  
**Real-World Scenario**: Find the cheapest and most expensive products in a store.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax(a, b);
```
**Example**: [minmax.cpp](../../examples/C++11/minmax.cpp)

### std::minmax_element (C++11 Addition)
**Explanation**: Finds both minimum and maximum elements in a range.  
**Real-World Scenario**: Identify lowest and highest scores in a leaderboard.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax_element(vec.begin(), vec.end());
```
**Example**: [minmax_element.cpp](../../examples/C++11/minmax_element.cpp)

### std::is_permutation (C++11 Addition)
**Explanation**: Checks if one range is a permutation of another, meaning both contain the same elements regardless of order.
**Real-World Scenario**: Verify that a shuffled deck of cards still contains exactly the same cards as the original deck.
**Snippet**:
```cpp
#include <algorithm>
std::vector<int> a = {1, 2, 3};
std::vector<int> b = {3, 1, 2};
bool same = std::is_permutation(a.begin(), a.end(), b.begin()); // true
```
**Example**: [is_permutation.cpp](../../examples/C++11/is_permutation.cpp)

### std::is_heap (C++11 Addition)
**Explanation**: Checks if a range forms a valid max-heap, useful for verifying heap invariants before performing heap operations.
**Real-World Scenario**: Validate that a priority queue's underlying storage maintains the heap property after manual modifications.
**Snippet**:
```cpp
#include <algorithm>
std::vector<int> v = {9, 5, 4, 1, 3};
bool valid = std::is_heap(v.begin(), v.end()); // true
```
**Example**: [is_heap.cpp](../../examples/C++11/is_heap.cpp)

### std::is_heap_until (C++11 Addition)
**Explanation**: Returns an iterator to the first element that violates the heap property, helping identify where a heap becomes invalid.
**Real-World Scenario**: Debug a custom priority scheduler by finding where the heap invariant breaks down.
**Snippet**:
```cpp
#include <algorithm>
std::vector<int> v = {9, 5, 4, 1, 8};
auto it = std::is_heap_until(v.begin(), v.end()); // points to 8
```
**Example**: [is_heap_until.cpp](../../examples/C++11/is_heap_until.cpp)

### std::iota (C++11 Addition)
**Explanation**: Fills a range with sequentially increasing values starting from a given value, provided by the `<numeric>` header.
**Real-World Scenario**: Generate sequential ticket numbers or indices for a seating chart.
**Snippet**:
```cpp
#include <numeric>
std::vector<int> v(10);
std::iota(v.begin(), v.end(), 1); // {1, 2, 3, ..., 10}
```
**Example**: [iota.cpp](../../examples/C++11/iota.cpp)

## Function Objects
### std::function (C++11 Addition)
**Explanation**: A general-purpose polymorphic function wrapper that can store, copy, and invoke any callable target including functions, lambdas, bind expressions, and function objects.
**Real-World Scenario**: Implement a callback registry in an event system where handlers can be any callable type.
**Snippet**:
```cpp
#include <functional>
std::function<int(int, int)> op = [](int a, int b) { return a + b; };
int result = op(3, 4); // 7
```
**Example**: [function.cpp](../../examples/C++11/function.cpp)

### std::bind (C++11 Addition)
**Explanation**: Creates a new callable by binding arguments to a function, enabling partial application and argument reordering using placeholders.
**Real-World Scenario**: Create a pre-configured logging function with a fixed severity level for a specific module.
**Snippet**:
```cpp
#include <functional>
void log(const std::string& level, const std::string& msg) {}
auto warn = std::bind(log, "WARN", std::placeholders::_1);
warn("Disk space low"); // calls log("WARN", "Disk space low")
```
**Example**: [bind.cpp](../../examples/C++11/bind.cpp)

### std::ref/cref (C++11 Addition)
**Explanation**: Creates `std::reference_wrapper` objects that allow passing references through interfaces that normally copy their arguments, such as `std::bind` and `std::thread`.
**Real-World Scenario**: Pass a large data structure by reference to a thread function without copying it.
**Snippet**:
```cpp
#include <functional>
void process(int& value) { value += 10; }
int x = 5;
auto bound = std::bind(process, std::ref(x));
bound(); // x is now 15
```
**Example**: [ref_cref.cpp](../../examples/C++11/ref_cref.cpp)

### std::mem_fn (C++11 Addition)
**Explanation**: Creates a callable wrapper from a pointer to a member function, simplifying its use with standard algorithms and function objects.
**Real-World Scenario**: Call a member function on each element in a collection of objects using `std::for_each`.
**Snippet**:
```cpp
#include <functional>
#include <vector>
#include <algorithm>
struct Widget { void activate() {} };
std::vector<Widget> widgets(5);
std::for_each(widgets.begin(), widgets.end(), std::mem_fn(&Widget::activate));
```
**Example**: [mem_fn.cpp](../../examples/C++11/mem_fn.cpp)

## Type Traits
### std::is_integral (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is an integral type (bool, char, int, long, etc.).
**Real-World Scenario**: Constrain a template function to only accept integer types in a math library.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_integral<int>::value, "int is integral");
static_assert(!std::is_integral<double>::value, "double is not integral");
```
**Example**: [is_integral.cpp](../../examples/C++11/is_integral.cpp)

### std::is_floating_point (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is a floating-point type (float, double, long double).
**Real-World Scenario**: Select different precision algorithms based on whether a template parameter is a floating-point type.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_floating_point<double>::value, "double is floating point");
```
**Example**: [is_floating_point.cpp](../../examples/C++11/is_floating_point.cpp)

### std::is_pointer (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is a pointer type.
**Real-World Scenario**: Write a generic serializer that handles pointer types differently from value types.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_pointer<int*>::value, "int* is a pointer");
static_assert(!std::is_pointer<int>::value, "int is not a pointer");
```
**Example**: [is_pointer.cpp](../../examples/C++11/is_pointer.cpp)

### std::is_array (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is a C-style array type.
**Real-World Scenario**: Specialize a print function for arrays versus single values in a debugging utility.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_array<int[5]>::value, "int[5] is an array");
static_assert(!std::is_array<std::array<int,5>>::value, "std::array is not a C array");
```
**Example**: [is_array.cpp](../../examples/C++11/is_array.cpp)

### std::is_class (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is a class or struct (but not a union).
**Real-World Scenario**: Enable SFINAE-based overloading for class types that may have member functions.
**Snippet**:
```cpp
#include <type_traits>
struct Foo {};
static_assert(std::is_class<Foo>::value, "Foo is a class");
```
**Example**: [is_class.cpp](../../examples/C++11/is_class.cpp)

### std::is_enum (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is an enumeration type.
**Real-World Scenario**: Write a generic to-string converter that handles enum types specially using `underlying_type`.
**Snippet**:
```cpp
#include <type_traits>
enum Color { Red, Green, Blue };
static_assert(std::is_enum<Color>::value, "Color is an enum");
```
**Example**: [is_enum.cpp](../../examples/C++11/is_enum.cpp)

### std::is_void (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is `void`.
**Real-World Scenario**: Specialize a return-value wrapper to handle void-returning functions differently.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_void<void>::value, "void is void");
```
**Example**: [is_void.cpp](../../examples/C++11/is_void.cpp)

### std::is_same (C++11 Addition)
**Explanation**: Compile-time check that determines whether two types are exactly the same.
**Real-World Scenario**: Assert that a template deduction produces the expected type in a serialization framework.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_same<int, int>::value, "same types");
static_assert(!std::is_same<int, long>::value, "different types");
```
**Example**: [is_same.cpp](../../examples/C++11/is_same.cpp)

### std::is_base_of (C++11 Addition)
**Explanation**: Compile-time check that determines whether one class is a base of another, enabling compile-time inheritance validation.
**Real-World Scenario**: Ensure that a plugin class derives from the required base interface before registration.
**Snippet**:
```cpp
#include <type_traits>
class Base {};
class Derived : public Base {};
static_assert(std::is_base_of<Base, Derived>::value, "Derived inherits from Base");
```
**Example**: [is_base_of.cpp](../../examples/C++11/is_base_of.cpp)

### std::is_convertible (C++11 Addition)
**Explanation**: Compile-time check that determines whether one type is implicitly convertible to another.
**Real-World Scenario**: Validate that a callback parameter type is compatible with the expected signature at compile time.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_convertible<int, double>::value, "int converts to double");
```
**Example**: [is_convertible.cpp](../../examples/C++11/is_convertible.cpp)

### std::is_trivially_copyable (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type can be safely copied with `memcpy`, important for low-level optimizations and serialization.
**Real-World Scenario**: Use `memcpy` for bulk data transfer only when the type is trivially copyable.
**Snippet**:
```cpp
#include <type_traits>
struct Pod { int x; float y; };
static_assert(std::is_trivially_copyable<Pod>::value, "Pod is trivially copyable");
```
**Example**: [is_trivially_copyable.cpp](../../examples/C++11/is_trivially_copyable.cpp)

### std::is_trivially_constructible (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type can be trivially constructed, meaning no user-defined constructor logic runs.
**Real-World Scenario**: Optimize container allocation by skipping initialization for trivially constructible types.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_trivially_constructible<int>::value, "int is trivially constructible");
```
**Example**: [is_trivially_constructible.cpp](../../examples/C++11/is_trivially_constructible.cpp)

### std::is_trivially_destructible (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type has a trivial destructor, meaning no cleanup logic runs on destruction.
**Real-World Scenario**: Skip destructor calls when deallocating arrays of trivially destructible types for performance.
**Snippet**:
```cpp
#include <type_traits>
static_assert(std::is_trivially_destructible<int>::value, "int is trivially destructible");
```
**Example**: [is_trivially_destructible.cpp](../../examples/C++11/is_trivially_destructible.cpp)

### std::is_standard_layout (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type has a standard memory layout compatible with C structs.
**Real-World Scenario**: Ensure a struct can be safely passed to a C library via FFI.
**Snippet**:
```cpp
#include <type_traits>
struct CCompatible { int x; float y; };
static_assert(std::is_standard_layout<CCompatible>::value, "C-compatible layout");
```
**Example**: [is_standard_layout.cpp](../../examples/C++11/is_standard_layout.cpp)

### std::is_pod (C++11 Addition)
**Explanation**: Compile-time check that determines whether a type is a Plain Old Data type (both trivial and standard layout), safe for `memcpy` and C interop.
**Real-World Scenario**: Validate that a network packet struct is POD before performing raw memory serialization.
**Snippet**:
```cpp
#include <type_traits>
struct Packet { int id; char data[256]; };
static_assert(std::is_pod<Packet>::value, "Packet is POD");
```
**Example**: [is_pod.cpp](../../examples/C++11/is_pod.cpp)

### std::integral_constant, true_type, false_type (C++11 Addition)
**Explanation**: `integral_constant` wraps a compile-time constant value as a type. `true_type` and `false_type` are convenient aliases for `integral_constant<bool, true>` and `integral_constant<bool, false>`, forming the foundation for all type traits.
**Real-World Scenario**: Build custom type traits by inheriting from `true_type` or `false_type`.
**Snippet**:
```cpp
#include <type_traits>
template<typename T>
struct is_my_type : std::false_type {};
template<>
struct is_my_type<int> : std::true_type {};
static_assert(is_my_type<int>::value, "int is my type");
```
**Example**: [integral_constant.cpp](../../examples/C++11/integral_constant.cpp)

### std::enable_if (C++11 Addition)
**Explanation**: A SFINAE utility that conditionally enables or disables template overloads based on a compile-time boolean condition, providing fine-grained control over overload resolution.
**Real-World Scenario**: Create a function overload that only accepts integral types, with a separate overload for floating-point types.
**Snippet**:
```cpp
#include <type_traits>
template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
T double_value(T x) { return x * 2; }
```
**Example**: [enable_if.cpp](../../examples/C++11/enable_if.cpp)

### std::conditional (C++11 Addition)
**Explanation**: A compile-time type selector that chooses between two types based on a boolean condition, similar to the ternary operator but for types.
**Real-World Scenario**: Select between a thread-safe and non-thread-safe allocator at compile time based on a configuration flag.
**Snippet**:
```cpp
#include <type_traits>
using type = std::conditional<sizeof(int) >= 4, int, long>::type;
```
**Example**: [conditional.cpp](../../examples/C++11/conditional.cpp)

### std::common_type (C++11 Addition)
**Explanation**: Deduces the common type to which all given types can be implicitly converted, essential for writing generic arithmetic functions.
**Real-World Scenario**: Determine the result type of adding different numeric types in a generic math library.
**Snippet**:
```cpp
#include <type_traits>
using T = std::common_type<int, double>::type; // double
```
**Example**: [common_type.cpp](../../examples/C++11/common_type.cpp)

### std::result_of (C++11 Addition)
**Explanation**: Deduces the return type of invoking a callable with given argument types, enabling generic wrapper functions.
**Real-World Scenario**: Determine the return type of a callback in a generic task scheduler.
**Snippet**:
```cpp
#include <type_traits>
int func(double);
using R = std::result_of<decltype(func)&(double)>::type; // int
```
**Example**: [result_of.cpp](../../examples/C++11/result_of.cpp)

### std::underlying_type (C++11 Addition)
**Explanation**: Retrieves the underlying integer type of an enumeration, useful for serialization and bitwise operations on enum class values.
**Real-World Scenario**: Serialize an enum class value to its integer representation for network transmission.
**Snippet**:
```cpp
#include <type_traits>
enum class Color : uint8_t { Red, Green, Blue };
using U = std::underlying_type<Color>::type; // uint8_t
```
**Example**: [underlying_type.cpp](../../examples/C++11/underlying_type.cpp)

### std::remove_reference (C++11 Addition)
**Explanation**: Removes reference qualifiers from a type, producing the underlying value type. Fundamental to implementing perfect forwarding.
**Real-World Scenario**: Strip references in a template to obtain the raw type for storage in a container.
**Snippet**:
```cpp
#include <type_traits>
using T = std::remove_reference<int&>::type; // int
using U = std::remove_reference<int&&>::type; // int
```
**Example**: [remove_reference.cpp](../../examples/C++11/remove_reference.cpp)

### std::remove_cv/remove_const/remove_volatile (C++11 Addition)
**Explanation**: Removes `const` and/or `volatile` qualifiers from a type, enabling uniform type comparisons and transformations regardless of cv-qualification.
**Real-World Scenario**: Normalize types in a template so that `const int` and `int` map to the same handler.
**Snippet**:
```cpp
#include <type_traits>
using T = std::remove_const<const int>::type; // int
using U = std::remove_cv<const volatile int>::type; // int
```
**Example**: [remove_cv.cpp](../../examples/C++11/remove_cv.cpp)

### std::add_lvalue_reference/add_rvalue_reference (C++11 Addition)
**Explanation**: Adds lvalue or rvalue reference qualifiers to a type, useful for building reference-manipulating metafunctions.
**Real-World Scenario**: Construct the correct reference type in a forwarding utility based on template parameters.
**Snippet**:
```cpp
#include <type_traits>
using LRef = std::add_lvalue_reference<int>::type; // int&
using RRef = std::add_rvalue_reference<int>::type; // int&&
```
**Example**: [add_reference.cpp](../../examples/C++11/add_reference.cpp)

### std::make_signed/make_unsigned (C++11 Addition)
**Explanation**: Converts an integral type to its signed or unsigned counterpart while preserving size, enabling safe conversions in generic code.
**Real-World Scenario**: Convert a container size type to a signed type for safe subtraction in index calculations.
**Snippet**:
```cpp
#include <type_traits>
using S = std::make_signed<unsigned int>::type; // int
using U = std::make_unsigned<int>::type; // unsigned int
```
**Example**: [make_signed_unsigned.cpp](../../examples/C++11/make_signed_unsigned.cpp)

### std::decay (C++11 Addition)
**Explanation**: Applies the type transformations that occur when passing by value: removes references, removes cv-qualifiers, and converts arrays and functions to pointers.
**Real-World Scenario**: Determine the stored type when capturing a variable by value in a generic container.
**Snippet**:
```cpp
#include <type_traits>
using T = std::decay<const int&>::type; // int
using U = std::decay<int[5]>::type; // int*
```
**Example**: [decay.cpp](../../examples/C++11/decay.cpp)

### std::aligned_storage (C++11 Addition)
**Explanation**: Provides a type suitable for use as uninitialized storage for an object of a given size and alignment, enabling manual object lifetime management.
**Real-World Scenario**: Implement an optional-like type or a small buffer optimization without dynamic allocation.
**Snippet**:
```cpp
#include <type_traits>
std::aligned_storage<sizeof(int), alignof(int)>::type storage;
int* p = new (&storage) int(42); // placement new
```
**Example**: [aligned_storage.cpp](../../examples/C++11/aligned_storage.cpp)

### std::aligned_union (C++11 Addition)
**Explanation**: Provides storage suitable for any of a list of types, with size and alignment sufficient for the largest type. Useful for implementing variant types.
**Real-World Scenario**: Implement a tagged union that can hold any of several types efficiently.
**Snippet**:
```cpp
#include <type_traits>
using Storage = std::aligned_union<0, int, double, std::string>::type;
Storage s;
new (&s) double(3.14);
```
**Example**: [aligned_union.cpp](../../examples/C++11/aligned_union.cpp)

## Hashing
### std::hash (C++11 Addition)
**Explanation**: A function object that computes hash values for fundamental and standard library types, used as the default hasher for unordered containers. Can be specialized for user-defined types.
**Real-World Scenario**: Use a custom hash specialization to store user-defined key types in an `unordered_map`.
**Snippet**:
```cpp
#include <functional>
std::hash<std::string> hasher;
size_t h = hasher("hello"); // hash value for "hello"
```
**Example**: [hash.cpp](../../examples/C++11/hash.cpp)

## Error Handling
### std::system_error (C++11 Addition)
**Explanation**: An exception class that carries an error code, providing a standard way to report system-level errors with associated error categories and messages.
**Real-World Scenario**: Throw a descriptive exception when a file system operation fails with an OS-level error code.
**Snippet**:
```cpp
#include <system_error>
throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
```
**Example**: [system_error.cpp](../../examples/C++11/system_error.cpp)

### std::error_code (C++11 Addition)
**Explanation**: A lightweight, copyable object representing a platform-specific error value and its associated category, designed for efficient error handling without exceptions.
**Real-World Scenario**: Return error codes from a file I/O function that callers can inspect without try/catch overhead.
**Snippet**:
```cpp
#include <system_error>
std::error_code ec = std::make_error_code(std::errc::permission_denied);
if (ec) { /* handle error */ }
```
**Example**: [error_code.cpp](../../examples/C++11/error_code.cpp)

### std::error_category (C++11 Addition)
**Explanation**: An abstract base class that defines a category of errors, providing error message generation and equivalence comparisons. The standard provides `generic_category()` and `system_category()`.
**Real-World Scenario**: Define a custom error category for a network library to provide meaningful error descriptions.
**Snippet**:
```cpp
#include <system_error>
const std::error_category& cat = std::generic_category();
std::string msg = cat.message(static_cast<int>(std::errc::invalid_argument));
```
**Example**: [error_category.cpp](../../examples/C++11/error_category.cpp)

### std::error_condition (C++11 Addition)
**Explanation**: A portable error abstraction representing an error condition independent of the originating platform, enabling cross-platform error comparison.
**Real-World Scenario**: Compare platform-specific file errors against portable error conditions in a cross-platform application.
**Snippet**:
```cpp
#include <system_error>
std::error_condition cond = std::errc::no_such_file_or_directory;
std::error_code ec = std::make_error_code(std::errc::no_such_file_or_directory);
bool match = (ec == cond); // true
```
**Example**: [error_condition.cpp](../../examples/C++11/error_condition.cpp)

## Utilities
### std::tuple (C++11 Addition)
**Explanation**: Stores a fixed-size collection of heterogeneous values.  
**Real-World Scenario**: Return multiple values (e.g., position and velocity) from a physics function.  
**Snippet**:  
```cpp
#include <tuple> std::tuple<int, std::string> t = {1, "value"};
```
**Example**: [tuple.cpp](../../examples/C++11/tuple.cpp)

### std::tie (C++11 Addition)
**Explanation**: Unpacks a tuple into individual variables.  
**Real-World Scenario**: Extract position and velocity from a physics calculation.  
**Snippet**:  
```cpp
#include <tuple> int x; std::string s; std::tie(x, s) = t;
```
**Example**: [tie.cpp](../../examples/C++11/tie.cpp)

### std::make_pair (C++11 Evolution)
**Explanation**: Creates a `std::pair`, now supports move semantics and type deduction.
**Real-World Scenario**: Create key-value pairs for a configuration parser.
**Snippet**:
```cpp
#include <utility> auto p = std::make_pair(1, std::string("value"));
```
**Example**: [make_pair.cpp](../../examples/C++11/make_pair.cpp)

### std::forward_as_tuple (C++11 Addition)
**Explanation**: Creates a tuple of references to its arguments, preserving their value categories. Useful for passing groups of arguments through forwarding interfaces.
**Real-World Scenario**: Pass multiple constructor arguments through `emplace` operations on associative containers.
**Snippet**:
```cpp
#include <tuple>
#include <map>
std::map<int, std::string> m;
m.emplace(std::piecewise_construct,
           std::forward_as_tuple(1),
           std::forward_as_tuple("value"));
```
**Example**: [forward_as_tuple.cpp](../../examples/C++11/forward_as_tuple.cpp)

### std::piecewise_construct (C++11 Addition)
**Explanation**: A tag constant used to select the piecewise constructor of `std::pair`, which constructs each element from a separate tuple of arguments.
**Real-World Scenario**: Insert a complex key-value pair into a map where both key and value require multi-argument construction.
**Snippet**:
```cpp
#include <utility>
#include <tuple>
#include <map>
std::map<std::string, std::string> m;
m.emplace(std::piecewise_construct,
           std::forward_as_tuple("key"),
           std::forward_as_tuple(10, 'x')); // string(10, 'x')
```
**Example**: [piecewise_construct.cpp](../../examples/C++11/piecewise_construct.cpp)

### std::type_index (C++11 Addition)
**Explanation**: A copyable, hashable wrapper around `std::type_info` that can be used as a key in associative and unordered containers for runtime type identification.
**Real-World Scenario**: Build a type-based factory or service locator that maps type identifiers to creation functions.
**Snippet**:
```cpp
#include <typeindex>
#include <unordered_map>
#include <string>
std::unordered_map<std::type_index, std::string> typeNames;
typeNames[std::type_index(typeid(int))] = "int";
typeNames[std::type_index(typeid(double))] = "double";
```
**Example**: [type_index.cpp](../../examples/C++11/type_index.cpp)

## Input/Output
### std::to_string (C++11 Addition)
**Explanation**: Converts numeric values to strings.  
**Real-World Scenario**: Format numbers for display in a UI.  
**Snippet**:  
```cpp
#include <string> std::string s = std::to_string(123);
```
**Example**: [to_string.cpp](../../examples/C++11/to_string.cpp)

### std::stoi/stol/stoll (C++11 Addition)
**Explanation**: Converts strings to integers (signed).  
**Real-World Scenario**: Parse user input numbers in a form.  
**Snippet**:  
```cpp
#include <string> int x = std::stoi("123");
```
**Example**: [stoi.cpp](../../examples/C++11/stoi.cpp)

### std::stoul/stoull (C++11 Addition)
**Explanation**: Converts strings to unsigned integers.  
**Real-World Scenario**: Parse unsigned IDs from a configuration file.  
**Snippet**:  
```cpp
#include <string> unsigned long x = std::stoul("123");
```
**Example**: [stoul.cpp](../../examples/C++11/stoul.cpp)

### std::stof/stod/stold (C++11 Addition)
**Explanation**: Converts strings to floating-point numbers.  
**Real-World Scenario**: Parse decimal values from a data file.  
**Snippet**:  
```cpp
#include <string> double x = std::stod("3.14");
```
**Example**: [stod.cpp](../../examples/C++11/stod.cpp)

## Random Number Generation
### std::random_device (C++11 Addition)
**Explanation**: A non-deterministic random number generator that produces cryptographically suitable seeds from hardware entropy sources.
**Real-World Scenario**: Seed a random engine for generating secure session tokens in a web server.
**Snippet**:
```cpp
#include <random>
std::random_device rd;
unsigned int seed = rd();
```
**Example**: [random_device.cpp](../../examples/C++11/random_device.cpp)

### std::mt19937 (C++11 Addition)
**Explanation**: A 32-bit Mersenne Twister pseudo-random number generator with a period of 2^19937-1, providing high-quality random numbers suitable for simulations.
**Real-World Scenario**: Generate random terrain features in a procedural game world.
**Snippet**:
```cpp
#include <random>
std::mt19937 gen(42); // seeded with 42
int value = gen(); // generate random number
```
**Example**: [mt19937.cpp](../../examples/C++11/mt19937.cpp)

### std::mt19937_64 (C++11 Addition)
**Explanation**: A 64-bit variant of the Mersenne Twister engine, producing 64-bit random values for applications requiring larger random ranges.
**Real-World Scenario**: Generate unique 64-bit identifiers for distributed systems where collision probability must be minimized.
**Snippet**:
```cpp
#include <random>
std::mt19937_64 gen(std::random_device{}());
uint64_t value = gen();
```
**Example**: [mt19937_64.cpp](../../examples/C++11/mt19937_64.cpp)

### Random Engines (C++11 Addition)
**Explanation**: C++11 provides several random engine types including `linear_congruential_engine`, `mersenne_twister_engine`, `subtract_with_carry_engine`, and engine adaptors like `discard_block_engine`, `independent_bits_engine`, and `shuffle_order_engine`. Predefined typedefs include `minstd_rand0`, `minstd_rand`, `ranlux24_base`, `ranlux48_base`, `ranlux24`, `ranlux48`, and `knuth_b`.
**Real-World Scenario**: Choose between lightweight (LCG) and high-quality (Mersenne Twister) engines based on performance versus quality requirements.
**Snippet**:
```cpp
#include <random>
std::minstd_rand lcg(42);           // lightweight LCG engine
std::ranlux24 rl(42);               // higher quality, slower
std::knuth_b kb(42);                // shuffle-order adaptor
int a = lcg(), b = rl(), c = kb();
```
**Example**: [random_engines.cpp](../../examples/C++11/random_engines.cpp)

### Random Distributions (C++11 Addition)
**Explanation**: C++11 provides a comprehensive set of distribution classes that transform engine output into specific statistical distributions: uniform (int/real), Bernoulli, binomial, negative binomial, geometric, Poisson, exponential, gamma, Weibull, extreme value, normal, lognormal, chi-squared, Cauchy, Fisher F, Student t, discrete, piecewise constant, and piecewise linear.
**Real-World Scenario**: Simulate realistic event timing using exponential distribution or model natural phenomena with normal distribution.
**Snippet**:
```cpp
#include <random>
std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> dice(1, 6);
std::normal_distribution<double> height(170.0, 10.0);
std::exponential_distribution<double> arrival(1.5);
int roll = dice(gen);
double h = height(gen);
double t = arrival(gen);
```
**Example**: [random_distributions.cpp](../../examples/C++11/random_distributions.cpp)

## Regular Expressions
### std::regex (C++11 Addition)
**Explanation**: A class that holds a compiled regular expression pattern supporting multiple grammars (ECMAScript, POSIX, grep, egrep, awk).
**Real-World Scenario**: Validate email addresses or phone numbers in a user registration form.
**Snippet**:
```cpp
#include <regex>
std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
```
**Example**: [regex.cpp](../../examples/C++11/regex.cpp)

### std::regex_match (C++11 Addition)
**Explanation**: Tests whether an entire string matches a regular expression pattern, returning true only if the full string is consumed by the match.
**Real-World Scenario**: Validate that an input string is a properly formatted date (YYYY-MM-DD).
**Snippet**:
```cpp
#include <regex>
std::regex date_re(R"(\d{4}-\d{2}-\d{2})");
bool valid = std::regex_match("2024-01-15", date_re); // true
```
**Example**: [regex_match.cpp](../../examples/C++11/regex_match.cpp)

### std::regex_search (C++11 Addition)
**Explanation**: Searches a string for the first substring that matches a regular expression pattern, unlike `regex_match` which requires a full-string match.
**Real-World Scenario**: Extract the first URL from a block of text in a web scraper.
**Snippet**:
```cpp
#include <regex>
std::regex url_re(R"(https?://\S+)");
std::smatch match;
std::string text = "Visit https://example.com for details";
if (std::regex_search(text, match, url_re)) {
    std::string url = match[0]; // "https://example.com"
}
```
**Example**: [regex_search.cpp](../../examples/C++11/regex_search.cpp)

### std::regex_replace (C++11 Addition)
**Explanation**: Replaces all occurrences of a pattern in a string with a replacement string, supporting back-references to captured groups.
**Real-World Scenario**: Redact credit card numbers in log files by replacing digits with asterisks.
**Snippet**:
```cpp
#include <regex>
std::regex digits(R"(\d{4}-\d{4}-\d{4}-(\d{4}))");
std::string result = std::regex_replace("Card: 1234-5678-9012-3456",
                                         digits, "****-****-****-$1");
```
**Example**: [regex_replace.cpp](../../examples/C++11/regex_replace.cpp)

### std::regex_iterator (C++11 Addition)
**Explanation**: An iterator that traverses all non-overlapping matches of a regex pattern in a string, enabling enumeration of all matches.
**Real-World Scenario**: Extract all hashtags from a social media post.
**Snippet**:
```cpp
#include <regex>
std::string text = "#hello #world #cpp11";
std::regex tag_re(R"(#\w+)");
auto begin = std::sregex_iterator(text.begin(), text.end(), tag_re);
auto end = std::sregex_iterator();
for (auto it = begin; it != end; ++it) {
    std::string tag = (*it)[0];
}
```
**Example**: [regex_iterator.cpp](../../examples/C++11/regex_iterator.cpp)

### std::regex_token_iterator (C++11 Addition)
**Explanation**: An iterator that accesses specific sub-matches or the parts of a string between matches, enabling tokenization and field extraction.
**Real-World Scenario**: Split a CSV line into fields using a comma delimiter pattern.
**Snippet**:
```cpp
#include <regex>
std::string csv = "Alice,30,Engineer";
std::regex sep(",");
std::sregex_token_iterator it(csv.begin(), csv.end(), sep, -1);
std::sregex_token_iterator end;
for (; it != end; ++it) {
    std::string field = *it;
}
```
**Example**: [regex_token_iterator.cpp](../../examples/C++11/regex_token_iterator.cpp)

### Regex Match Types (C++11 Addition)
**Explanation**: `std::match_results` (with aliases `smatch`, `cmatch`, `wsmatch`, `wcmatch`) stores the results of a regex match, including the full match, sub-matches, prefix, suffix, and match flags like `match_default`, `match_not_bol`, `match_any`, and `format_default`.
**Real-World Scenario**: Parse a log entry into structured fields (timestamp, severity, message) using named capture groups.
**Snippet**:
```cpp
#include <regex>
std::string log = "[2024-01-15] ERROR: disk full";
std::regex re(R"(\[(\d{4}-\d{2}-\d{2})\] (\w+): (.+))");
std::smatch m;
if (std::regex_match(log, m, re)) {
    std::string date = m[1];     // "2024-01-15"
    std::string level = m[2];    // "ERROR"
    std::string msg = m[3];      // "disk full"
}
```
**Example**: [regex_match_types.cpp](../../examples/C++11/regex_match_types.cpp)

## Chrono Library
### std::chrono::duration (C++11 Addition)
**Explanation**: Represents a time interval with a specified tick period, enabling type-safe time arithmetic. The representation type and period are template parameters.
**Real-World Scenario**: Define timeout intervals with compile-time unit safety in a network library.
**Snippet**:
```cpp
#include <chrono>
std::chrono::duration<double> halfSecond(0.5);
std::chrono::milliseconds timeout(500);
auto total = timeout + std::chrono::milliseconds(100); // 600ms
```
**Example**: [chrono_duration.cpp](../../examples/C++11/chrono_duration.cpp)

### std::chrono::time_point (C++11 Addition)
**Explanation**: Represents a specific point in time relative to a clock's epoch, expressed as a duration since that epoch. Supports arithmetic with durations.
**Real-World Scenario**: Record when a cache entry was created and check if it has expired.
**Snippet**:
```cpp
#include <chrono>
auto now = std::chrono::system_clock::now();
auto expiry = now + std::chrono::hours(24);
bool expired = std::chrono::system_clock::now() > expiry;
```
**Example**: [chrono_time_point.cpp](../../examples/C++11/chrono_time_point.cpp)

### std::chrono::system_clock (C++11 Addition)
**Explanation**: A clock representing wall-clock time from the system-wide real-time clock. Its time points can be converted to/from `time_t` for interoperability with C APIs.
**Real-World Scenario**: Timestamp log entries with the current wall-clock time.
**Snippet**:
```cpp
#include <chrono>
#include <ctime>
auto now = std::chrono::system_clock::now();
std::time_t t = std::chrono::system_clock::to_time_t(now);
```
**Example**: [system_clock.cpp](../../examples/C++11/system_clock.cpp)

### std::chrono::steady_clock (C++11 Addition)
**Explanation**: A monotonic clock that is guaranteed to never go backwards, making it ideal for measuring elapsed time. Unaffected by system clock adjustments.
**Real-World Scenario**: Measure the execution time of an algorithm for performance benchmarking.
**Snippet**:
```cpp
#include <chrono>
auto start = std::chrono::steady_clock::now();
// ... work ...
auto end = std::chrono::steady_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
```
**Example**: [steady_clock.cpp](../../examples/C++11/steady_clock.cpp)

### std::chrono::high_resolution_clock (C++11 Addition)
**Explanation**: The clock with the shortest tick period available on the system, providing the highest resolution timing. May be an alias for `system_clock` or `steady_clock`.
**Real-World Scenario**: Profile micro-benchmarks where nanosecond precision is needed.
**Snippet**:
```cpp
#include <chrono>
auto start = std::chrono::high_resolution_clock::now();
// ... fine-grained operation ...
auto end = std::chrono::high_resolution_clock::now();
auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
```
**Example**: [high_resolution_clock.cpp](../../examples/C++11/high_resolution_clock.cpp)

### Duration Typedefs (C++11 Addition)
**Explanation**: Predefined `std::chrono::duration` aliases for common time units: `nanoseconds`, `microseconds`, `milliseconds`, `seconds`, `minutes`, and `hours`, providing convenient and readable time specifications.
**Real-World Scenario**: Set timeouts, delays, and intervals using expressive, self-documenting duration types.
**Snippet**:
```cpp
#include <chrono>
std::chrono::nanoseconds ns(1000);
std::chrono::microseconds us(500);
std::chrono::milliseconds ms(100);
std::chrono::seconds s(5);
std::chrono::minutes m(2);
std::chrono::hours h(1);
auto total = std::chrono::duration_cast<std::chrono::seconds>(h + m + s); // 3725s
```
**Example**: [duration_typedefs.cpp](../../examples/C++11/duration_typedefs.cpp)

## Ratio Library
### std::ratio (C++11 Addition)
**Explanation**: A compile-time rational number representation using two `intmax_t` template parameters (numerator and denominator), forming the foundation for type-safe unit conversions and the chrono library.
**Real-World Scenario**: Define compile-time conversion factors between measurement units in a physics engine.
**Snippet**:
```cpp
#include <ratio>
using one_third = std::ratio<1, 3>;
using two_thirds = std::ratio<2, 3>;
static_assert(one_third::num == 1 && one_third::den == 3, "1/3");
```
**Example**: [ratio.cpp](../../examples/C++11/ratio.cpp)

### Ratio Operations (C++11 Addition)
**Explanation**: Compile-time arithmetic and comparison operations on `std::ratio` types: `ratio_add`, `ratio_subtract`, `ratio_multiply`, `ratio_divide`, `ratio_equal`, `ratio_not_equal`, `ratio_less`, `ratio_less_equal`, `ratio_greater`, and `ratio_greater_equal`.
**Real-World Scenario**: Verify unit conversion factors at compile time in a dimensional analysis library.
**Snippet**:
```cpp
#include <ratio>
using half = std::ratio<1, 2>;
using third = std::ratio<1, 3>;
using sum = std::ratio_add<half, third>; // 5/6
static_assert(sum::num == 5 && sum::den == 6, "1/2 + 1/3 = 5/6");
static_assert(std::ratio_less<third, half>::value, "1/3 < 1/2");
```
**Example**: [ratio_operations.cpp](../../examples/C++11/ratio_operations.cpp)

### SI Prefixes (C++11 Addition)
**Explanation**: Predefined `std::ratio` typedefs for SI metric prefixes: `atto`, `femto`, `pico`, `nano`, `micro`, `milli`, `centi`, `deci`, `deca`, `hecto`, `kilo`, `mega`, `giga`, `tera`, `peta`, and `exa`, enabling type-safe metric unit calculations.
**Real-World Scenario**: Define storage sizes or network bandwidth units using SI prefixes for a system monitoring tool.
**Snippet**:
```cpp
#include <ratio>
static_assert(std::kilo::num == 1000, "kilo = 1000");
static_assert(std::mega::num == 1000000, "mega = 10^6");
static_assert(std::milli::num == 1 && std::milli::den == 1000, "milli = 1/1000");
static_assert(std::nano::num == 1 && std::nano::den == 1000000000, "nano = 10^-9");
```
**Example**: [si_prefixes.cpp](../../examples/C++11/si_prefixes.cpp)