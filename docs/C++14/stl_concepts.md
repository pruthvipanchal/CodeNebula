# C++14 STL Concepts

This document covers new or evolved C++14 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++14/). Only additions or evolutions from C++98/C++03/C++11 are included.

## Utilities
### std::make_unique (C++14 Addition)
**Explanation**: Creates a `std::unique_ptr`, complementing `std::make_shared` from C++11.  
**Real-World Scenario**: Safely allocate a unique resource in a system without raw `new`.  
**Snippet**:  
```cpp
#include <memory> auto ptr = std::make_unique<int>(5);
```
**Example**: [make_unique.cpp](../examples/C++14/make_unique.cpp)

### std::tuple Addressing via Types (C++14 Evolution)
**Explanation**: Access tuple elements by type using `std::get<T>`, assuming unique types.  
**Real-World Scenario**: Retrieve specific data from a heterogeneous tuple in a physics engine.  
**Snippet**:  
```cpp
#include <tuple> std::tuple<int, std::string> t{1, "value"}; auto s = std::get<std::string>(t);
```
**Example**: [tuple_addressing.cpp](../examples/C++14/tuple_addressing.cpp)

### std::exchange (C++14 Addition)
**Explanation**: Replaces a value with a new one and returns the old value.  
**Real-World Scenario**: Swap a resource pointer in a resource manager while keeping the old value.  
**Snippet**:  
```cpp
#include <utility> int x = 5; int old = std::exchange(x, 10);
```
**Example**: [exchange.cpp](../examples/C++14/exchange.cpp)

## Algorithms
### std::equal_range (C++14 Evolution)
**Explanation**: Returns range of equal elements, now supports heterogeneous comparisons.  
**Real-World Scenario**: Find all matching keys in a sorted configuration list with custom comparators.  
**Snippet**:  
```cpp
#include <algorithm> auto [first, last] = std::equal_range(vec.begin(), vec.end(), 5);
```
**Example**: [equal_range.cpp](../examples/C++14/equal_range.cpp)

### std::mismatch (C++14 Evolution)
**Explanation**: Finds first mismatch between ranges, now supports heterogeneous predicates.  
**Real-World Scenario**: Compare two configuration lists with custom comparison logic.  
**Snippet**:  
```cpp
#include <algorithm> auto [it1, it2] = std::mismatch(vec1.begin(), vec1.end(), vec2.begin(), pred);
```
**Example**: [mismatch.cpp](../examples/C++14/mismatch.cpp)

### std::is_permutation (C++14 Evolution)
**Explanation**: Checks if one range is a permutation of another, now supports custom predicates.  
**Real-World Scenario**: Verify if two task lists are equivalent regardless of order in a scheduler.  
**Snippet**:  
```cpp
#include <algorithm> bool same = std::is_permutation(vec1.begin(), vec1.end(), vec2.begin(), pred);
```
**Example**: [is_permutation.cpp](../examples/C++14/is_permutation.cpp)

### std::minmax (C++14 Evolution)
**Explanation**: Returns min and max of values, now supports initializer lists.  
**Real-World Scenario**: Find cheapest and most expensive products in a store from a list.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax({1, 2, 3});
```
**Example**: [minmax.cpp](../examples/C++14/minmax.cpp)

### std::minmax_element (C++14 Evolution)
**Explanation**: Finds min and max elements in a range, now supports custom comparators.  
**Real-World Scenario**: Identify lowest and highest scores in a leaderboard with custom ordering.  
**Snippet**:  
```cpp
#include <algorithm> auto [min, max] = std::minmax_element(vec.begin(), vec.end(), comp);
```
**Example**: [minmax_element.cpp](../examples/C++14/minmax_element.cpp)