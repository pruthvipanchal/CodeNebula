# C++11 STL Concepts

This document covers new or evolved C++11 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++11/). Only additions or evolutions from C++98/C++03 are included.

## Containers
### std::array (C++11 Addition)
**Explanation**: Fixed-size array with STL-like interface, safer than C-style arrays.  
**Real-World Scenario**: Store fixed-size game board coordinates in a puzzle game.  
**Snippet**:  
```cpp
#include <array> std::array<int, 5> arr = {1, 2, 3, 4, 5};
```
**Example**: [array.cpp](../examples/C++11/array.cpp)

### std::forward_list (C++11 Addition)
**Explanation**: Singly-linked list for efficient insertions at the front.  
**Real-World Scenario**: Implement a lightweight event log with frequent additions.  
**Snippet**:  
```cpp
#include <forward_list> std::forward_list<int> flist = {1, 2, 3};
```
**Example**: [forward_list.cpp](../examples/C++11/forward_list.cpp)

### std::unordered_set (C++11 Addition)
**Explanation**: Hash-based container for unique elements, offering O(1) lookup.  
**Real-World Scenario**: Store unique user IDs in a fast-access membership system.  
**Snippet**:  
```cpp
#include <unordered_set> std::unordered_set<int> uset = {1, 2, 3};
```
**Example**: [unordered_set.cpp](../examples/C++11/unordered_set.cpp)

### std::unordered_multiset (C++11 Addition)
**Explanation**: Hash-based container allowing duplicate elements.  
**Real-World Scenario**: Track multiple occurrences of event IDs in a log.  
**Snippet**:  
```cpp
#include <unordered_set> std::unordered_multiset<int> umset = {1, 1, 2};
```
**Example**: [unordered_multiset.cpp](../examples/C++11/unordered_multiset.cpp)

### std::unordered_map (C++11 Addition)
**Explanation**: Hash-based key-value pairs with unique keys, O(1) lookup.  
**Real-World Scenario**: Store user settings by ID in a configuration system.  
**Snippet**:  
```cpp
#include <unordered_map> std::unordered_map<int, std::string> umap = {{1, "A"}};
```
**Example**: [unordered_map.cpp](../examples/C++11/unordered_map.cpp)

### std::unordered_multimap (C++11 Addition)
**Explanation**: Hash-based key-value pairs allowing duplicate keys.  
**Real-World Scenario**: Store multiple phone numbers per contact in an address book.  
**Snippet**:  
```cpp
#include <unordered_map> std::unordered_multimap<int, std::string> ummap = {{1, "A"}};
```
**Example**: [unordered_multimap.cpp](../examples/C++11/unordered_multimap.cpp)

### std::vector (C++11 Evolution)
**Explanation**: Dynamic array, now supports move semantics and `emplace_back`.  
**Real-World Scenario**: Efficiently add complex objects to a chat message list.  
**Snippet**:  
```cpp
#include <vector> std::vector<int> vec; vec.emplace_back(1);
```
**Example**: [vector.cpp](../examples/C++11/vector.cpp)

### std::list (C++11 Evolution)
**Explanation**: Doubly-linked list, supports move semantics and `emplace`.  
**Real-World Scenario**: Efficiently insert objects into a playlist.  
**Snippet**:  
```cpp
#include <list> std::list<int> lst; lst.emplace_front(1);
```
**Example**: [list.cpp](../examples/C++11/list.cpp)

### std::deque (C++11 Evolution)
**Explanation**: Double-ended queue, supports move semantics and `emplace`.  
**Real-World Scenario**: Add tasks to a scheduler queue efficiently.  
**Snippet**:  
```cpp
#include <deque> std::deque<int> dq; dq.emplace_back(1);
```
**Example**: [deque.cpp](../examples/C++11/deque.cpp)

### std::set (C++11 Evolution)
**Explanation**: Sorted unique elements, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert unique IDs into a membership system efficiently.  
**Snippet**:  
```cpp
#include <set> std::set<int> s; s.emplace(1);
```
**Example**: [set.cpp](../examples/C++11/set.cpp)

### std::map (C++11 Evolution)
**Explanation**: Sorted key-value pairs, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert student grades by ID efficiently.  
**Snippet**:  
```cpp
#include <map> std::map<int, std::string> m; m.emplace(1, "A");
```
**Example**: [map.cpp](../examples/C++11/map.cpp)

### std::multiset (C++11 Evolution)
**Explanation**: Sorted collection with duplicates, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert multiple event timestamps in a log.  
**Snippet**:  
```cpp
#include <multiset> std::multiset<int> ms; ms.emplace(1);
```
**Example**: [multiset.cpp](../examples/C++11/multiset.cpp)

