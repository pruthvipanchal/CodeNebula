# C++03 STL Concepts

This document covers evolved C++03 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++03/). Only evolutions from C++98 are included.

## Iterator Requirements (C++03 Evolution)
**Explanation**: C++03 clarified iterator requirements, ensuring stricter definitions for iterator categories (e.g., Input, Output, Forward, Bidirectional, Random Access) to improve portability and correctness.  
**Real-World Scenario**: Write a generic algorithm that relies on precise iterator behavior in a data processing library.  
**Snippet**:  
```cpp
#include <vector> std::vector<int>::iterator it; // Stricter requirements ensure portability
```
**Example**: [iterator_requirements.cpp](../examples/C++03/iterator_requirements.cpp)