### std::multimap (C++11 Evolution)
**Explanation**: Sorted key-value pairs with duplicates, supports move semantics and `emplace`.  
**Real-World Scenario**: Insert multiple phone numbers per contact.  
**Snippet**:  
```cpp
#include <map> std::multimap<int, std::string> mm; mm.emplace(1, "A");
```
**Example**: [multimap.cpp](../examples/C++11/multimap.cpp)

### std::stack (C++11 Evolution)
**Explanation**: LIFO container adaptor, supports move semantics and `emplace`.  
**Real-World Scenario**: Add undo operations to a text editor efficiently.  
**Snippet**:  
```cpp
#include <stack> std::stack<int> stk; stk.emplace(1);
```
**Example**: [stack.cpp](../examples/C++11/stack.cpp)

### std::queue (C++11 Evolution)
**Explanation**: FIFO container adaptor, supports move semantics and `emplace`.  
**Real-World Scenario**: Add print jobs to a printer queue efficiently.  
**Snippet**:  
```cpp
#include <queue> std::queue<int> q; q.emplace(1);
```
**Example**: [queue.cpp](../examples/C++11/queue.cpp)

### std::priority_queue (C++11 Evolution)
**Explanation**: Queue with largest element at top, supports move semantics and `emplace`.  
**Real-World Scenario**: Add tasks to a priority-based scheduler.  
**Snippet**:  
```cpp
#include <queue> std::priority_queue<int> pq; pq.emplace(1);
```
**Example**: [priority_queue.cpp](../examples/C++11/priority_queue.cpp)

## Algorithms
### std::all_of (C++11 Addition)
**Explanation**: Checks if all elements in a range satisfy a predicate.  
**Real-World Scenario**: Verify all scores in a game are positive.  
**Snippet**:  
```cpp
#include <algorithm> std::all_of(vec.begin(), vec.end(), isPositive);
```
**Example**: [all_of.cpp](../examples/C++11/all_of.cpp)

### std::any_of (C++11 Addition)
**Explanation**: Checks if any element in a range satisfies a predicate.  
**Real-World Scenario**: Check if any user input is invalid in a form.  
**Snippet**:  
```cpp
#include <algorithm> std::any_of(vec.begin(), vec.end(), isInvalid);
```
**Example**: [any_of.cpp](../examples/C++11/any_of.cpp)

### std::none_of (C++11 Addition)
**Explanation**: Checks if no elements in a range satisfy a predicate.  
**Real-World Scenario**: Ensure no tasks in a queue are overdue.  
**Snippet**:  
```cpp
#include <algorithm> std::none_of(vec.begin(), vec.end(), isOverdue);
```
**Example**: [none_of.cpp](../examples/C++11/none_of.cpp)

### std::find_if_not (C++11 Addition)
**Explanation**: Finds the first element not satisfying a predicate.  
**Real-World Scenario**: Find the first non-completed task in a to-do list.  
**Snippet**:  
```cpp
#include <algorithm> std::find_if_not(vec.begin(), vec.end(), isCompleted);
```
**Example**: [find_if_not.cpp](../examples/C++11/find_if_not.cpp)

### std::copy_if (C++11 Addition)
**Explanation**: Copies elements satisfying a predicate to a destination.  
**Real-World Scenario**: Copy valid user inputs to a filtered list.  
**Snippet**:  
```cpp
#include <algorithm> std::copy_if(vec.begin(), vec.end(), dest.begin(), isValid);
```
**Example**: [copy_if.cpp](../examples/C++11/copy_if.cpp)

### std::copy_n (C++11 Addition)
**Explanation**: Copies n elements from a range to a destination.  
**Real-World Scenario**: Copy the first n log entries to a report.  
**Snippet**:  
```cpp
#include <algorithm> std::copy_n(vec.begin(), 5, dest.begin());
```
**Example**: [copy_n.cpp](../examples/C++11/copy_n.cpp)

### std::move (Algorithm, C++11 Evolution)
**Explanation**: Moves elements to a destination, leveraging move semantics.  
**Real-World Scenario**: Transfer large objects between buffers in a network app.  
**Snippet**:  
```cpp
#include <algorithm> std::move(vec.begin(), vec.end(), dest.begin());
```
**Example**: [move_algorithm.cpp](../examples/C++11/move_algorithm.cpp)

### std::move_backward (C++11 Evolution)
**Explanation**: Moves elements in reverse order, leveraging move semantics.  
**Real-World Scenario**: Reverse-move data in a memory manager.  
**Snippet**:  
```cpp
#include <algorithm> std::move_backward(vec.begin(), vec.end(), dest.end());
```
**Example**: [move_backward.cpp](../examples/C++11/move_backward.cpp)

### std::is_sorted (C++11 Addition)
**Explanation**: Checks if a range is sorted.  
**Real-World Scenario**: Verify a leaderboard is sorted by score.  
**Snippet**:  
```cpp
#include <algorithm> std::is_sorted(vec.begin(), vec.end());
```
**Example**: [is_sorted.cpp](../examples/C++11/is_sorted.cpp)

### std::is_sorted_until (C++11 Addition)
**Explanation**: Finds the first unsorted element in a range.  
**Real-World Scenario**: Identify where sorting fails in a dataset.  
**Snippet**:  
```cpp
#include <algorithm> std::is_sorted_until(vec.begin(), vec.end());
```
**Example**: [is_sorted_until.cpp](../examples/C++11/is_sorted_until.cpp)

### std::partition_copy (C++11 Addition)
**Explanation**: Copies elements to two destinations based on a predicate.  
**Real-World Scenario**: Separate completed and pending tasks in a scheduler.  
**Snippet**:  
```cpp
#include <algorithm> std::partition_copy(vec.begin(), vec.end(), dest1.begin(), dest2.begin(), isCompleted);
```
**Example**: [partition_copy.cpp](../examples/C++11/partition_copy.cpp)

### std::partition_point (C++11 Addition)
**Explanation**: Finds the partition point in a partitioned range.  
**Real-World Scenario**: Locate the boundary between completed and pending tasks.  
**Snippet**:  
```cpp
#include <algorithm> std::partition_point(vec.begin(), vec.end(), isCompleted);
```
**Example**: [partition_point.cpp](../examples/C++11/partition_point.cpp)

### std::shuffle (C++11 Addition)
**Explanation**: Randomly shuffles elements in a range using a random engine.  
**Real-World Scenario**: Shuffle a deck of cards in a game.  
**Snippet**:  
```cpp
#include <algorithm> #include <random> std::shuffle(vec.begin(), vec.end(), std::default_random_engine());
```
**Example**: [shuffle.cpp](../examples/C++11/shuffle.cpp)

### std::minmax (C++11 Addition)
**Explanation**: Returns both minimum and maximum of two values.  
**Real-World Scenario**: Find the cheapest and most expensive products in a store.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax(a, b);
```
**Example**: [minmax.cpp](../examples/C++11/minmax.cpp)

### std::minmax_element (C++11 Addition)
**Explanation**: Finds both minimum and maximum elements in a range.  
**Real-World Scenario**: Identify lowest and highest scores in a leaderboard.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax_element(vec.begin(), vec.end());
```
**Example**: [minmax_element.cpp](../examples/C++11/minmax_element.cpp)

## Utilities
### std::tuple (C++11 Addition)
**Explanation**: Stores a fixed-size collection of heterogeneous values.  
**Real-World Scenario**: Return multiple values (e.g., position and velocity) from a physics function.  
**Snippet**:  
```cpp
#include <tuple> std::tuple<int, std::string> t = {1, "value"};
```
**Example**: [tuple.cpp](../examples/C++11/tuple.cpp)

### std::tie (C++11 Addition)
**Explanation**: Unpacks a tuple into individual variables.  
**Real-World Scenario**: Extract position and velocity from a physics calculation.  
**Snippet**:  
```cpp
#include <tuple> int x; std::string s; std::tie(x, s) = t;
```
**Example**: [tie.cpp](../examples/C++11/tie.cpp)

### std::make_pair (C++11 Evolution)
**Explanation**: Creates a `std::pair`, now supports move semantics and type deduction.  
**Real-World Scenario**: Create key-value pairs for a configuration parser.  
**Snippet**:  
```cpp
#include <utility> auto p = std::make_pair(1, std::string("value"));
```
**Example**: [make_pair.cpp](../examples/C++11/make_pair.cpp)

## Input/Output
### std::to_string (C++11 Addition)
**Explanation**: Converts numeric values to strings.  
**Real-World Scenario**: Format numbers for display in a UI.  
**Snippet**:  
```cpp
#include <string> std::string s = std::to_string(123);
```
**Example**: [to_string.cpp](../examples/C++11/to_string.cpp)

### std::stoi/stol/stoll (C++11 Addition)
**Explanation**: Converts strings to integers (signed).  
**Real-World Scenario**: Parse user input numbers in a form.  
**Snippet**:  
```cpp
#include <string> int x = std::stoi("123");
```
**Example**: [stoi.cpp](../examples/C++11/stoi.cpp)

### std::stoul/stoull (C++11 Addition)
**Explanation**: Converts strings to unsigned integers.  
**Real-World Scenario**: Parse unsigned IDs from a configuration file.  
**Snippet**:  
```cpp
#include <string> unsigned long x = std::stoul("123");
```
**Example**: [stoul.cpp](../examples/C++11/stoul.cpp)

### std::stof/stod/stold (C++11 Addition)
**Explanation**: Converts strings to floating-point numbers.  
**Real-World Scenario**: Parse decimal values from a data file.  
**Snippet**:  
```cpp
#include <string> double x = std::stod("3.14");
```
**Example**: [stod.cpp](../examples/C++11/stod.cpp)