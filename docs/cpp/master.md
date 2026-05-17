<div align="center">

# CodeNebula — C++ Master Concepts Index

**The complete reference to every C++ concept from C++98 through C++26.**

[![Standards](https://img.shields.io/badge/Standards-8-00599C?logo=cplusplus)](./)
[![Concepts](https://img.shields.io/badge/Concepts-968-blueviolet)](./)
[![Format](https://img.shields.io/badge/Format-Tables%20%2B%20Descriptions-success)](./)

</div>

---

## At a Glance

| | C++98 | C++03 | C++11 | C++14 | C++17 | C++20 | C++23 | C++26 | **Total** |
|:--|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:---------:|
| **Core Language** | 52 | 3 | 53 | 10 | 19 | 39 | 13 | 11 | **200** |
| **STL** | 161 | 2 | 160 | 13 | 78 | 245 | 76 | 33 | **768** |
| **Total** | 213 | 5 | 213 | 23 | 97 | 284 | 89 | 44 | **968** |

## Navigation

- [C++98 — The Foundation](#c98--the-foundation)
- [C++03 — The Bug-Fix Release](#c03--the-bug-fix-release)
- [C++11 — Modern C++ Revolution](#c11--modern-c-revolution)
- [C++14 — Modern C++ Refined](#c14--modern-c-refined)
- [C++17 — Practical Modern C++](#c17--practical-modern-c)
- [C++20 — The Big Four](#c20--the-big-four)
- [C++23 — Completing Modern C++](#c23--completing-modern-c)
- [C++26 — The Next Frontier](#c26--the-next-frontier)

---

## C++98 — The Foundation

> **52 core language features · 161 STL components** | [Core Language](C++98/core_language.md) · [STL](C++98/stl_concepts.md)

The original ISO C++ standard. Established classes, templates, the STL, and exception handling as the building blocks of C++.

### Core Language

| Concept | Description |
|:--------|:------------|
| Basic types (`int`, `float`, `double`, `char`, `bool`) | Fundamental built-in data types for values |
| Enumerations (unscoped enums) | Named integer constants grouped under a type |
| Unions | Memory-sharing type that holds one member at a time |
| Bitfields | Specify exact bit widths for struct members |
| `sizeof` operator | Query the byte size of a type or object |
| Pointers | Variables storing memory addresses of objects |
| References | Aliases to existing objects, cannot be null |
| Arrays | Fixed-size contiguous sequences of elements |
| Functions | Named blocks of reusable executable code |
| Function overloading | Multiple functions sharing a name, differing in parameters |
| Default arguments | Parameter values used when caller omits them |
| Inline functions | Hint to expand function body at the call site |
| Function pointers | Pointers that store addresses of functions |
| Pointers to members | Pointers to class data members or member functions |
| Classes | User-defined types bundling data and behavior |
| Objects | Instances of classes with their own state |
| Constructors | Special functions that initialize objects |
| Copy constructor | Creates a new object as a copy of another |
| Destructors | Clean up resources when objects are destroyed |
| Copy assignment operator | Assigns one object's state to another existing object |
| Conversion functions | Implicit or explicit type-conversion operators |
| Inheritance — Single | Derive a class from one base class |
| Inheritance — Multiple | Derive a class from two or more base classes |
| Inheritance — Virtual | Resolve diamond-problem ambiguity in inheritance hierarchies |
| Polymorphism | Objects of different types respond to the same interface |
| Virtual functions | Functions resolved at runtime via vtable dispatch |
| Pure virtual functions | Declare interface methods with no base implementation |
| Abstract classes | Classes with pure virtuals that cannot be instantiated |
| Encapsulation | Bundling data with methods that control access |
| Access specifiers (`public`, `private`, `protected`) | Control visibility of class members |
| Friend functions | Non-member functions granted access to private members |
| Friend classes | Classes granted access to another class's privates |
| Nested classes | Classes defined inside another class's scope |
| Local classes | Classes defined inside a function body |
| Operator overloading | Define custom behavior for built-in operators |
| Function templates | Generic functions parameterized by type |
| Class templates | Generic classes parameterized by type |
| Exception handling (`try`, `catch`, `throw`) | Structured error propagation and recovery |
| Namespaces | Named scopes to prevent identifier collisions |
| Scope resolution operator (`::`) | Access members of a namespace, class, or enum |
| Dynamic memory (`new`, `delete`) | Heap allocation and deallocation of objects |
| Type casting (`static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`) | Explicit type conversions with varying safety levels |
| RTTI (Run-time type information) | Identify object types at runtime |
| `typeid` | Retrieve type information of an expression at runtime |
| Storage class specifiers (`static`, `extern`, `register`) | Control storage duration and linkage of variables |
| `volatile` keyword | Prevent compiler optimization of memory reads/writes |
| `mutable` keyword | Allow modification of a member inside const methods |
| Conditional (ternary) operator | Inline `condition ? true_val : false_val` expression |
| Comma operator | Evaluate two expressions, return the second |
| Preprocessor directives (`#define`, `#include`, `#ifdef`, etc.) | Compile-time text substitution and conditional compilation |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::vector` | Dynamic array with contiguous storage |
| `std::list` | Doubly-linked list for fast insert/erase anywhere |
| `std::deque` | Double-ended queue with fast front/back operations |
| `std::set` | Sorted unique-element container (red-black tree) |
| `std::map` | Sorted key-value associative container |
| `std::multiset` | Sorted container allowing duplicate elements |
| `std::multimap` | Sorted key-value container allowing duplicate keys |
| `std::stack` | LIFO container adaptor |
| `std::queue` | FIFO container adaptor |
| `std::priority_queue` | Heap-based priority container adaptor |
| `std::bitset` | Fixed-size sequence of bits with bitwise operations |

#### Iterators

| Iterator | Description |
|:---------|:------------|
| Input iterator | Read-only, single-pass forward traversal |
| Output iterator | Write-only, single-pass forward traversal |
| Forward iterator | Read/write, multi-pass forward traversal |
| Bidirectional iterator | Forward + backward traversal |
| Random access iterator | Bidirectional + constant-time jumps |
| Iterator traits | Type information query for iterator properties |
| `std::iterator` | Base class template for custom iterators |
| `std::advance` | Move iterator forward by N positions |
| `std::distance` | Count elements between two iterators |
| `std::next` / `std::prev` | Return iterator advanced/retreated by N |

<details>
<summary><b>Iterator Adaptors</b> (8)</summary>

| Adaptor | Description |
|:--------|:------------|
| `std::reverse_iterator` | Traverse a range in reverse order |
| `std::back_insert_iterator` | Insert at container back via `push_back` |
| `std::front_insert_iterator` | Insert at container front via `push_front` |
| `std::insert_iterator` | Insert at a specified position |
| `std::istream_iterator` | Read values from an input stream |
| `std::ostream_iterator` | Write values to an output stream |
| `std::istreambuf_iterator` | Read characters from a stream buffer |
| `std::ostreambuf_iterator` | Write characters to a stream buffer |

</details>

<details>
<summary><b>Algorithms</b> (54)</summary>

| Algorithm | Purpose |
|:----------|:--------|
| `std::for_each` | Apply a function to every element in a range |
| `std::find` | Find first element equal to a value |
| `std::find_if` | Find first element satisfying a predicate |
| `std::find_end` | Find last occurrence of a subsequence |
| `std::find_first_of` | Find first element from a set of candidates |
| `std::adjacent_find` | Find first pair of adjacent equal elements |
| `std::count` | Count elements equal to a value |
| `std::count_if` | Count elements satisfying a predicate |
| `std::mismatch` | Find first position where two ranges differ |
| `std::equal` | Check if two ranges are element-wise equal |
| `std::search` | Find first occurrence of a subsequence |
| `std::search_n` | Find N consecutive copies of a value |
| `std::copy` | Copy elements from one range to another |
| `std::copy_backward` | Copy elements backward (from end to start) |
| `std::move` (algorithm) | Move elements from one range to another |
| `std::move_backward` | Move elements backward within a range |
| `std::fill` | Fill a range with a value |
| `std::fill_n` | Fill the first N positions with a value |
| `std::transform` | Apply a function to each element, store results |
| `std::generate` | Fill range with values from a generator function |
| `std::generate_n` | Fill first N positions from a generator |
| `std::remove` | Move non-matching elements to front (erase-remove idiom) |
| `std::remove_if` | Remove elements satisfying a predicate |
| `std::replace` | Replace all occurrences of a value |
| `std::replace_if` | Replace elements satisfying a predicate |
| `std::swap` | Exchange the values of two objects |
| `std::swap_ranges` | Swap elements of two ranges |
| `std::iter_swap` | Swap values pointed to by two iterators |
| `std::reverse` | Reverse element order in a range |
| `std::reverse_copy` | Copy a range in reverse order |
| `std::rotate` | Rotate elements so a given element becomes first |
| `std::rotate_copy` | Copy a rotated range |
| `std::unique` | Remove consecutive duplicate elements |
| `std::unique_copy` | Copy without consecutive duplicates |
| `std::partition` | Reorder so predicate-true elements come first |
| `std::stable_partition` | Partition preserving relative order |
| `std::sort` | Sort elements in ascending order |
| `std::stable_sort` | Sort preserving relative order of equal elements |
| `std::partial_sort` | Sort only the first N elements |
| `std::partial_sort_copy` | Copy and partially sort into another range |
| `std::nth_element` | Place Nth element in its sorted position |
| `std::merge` | Merge two sorted ranges into one |
| `std::inplace_merge` | Merge two consecutive sorted subranges in-place |
| `std::includes` | Check if one sorted range contains another |
| `std::set_union` | Union of two sorted ranges |
| `std::set_intersection` | Intersection of two sorted ranges |
| `std::set_difference` | Difference of two sorted ranges |
| `std::set_symmetric_difference` | Symmetric difference of two sorted ranges |
| `std::push_heap` | Add an element to a heap |
| `std::pop_heap` | Remove the top element from a heap |
| `std::make_heap` | Rearrange a range into a heap |
| `std::sort_heap` | Sort a heap into ascending order |
| `std::min` / `std::max` | Return the smaller/larger of two values |
| `std::min_element` / `std::max_element` | Find the smallest/largest element in a range |
| `std::lexicographical_compare` | Compare two ranges lexicographically |
| `std::next_permutation` / `std::prev_permutation` | Generate the next/previous permutation |

</details>

<details>
<summary><b>Numeric Algorithms</b> (4)</summary>

| Algorithm | Purpose |
|:----------|:--------|
| `std::accumulate` | Fold a range into a single value (left fold) |
| `std::inner_product` | Compute dot product of two ranges |
| `std::partial_sum` | Compute running cumulative sums |
| `std::adjacent_difference` | Compute differences between consecutive elements |

</details>

<details>
<summary><b>Function Objects / Functors</b> (24)</summary>

| Functor | Description |
|:--------|:------------|
| `std::unary_function` | Base for unary function objects (deprecated C++11) |
| `std::binary_function` | Base for binary function objects (deprecated C++11) |
| `std::plus` | Binary functor for addition |
| `std::minus` | Binary functor for subtraction |
| `std::multiplies` | Binary functor for multiplication |
| `std::divides` | Binary functor for division |
| `std::modulus` | Binary functor for modulo |
| `std::negate` | Unary functor for negation |
| `std::equal_to` | Binary comparison for `==` |
| `std::not_equal_to` | Binary comparison for `!=` |
| `std::greater` | Binary comparison for `>` |
| `std::less` | Binary comparison for `<` |
| `std::greater_equal` | Binary comparison for `>=` |
| `std::less_equal` | Binary comparison for `<=` |
| `std::logical_and` | Binary functor for logical AND |
| `std::logical_or` | Binary functor for logical OR |
| `std::logical_not` | Unary functor for logical NOT |
| `std::unary_negate` | Negate a unary predicate |
| `std::binary_negate` | Negate a binary predicate |
| `std::binder1st` / `std::binder2nd` | Bind an argument to a binary function (deprecated C++11) |
| `std::pointer_to_unary_function` | Wrap a unary function pointer as a functor |
| `std::pointer_to_binary_function` | Wrap a binary function pointer as a functor |
| `std::mem_fun` | Wrap member function via pointer (deprecated C++11) |
| `std::mem_fun_ref` | Wrap member function via reference (deprecated C++11) |

</details>

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::pair` | Hold two heterogeneous values as a single unit |
| `std::string` | Dynamic character string with rich operations |
| `std::auto_ptr` | Ownership-transferring smart pointer (deprecated C++11) |
| `std::rel_ops` | Generate relational operators from `==` and `<` |
| `std::numeric_limits` | Query properties of arithmetic types |

<details>
<summary><b>Numerics</b> (2)</summary>

| Component | Description |
|:----------|:------------|
| `std::valarray` | Numeric array with element-wise operations |
| `std::complex` | Complex number representation and arithmetic |

</details>

<details>
<summary><b>Memory</b> (1)</summary>

| Component | Description |
|:----------|:------------|
| `std::allocator` | Default memory allocator for STL containers |

</details>

<details>
<summary><b>Exception Classes</b> (14)</summary>

| Exception | Description |
|:----------|:------------|
| `std::exception` | Base class for all standard exceptions |
| `std::runtime_error` | Error detectable only at runtime |
| `std::logic_error` | Error due to flawed program logic |
| `std::out_of_range` | Index or key outside valid bounds |
| `std::invalid_argument` | Invalid argument passed to a function |
| `std::overflow_error` | Arithmetic overflow detected |
| `std::underflow_error` | Arithmetic underflow detected |
| `std::length_error` | Attempt to exceed maximum allowed size |
| `std::domain_error` | Math function called outside its domain |
| `std::range_error` | Result outside representable range |
| `std::bad_alloc` | Memory allocation failure |
| `std::bad_cast` | Invalid `dynamic_cast` on a reference |
| `std::bad_typeid` | `typeid` applied to a null polymorphic pointer |
| `std::bad_exception` | Unexpected exception handling failure |

</details>

<details>
<summary><b>Localization</b> (2)</summary>

| Component | Description |
|:----------|:------------|
| `std::locale` | Encapsulate cultural formatting conventions |
| `std::locale::facet` | Base class for locale-specific formatting facets |

</details>

<details>
<summary><b>Input/Output</b> (10)</summary>

| Component | Description |
|:----------|:------------|
| `std::iostream` | Combined input/output stream |
| `std::istream` | Input stream for reading data |
| `std::ostream` | Output stream for writing data |
| `std::fstream` | File-based input/output stream |
| `std::ifstream` | File input stream |
| `std::ofstream` | File output stream |
| `std::stringstream` | String-based input/output stream |
| `std::streambuf` | Low-level stream buffer abstraction |
| `std::ios_base` | Base class for all I/O stream state |
| `std::cin` / `std::cout` / `std::cerr` / `std::clog` | Standard global I/O stream objects |

</details>

<details>
<summary><b>C Library Wrappers</b> (9)</summary>

| Header | Purpose |
|:-------|:--------|
| `<cmath>` | Mathematical functions (sin, cos, sqrt, pow, etc.) |
| `<cstdlib>` | General utilities (malloc, rand, atoi, exit, etc.) |
| `<cstring>` | C string manipulation (strlen, strcpy, memcpy, etc.) |
| `<cstdio>` | C-style I/O (printf, scanf, FILE, etc.) |
| `<cctype>` | Character classification (isalpha, isdigit, toupper, etc.) |
| `<climits>` | Integer type limits (INT_MAX, LONG_MIN, etc.) |
| `<cfloat>` | Floating-point type limits (FLT_MAX, DBL_EPSILON, etc.) |
| `<cassert>` | Runtime assertion macro |
| `<ctime>` | Date and time utilities (time, clock, difftime, etc.) |

</details>

---

## C++03 — The Bug-Fix Release

> **3 core language features · 2 STL fixes** | [Core Language](C++03/core_language.md) · [STL](C++03/stl_concepts.md)

A technical correction release that refined value initialization rules and fixed ambiguities. No major new features.

### Core Language

| Concept | Description |
|:--------|:------------|
| Value initialization (refined rules) | Clarified zero- and default-initialization behavior |
| Explicit template argument specification for constructors | Explicitly specify template args when calling templated constructors |
| POD type definition refinement | Clarified rules for Plain Old Data type compatibility |

### STL

| Component | Description |
|:----------|:------------|
| `std::vector<bool>` improvements | Bug fixes for the specialized bool vector |
| Algorithm behavior fixes | Minor corrections to algorithm specifications |

---

## C++11 — Modern C++ Revolution

> **53 core language features · 160 STL additions** | [Core Language](C++11/core_language.md) · [STL](C++11/stl_concepts.md)

The standard that transformed C++ into a modern language. Introduced move semantics, lambdas, smart pointers, `auto`, and built-in threading support.

### Core Language

| Concept | Description |
|:--------|:------------|
| `auto` keyword | Automatic type deduction from initializers |
| `decltype` | Query the type of an expression at compile time |
| Range-based `for` loops | Iterate over containers with concise `for(auto& x : v)` syntax |
| Lambda expressions | Anonymous inline functions with variable capture |
| `nullptr` | Type-safe null pointer constant replacing `NULL` |
| Strongly-typed enums (`enum class`) | Scoped enumerations preventing implicit integer conversion |
| Type traits | Compile-time type property queries and transformations |
| `static_assert` | Compile-time assertion with custom error message |
| Variadic templates | Templates accepting any number of type/value arguments |
| Template aliases (`using`) | Create type aliases for template instantiations |
| Rvalue references | References to temporaries (`&&`) enabling move semantics |
| Move semantics | Transfer resources from temporaries instead of copying |
| Move constructor | Construct by stealing resources from an rvalue |
| Move assignment operator | Assign by stealing resources from an rvalue |
| Perfect forwarding | Preserve value category when passing through templates |
| `std::forward` | Cast to preserve lvalue/rvalue nature during forwarding |
| `std::move` | Cast an lvalue to an rvalue to enable moving |
| Initializer lists | Brace-enclosed lists for uniform container initialization |
| Uniform initialization | Consistent `{}` syntax for all initialization contexts |
| Delegating constructors | One constructor calls another in the same class |
| In-class member initializers (NSDMI) | Default member values declared at the point of definition |
| Explicit conversion operators | Prevent implicit use of user-defined conversions |
| `override` keyword | Verify a virtual function overrides a base class method |
| `final` keyword | Prevent further overriding or derivation |
| `noexcept` specifier | Declare that a function does not throw exceptions |
| `constexpr` (generalized) | Mark functions/variables evaluable at compile time |
| User-defined literals | Create custom literal suffixes (e.g., `42_km`) |
| Raw string literals | Strings with no escape processing (`R"(...)"`) |
| Trailing return types | Declare return type after parameter list with `-> T` |
| `extern template` | Suppress implicit template instantiation in a TU |
| `thread_local` storage | Variables with per-thread lifetime and storage |
| `alignas` and `alignof` | Control and query memory alignment of types |
| `char16_t`, `char32_t` | Fixed-width Unicode character types |
| Unicode string literals (`u8""`, `u""`, `U""`) | UTF-8/16/32 string prefixes |
| Inheriting constructors | Import base class constructors into derived class |
| Unrestricted unions | Unions can hold members with non-trivial special functions |
| Attributes (`[[noreturn]]`, `[[carries_dependency]]`) | Standardized annotation syntax for compiler hints |
| `std::thread` | Launch and manage OS-level threads |
| `std::mutex` | Mutual exclusion lock for thread synchronization |
| `std::lock_guard` | RAII scoped mutex lock |
| `std::unique_lock` | Flexible RAII mutex lock with deferred/timed locking |
| `std::condition_variable` | Block threads until notified by another thread |
| `std::atomic` | Lock-free atomic operations on shared variables |
| Memory model | Formal rules for multi-threaded memory access ordering |
| `std::future` | Retrieve a value from an asynchronous operation |
| `std::promise` | Set a value to be retrieved by a future |
| `std::async` | Launch a function asynchronously, returning a future |
| `std::shared_ptr` | Reference-counted shared ownership smart pointer |
| `std::unique_ptr` | Exclusive ownership smart pointer with zero overhead |
| `std::weak_ptr` | Non-owning observer of a `shared_ptr`-managed object |
| `=default` and `=delete` | Explicitly default or suppress special member functions |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::array` | Fixed-size stack-allocated container |
| `std::forward_list` | Singly-linked list optimized for insert/erase |
| `std::unordered_set` | Hash-based unique-element container |
| `std::unordered_map` | Hash-based key-value associative container |
| `std::unordered_multiset` | Hash-based container allowing duplicate elements |
| `std::unordered_multimap` | Hash-based key-value container allowing duplicate keys |

<details>
<summary><b>Container Improvements</b> (8)</summary>

| Improvement | Description |
|:------------|:------------|
| `std::vector` emplace_back/emplace | Construct elements in-place inside vector |
| `std::list` emplace_front/emplace_back/emplace | Construct elements in-place inside list |
| `std::deque` emplace_front/emplace_back/emplace | Construct elements in-place inside deque |
| `std::map` emplace/emplace_hint | Construct map entries in-place |
| `std::set` emplace/emplace_hint | Construct set entries in-place |
| `std::unordered_map` emplace/emplace_hint | Construct unordered_map entries in-place |
| `std::unordered_set` emplace/emplace_hint | Construct unordered_set entries in-place |
| `std::initializer_list` support | All containers accept brace-enclosed initialization |

</details>

#### Iterators

| Iterator | Description |
|:---------|:------------|
| `std::begin` / `std::end` | Free functions for range begin/end |
| `std::cbegin` / `std::cend` | Free functions for const begin/end |
| `std::rbegin` / `std::rend` | Free functions for reverse begin/end |
| `std::crbegin` / `std::crend` | Free functions for const reverse begin/end |
| `std::move_iterator` | Adaptor that dereferences as an rvalue |

<details>
<summary><b>Algorithms</b> (17)</summary>

| Algorithm | Purpose |
|:----------|:--------|
| `std::all_of` | Check if predicate holds for all elements |
| `std::any_of` | Check if predicate holds for any element |
| `std::none_of` | Check if predicate holds for no elements |
| `std::find_if_not` | Find first element where predicate is false |
| `std::copy_if` | Copy elements satisfying a predicate |
| `std::copy_n` | Copy exactly N elements |
| `std::move` (algorithm) | Move elements from one range to another |
| `std::move_backward` | Move elements backward within a range |
| `std::shuffle` | Randomly reorder elements using a generator |
| `std::is_sorted` | Check if range is sorted |
| `std::is_sorted_until` | Find first out-of-order element |
| `std::is_permutation` | Check if one range is a permutation of another |
| `std::is_heap` | Check if range is a valid heap |
| `std::is_heap_until` | Find first element breaking heap property |
| `std::minmax` | Return both min and max of two values |
| `std::minmax_element` | Find both min and max elements in a range |
| `std::iota` | Fill range with sequentially increasing values |

</details>

#### Function Objects

| Component | Description |
|:----------|:------------|
| `std::function` | Type-erased callable wrapper for any invocable |
| `std::bind` | Bind arguments to a callable, creating a new callable |
| `std::ref` / `std::cref` | Wrap a reference for use with `std::bind` and threads |
| `std::mem_fn` | Wrap a member function pointer into a callable object |

<details>
<summary><b>Type Traits</b> (33)</summary>

| Trait | Description |
|:------|:------------|
| `std::is_integral` | Check if type is an integer type |
| `std::is_floating_point` | Check if type is a floating-point type |
| `std::is_pointer` | Check if type is a pointer type |
| `std::is_array` | Check if type is an array type |
| `std::is_class` | Check if type is a class or struct |
| `std::is_enum` | Check if type is an enumeration |
| `std::is_void` | Check if type is `void` |
| `std::is_same` | Check if two types are identical |
| `std::is_base_of` | Check if one type derives from another |
| `std::is_convertible` | Check if implicit conversion exists |
| `std::is_trivially_copyable` | Check if type can be copied with `memcpy` |
| `std::is_trivially_constructible` | Check if type has trivial construction |
| `std::is_trivially_destructible` | Check if type has trivial destruction |
| `std::is_standard_layout` | Check if type has C-compatible memory layout |
| `std::is_pod` | Check if type is Plain Old Data (deprecated C++20) |
| `std::integral_constant` | Compile-time constant wrapper type |
| `std::true_type` / `std::false_type` | Compile-time boolean constants |
| `std::enable_if` | SFINAE helper to conditionally enable overloads |
| `std::conditional` | Choose between two types at compile time |
| `std::common_type` | Determine the common type of multiple types |
| `std::result_of` | Determine callable return type (deprecated C++17) |
| `std::underlying_type` | Get the underlying integer type of an enum |
| `std::remove_reference` | Strip reference qualifiers from a type |
| `std::remove_cv` / `remove_const` / `remove_volatile` | Strip const/volatile qualifiers |
| `std::add_lvalue_reference` | Add `&` to a type |
| `std::add_rvalue_reference` | Add `&&` to a type |
| `std::make_signed` / `std::make_unsigned` | Convert integer type to signed/unsigned |
| `std::decay` | Apply array/function-to-pointer and remove cv/ref |
| `std::aligned_storage` | Aligned raw storage buffer (deprecated C++23) |
| `std::aligned_union` | Aligned storage for any of several types (deprecated C++23) |

</details>

#### Hashing

| Component | Description |
|:----------|:------------|
| `std::hash` | Function object for computing hash values of types |

#### Error Handling

| Component | Description |
|:----------|:------------|
| `std::system_error` | Exception carrying an error code |
| `std::error_code` | Platform-dependent error code value |
| `std::error_category` | Abstract base defining an error code domain |
| `std::error_condition` | Platform-independent error condition |

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::tuple` | Fixed-size heterogeneous value collection |
| `std::forward_as_tuple` | Create a tuple of references for forwarding |
| `std::make_pair` (move-aware) | Construct a pair with move semantics support |
| `std::piecewise_construct` | Tag for piecewise construction of pairs |
| `std::type_index` | Hashable wrapper for `std::type_info` |
| `std::to_string` | Convert numeric values to `std::string` |
| `std::stoi` / `std::stol` / `std::stoll` | Convert strings to integer types |
| `std::stof` / `std::stod` / `std::stold` | Convert strings to floating-point types |

<details>
<summary><b>Random Number Generation</b> (30)</summary>

| Component | Description |
|:----------|:------------|
| `std::random_device` | Non-deterministic random number source |
| `std::mt19937` / `std::mt19937_64` | Mersenne Twister engines (32/64-bit) |
| `std::linear_congruential_engine` | LCG-based pseudo-random engine |
| `std::mersenne_twister_engine` | Configurable Mersenne Twister engine |
| `std::subtract_with_carry_engine` | Lagged Fibonacci pseudo-random engine |
| `std::discard_block_engine` | Engine adaptor that discards output blocks |
| `std::independent_bits_engine` | Engine adaptor for specific bit widths |
| `std::shuffle_order_engine` | Engine adaptor that shuffles output |
| `std::uniform_int_distribution` | Uniform integers in [a, b] |
| `std::uniform_real_distribution` | Uniform reals in [a, b) |
| `std::normal_distribution` | Gaussian (bell curve) distribution |
| `std::bernoulli_distribution` | Boolean distribution with probability p |
| `std::binomial_distribution` | Number of successes in N trials |
| `std::negative_binomial_distribution` | Trials until K successes |
| `std::geometric_distribution` | Trials until first success |
| `std::poisson_distribution` | Events per fixed interval |
| `std::exponential_distribution` | Time between Poisson events |
| `std::gamma_distribution` | Generalized exponential distribution |
| `std::weibull_distribution` | Reliability / failure-time modeling |
| `std::extreme_value_distribution` | Gumbel distribution for extremes |
| `std::lognormal_distribution` | Log-normal distribution |
| `std::chi_squared_distribution` | Chi-squared goodness-of-fit distribution |
| `std::cauchy_distribution` | Cauchy (Lorentz) distribution |
| `std::fisher_f_distribution` | F-distribution for variance ratio tests |
| `std::student_t_distribution` | Student's t-distribution for small samples |
| `std::discrete_distribution` | Custom discrete probability distribution |
| `std::piecewise_constant_distribution` | Piecewise constant probability density |
| `std::piecewise_linear_distribution` | Piecewise linear probability density |
| `std::seed_seq` | Seed sequence for engine initialization |

</details>

<details>
<summary><b>Regular Expressions</b> (14)</summary>

| Component | Description |
|:----------|:------------|
| `std::regex` | Compiled regular expression pattern |
| `std::regex_match` | Check if entire string matches a pattern |
| `std::regex_search` | Search for a pattern within a string |
| `std::regex_replace` | Replace pattern matches in a string |
| `std::regex_iterator` | Iterate over all matches in a string |
| `std::regex_token_iterator` | Iterate over sub-matches or non-matching parts |
| `std::smatch` / `std::cmatch` | Match results for `std::string` / C-strings |
| `std::wsmatch` / `std::wcmatch` | Match results for wide strings |
| `std::ssub_match` / `std::csub_match` | Sub-match for `std::string` / C-strings |
| `std::wssub_match` / `std::wcsub_match` | Sub-match for wide strings |
| `std::regex_error` | Exception for regex compilation errors |

</details>

<details>
<summary><b>Chrono Library</b> (11)</summary>

| Component | Description |
|:----------|:------------|
| `std::chrono::duration` | Represent a time interval with compile-time units |
| `std::chrono::time_point` | A point in time relative to a clock's epoch |
| `std::chrono::system_clock` | Wall-clock time tied to the system clock |
| `std::chrono::steady_clock` | Monotonic clock that never adjusts backward |
| `std::chrono::high_resolution_clock` | Highest-resolution available clock |
| `std::chrono::nanoseconds` | Duration in nanoseconds |
| `std::chrono::microseconds` | Duration in microseconds |
| `std::chrono::milliseconds` | Duration in milliseconds |
| `std::chrono::seconds` | Duration in seconds |
| `std::chrono::minutes` | Duration in minutes |
| `std::chrono::hours` | Duration in hours |

</details>

<details>
<summary><b>Ratio Library</b> (16)</summary>

| Component | Description |
|:----------|:------------|
| `std::ratio` | Compile-time rational number |
| `std::ratio_add` / `ratio_subtract` | Compile-time rational addition/subtraction |
| `std::ratio_multiply` / `ratio_divide` | Compile-time rational multiplication/division |
| `std::ratio_equal` / `ratio_not_equal` | Compile-time rational equality comparison |
| `std::ratio_less` / `ratio_less_equal` | Compile-time rational less-than comparison |
| `std::ratio_greater` / `ratio_greater_equal` | Compile-time rational greater-than comparison |
| SI prefixes (`std::atto` through `std::exa`) | Standard SI ratio typedefs |

</details>

---

## C++14 — Modern C++ Refined

> **10 core language features · 13 STL additions** | [Core Language](C++14/core_language.md) · [STL](C++14/stl_concepts.md)

A refinement release that polished C++11's rough edges. Relaxed `constexpr`, added generic lambdas, and introduced `std::make_unique`.

### Core Language

| Concept | Description |
|:--------|:------------|
| Generic lambda expressions | Lambdas with `auto` parameters for polymorphic calls |
| Lambda capture initializers | Initialize new variables directly in the capture clause |
| Return type deduction | Compiler deduces function return type from `return` statements |
| `decltype(auto)` | Deduce type preserving references and cv-qualifiers |
| Variable templates | Templates that define a family of variables |
| Binary literals | Write integers in binary with `0b` prefix |
| Digit separators | Use `'` to visually group digits in numeric literals |
| Relaxed `constexpr` | Allow loops, branches, and local variables in `constexpr` |
| `[[deprecated]]` attribute | Mark entities as deprecated with optional message |
| Aggregate member initialization relaxation | More flexible rules for aggregate initialization |

### STL

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::make_unique` | Safely construct a `unique_ptr` without `new` |
| `std::quoted` | I/O manipulator for quoted string round-tripping |
| `std::exchange` | Replace a value and return the old one |
| `std::integer_sequence` / `std::index_sequence` | Compile-time integer parameter packs |
| `std::get<Type>()` for tuples | Access tuple element by type instead of index |

#### Container Improvements

| Component | Description |
|:----------|:------------|
| Heterogeneous lookup | Look up in ordered containers without constructing a key |
| Transparent operator functors (`std::less<>`) | Comparators that accept any compatible types |

#### Type Traits

| Trait | Description |
|:------|:------------|
| `std::is_final` | Check if a class is marked `final` |

#### Threading

| Component | Description |
|:----------|:------------|
| `std::shared_timed_mutex` | Shared mutex with timed locking support |
| `std::shared_lock` | RAII lock for shared (reader) ownership |

---

## C++17 — Practical Modern C++

> **19 core language features · 78 STL additions** | [Core Language](C++17/core_language.md) · [STL](C++17/stl_concepts.md)

Brought major quality-of-life improvements: structured bindings, `if constexpr`, `std::optional`/`variant`/`any`, `std::filesystem`, and parallel algorithms.

### Core Language

| Concept | Description |
|:--------|:------------|
| Structured bindings | Decompose aggregates into named variables (`auto [a,b] = ...`) |
| `if constexpr` | Compile-time branch elimination in templates |
| Init-statements for `if`/`switch` | Declare variables in `if`/`switch` initializer |
| Inline variables | Define variables in headers without ODR violations |
| Fold expressions | Expand parameter packs with binary operators |
| Template argument deduction for class templates | Deduce class template arguments from constructor args |
| CTAD (Class template argument deduction) | Deduction guides for user-defined class templates |
| Nested namespace definitions | `namespace A::B::C { }` instead of nested braces |
| `__has_include` | Preprocessor check for header availability |
| `[[nodiscard]]` | Warn if return value is discarded |
| `[[maybe_unused]]` | Suppress unused-variable/parameter warnings |
| `[[fallthrough]]` | Mark intentional switch case fall-through |
| Guaranteed copy elision | Mandatory RVO for prvalue initialization |
| `std::launder` | Access an object at a reused storage location |
| `constexpr` lambda expressions | Lambdas usable in constant expressions |
| Hexadecimal floating-point literals | Write floating-point values in hex (`0x1.2p3`) |
| Using-declaration for parameter packs | Expand pack into a using-declaration list |
| Aggregate initialization with base classes | Aggregate-init derived classes with base subobjects |
| Non-type template parameters `auto` | Deduce non-type template parameter type automatically |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::string_view` | Non-owning lightweight view over a string |
| `std::optional` | Value-or-nothing container (no heap allocation) |
| `std::variant` | Type-safe discriminated union |
| `std::any` | Type-safe container for any single value |

<details>
<summary><b>Filesystem Library</b> (28)</summary>

| Component | Description |
|:----------|:------------|
| `std::filesystem::path` | Platform-independent file path manipulation |
| `std::filesystem::directory_entry` | Represents a directory entry with cached attributes |
| `std::filesystem::directory_iterator` | Iterate over entries in a directory |
| `std::filesystem::recursive_directory_iterator` | Recursively iterate directory trees |
| `std::filesystem::file_status` | File type and permissions information |
| `std::filesystem::space_info` | Filesystem capacity, free, and available space |
| `std::filesystem::file_type` | Enumeration of file types |
| `std::filesystem::perms` | File permission bits |
| `std::filesystem::copy_options` | Options controlling copy behavior |
| `std::filesystem::directory_options` | Options for directory iteration |
| `std::filesystem::create_directory` / `create_directories` | Create one or more directories |
| `std::filesystem::copy` / `copy_file` | Copy files or directories |
| `std::filesystem::remove` / `remove_all` | Delete files or directory trees |
| `std::filesystem::rename` | Move or rename a file/directory |
| `std::filesystem::resize_file` | Truncate or extend a file |
| `std::filesystem::space` | Query filesystem space information |
| `std::filesystem::last_write_time` | Get/set file modification time |
| `std::filesystem::permissions` | Modify file permissions |
| `std::filesystem::current_path` | Get/set current working directory |
| `std::filesystem::temp_directory_path` | Get the system temporary directory |
| `std::filesystem::exists` | Check if a path exists |
| `std::filesystem::is_directory` | Check if path is a directory |
| `std::filesystem::is_regular_file` | Check if path is a regular file |
| `std::filesystem::is_symlink` | Check if path is a symbolic link |
| `std::filesystem::file_size` | Get file size in bytes |
| `std::filesystem::hard_link_count` | Count hard links to a file |

</details>

<details>
<summary><b>Algorithms</b> (9)</summary>

| Algorithm | Purpose |
|:----------|:--------|
| `std::sample` | Randomly sample N elements from a range |
| `std::for_each_n` | Apply function to the first N elements |
| `std::reduce` | Generalized parallel-friendly accumulate |
| `std::transform_reduce` | Fused transform and reduce (parallel inner product) |
| `std::inclusive_scan` | Running sum including current element |
| `std::exclusive_scan` | Running sum excluding current element |
| `std::transform_inclusive_scan` | Fused transform + inclusive scan |
| `std::transform_exclusive_scan` | Fused transform + exclusive scan |
| Parallel algorithms (`seq`, `par`, `par_unseq`) | Execute standard algorithms in parallel |

</details>

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::byte` | Type-safe byte representation (not an integer) |
| `std::apply` | Call a function with a tuple as arguments |
| `std::invoke` | Uniformly call any callable (function, member, functor) |
| `std::is_invocable` / `std::is_invocable_r` | Check if a callable can be invoked with given args |
| `std::invoke_result` | Determine return type of a callable invocation |
| `std::is_swappable` / `std::is_nothrow_swappable` | Check if types support swap |
| `std::void_t` | SFINAE helper that maps any types to `void` |
| `std::bool_constant` | Alias for `integral_constant<bool, V>` |
| `std::conjunction` / `std::disjunction` / `std::negation` | Compile-time logical operations on type traits |
| `std::clamp` | Constrain a value within a min/max range |
| `std::from_chars` / `std::to_chars` | Fast locale-independent number parsing/formatting |
| `std::not_fn` | Negate a predicate callable |
| `std::gcd` / `std::lcm` | Greatest common divisor / least common multiple |
| `std::as_const` | Obtain a const reference to an object |
| `std::make_from_tuple` | Construct an object from a tuple of arguments |
| `std::has_unique_object_representations` | Check if type has unique bit representation |
| `std::is_aggregate` | Check if type is an aggregate |
| `std::hardware_destructive_interference_size` | Minimum offset to avoid false sharing |
| `std::hardware_constructive_interference_size` | Maximum size for true sharing |

#### Polymorphic Memory Resources

| Component | Description |
|:----------|:------------|
| `std::pmr::memory_resource` | Abstract base for custom memory allocation |
| `std::pmr::polymorphic_allocator` | Allocator that dispatches to a `memory_resource` |
| `std::pmr::monotonic_buffer_resource` | Fast bump allocator, no individual deallocation |
| `std::pmr::unsynchronized_pool_resource` | Pool allocator (single-threaded) |
| `std::pmr::synchronized_pool_resource` | Pool allocator (thread-safe) |

#### Container Improvements

| Component | Description |
|:----------|:------------|
| `std::map` `try_emplace` / `insert_or_assign` | Insert-if-absent or update-if-present in one call |
| `std::unordered_map` `try_emplace` / `insert_or_assign` | Same for unordered maps |
| `std::string_view` `starts_with` / `ends_with` | Check string prefix/suffix |
| Node handle API (`extract`, `insert`) | Move elements between compatible containers |

#### Threading

| Component | Description |
|:----------|:------------|
| `std::shared_mutex` | Shared (reader-writer) mutex without timed operations |
| `std::scoped_lock` | RAII lock for multiple mutexes with deadlock avoidance |

---

## C++20 — The Big Four

> **39 core language features · 245 STL additions** | [Core Language](C++20/core_language.md) · [STL](C++20/stl_concepts.md)

The largest standard since C++11. Introduced the "Big Four": **Concepts**, **Ranges**, **Coroutines**, and **Modules** — plus `std::format`, the spaceship operator, and major threading additions.

### Core Language

| Concept | Description |
|:--------|:------------|
| Concepts | Named compile-time predicates constraining template arguments |
| Constraints and requires clauses | Express requirements on template parameters |
| Constrained templates | Templates restricted to types satisfying a concept |
| Abbreviated function templates | `void f(auto x)` shorthand for simple templates |
| Three-way comparison (`<=>`) | Single operator returning ordering of two values |
| `std::strong_ordering` | Three-way result for types with unique equivalence |
| `std::weak_ordering` | Three-way result where equivalent values may differ |
| `std::partial_ordering` | Three-way result that allows incomparable values |
| Designated initializers | Initialize aggregate members by name (`{.x=1, .y=2}`) |
| `using enum` | Import all enumerators of a scoped enum into scope |
| `char8_t` | Distinct type for UTF-8 encoded characters |
| `constinit` | Ensure a variable is initialized at compile time |
| Lambda: `consteval` call operator | Lambdas as immediate (consteval) functions |
| Lambda: capture `[*this]` by value | Capture the current object by copy |
| Template lambdas | Lambdas with explicit template parameter lists |
| `constexpr` virtual functions | Virtual functions callable at compile time |
| `constexpr` dynamic allocation | `new`/`delete` allowed in constant expressions |
| `constexpr std::string` | `std::string` usable at compile time |
| `constexpr std::vector` | `std::vector` usable at compile time |
| Immediate functions (`consteval`) | Functions that must be evaluated at compile time |
| Constant evaluation for NTTPs | Non-type template parameters from constant evaluation |
| `std::is_constant_evaluated` | Detect if code is running at compile time |
| Modules | Replace headers with compiled, encapsulated module units |
| Import/export declarations | `import`/`export` syntax for module interfaces |
| Coroutines | Suspendable/resumable functions for async and generators |
| `co_await` | Suspend a coroutine until an awaitable completes |
| `co_yield` | Produce a value and suspend a generator coroutine |
| `co_return` | Return a final value and end a coroutine |
| `std::source_location` | Compile-time capture of file, line, and function name |
| `std::endian` | Query the platform's byte order at compile time |
| `[[likely]]` / `[[unlikely]]` | Hint the compiler about branch prediction |
| `[[no_unique_address]]` | Allow empty member to share storage with neighbors |
| Conditional `explicit` (`explicit(bool)`) | Make a constructor conditionally explicit |
| Non-type template parameters of class type | Use class objects as template arguments |
| Destroying delete | Customize destruction inside `operator delete` |
| Feature test macros | Preprocessor macros to detect supported features |
| Aggregate initialization improvements | Parenthesized initialization of aggregates |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::span` | Non-owning view over a contiguous sequence |

#### Concepts Library

| Concept | Description |
|:--------|:------------|
| `std::same_as` | Two types are identical |
| `std::derived_from` | One type publicly derives from another |
| `std::convertible_to` | Implicit and explicit conversion exists |
| `std::integral` | Type is an integer type |
| `std::floating_point` | Type is a floating-point type |
| `std::signed_integral` / `std::unsigned_integral` | Signed/unsigned integer type |
| `std::common_reference_with` | Two types share a common reference type |
| `std::common_with` | Two types share a common type |
| `std::assignable_from` | One type is assignable from another |
| `std::swappable` | Type supports swap |
| `std::destructible` | Type has a valid destructor |
| `std::constructible_from` | Type is constructible from given args |
| `std::default_initializable` | Type supports default construction |
| `std::move_constructible` | Type supports move construction |
| `std::copy_constructible` | Type supports copy construction |
| `std::equality_comparable` | Type supports `==` comparison |
| `std::totally_ordered` | Type supports all relational operators |
| `std::regular` | Copyable + default-constructible + equality-comparable |
| `std::semiregular` | Copyable + default-constructible |
| `std::invocable` | Type can be called with given arguments |
| `std::predicate` | Invocable returning a boolean |
| `std::relation` | Binary predicate defining a relation |

<details>
<summary><b>Ranges Library</b> (19)</summary>

| Component | Description |
|:----------|:------------|
| `std::ranges::range` | Type providing `begin()` and `end()` |
| `std::ranges::input_range` | Range for single-pass input iteration |
| `std::ranges::output_range` | Range for output iteration |
| `std::ranges::forward_range` | Range for multi-pass forward iteration |
| `std::ranges::bidirectional_range` | Range for bidirectional iteration |
| `std::ranges::random_access_range` | Range for constant-time jumps |
| `std::ranges::contiguous_range` | Range with contiguous storage |
| `std::ranges::sized_range` | Range with O(1) size query |
| `std::ranges::view` | Lightweight, non-owning range with O(1) copy |
| `std::ranges::viewable_range` | Range convertible to a view |
| `std::ranges::borrowed_range` | Range safe to use after the source is destroyed |
| `std::ranges::common_range` | Range where begin/end return the same type |
| `std::ranges::range_value_t` / `range_reference_t` | Type aliases for range element types |
| `std::ranges::range_difference_t` / `range_size_t` | Type aliases for range distance/size |
| `std::ranges::begin` / `end` | Customization point objects for range access |
| `std::ranges::cbegin` / `cend` | Const range access |
| `std::ranges::rbegin` / `rend` | Reverse range access |
| `std::ranges::size` / `ssize` | Range size queries |
| `std::ranges::empty` / `data` / `cdata` | Range emptiness and data pointer queries |

</details>

<details>
<summary><b>Range Views</b> (19)</summary>

| View | Description |
|:-----|:------------|
| `all_view` / `ref_view` / `owning_view` | Wrap a range into a view |
| `filter_view` | Lazily filter elements by a predicate |
| `transform_view` | Lazily apply a function to each element |
| `take_view` | Take the first N elements |
| `take_while_view` | Take elements while predicate holds |
| `drop_view` | Skip the first N elements |
| `drop_while_view` | Skip elements while predicate holds |
| `join_view` | Flatten nested ranges into one |
| `split_view` | Split a range by a delimiter |
| `counted_view` | View of N elements from an iterator |
| `common_view` | Adapt to common begin/end types |
| `reverse_view` | View a range in reverse |
| `elements_view` | Project the Nth element of tuple-like elements |
| `keys_view` / `values_view` | Project keys/values from pair-like ranges |
| `iota_view` | Generate an incrementing sequence |
| `empty_view` | Empty range of a given type |
| `single_view` | Range containing exactly one element |

</details>

<details>
<summary><b>Range Adaptors</b> (17)</summary>

| Adaptor (`std::views::`) | Description |
|:--------------------------|:------------|
| `all` | View the entire range |
| `filter` | Pipe-syntax filtering |
| `transform` | Pipe-syntax transformation |
| `take` / `take_while` | Pipe-syntax take operations |
| `drop` / `drop_while` | Pipe-syntax drop operations |
| `join` | Pipe-syntax flattening |
| `split` | Pipe-syntax splitting |
| `common` | Pipe-syntax common range conversion |
| `reverse` | Pipe-syntax reverse |
| `elements` / `keys` / `values` | Pipe-syntax tuple projection |
| `iota` | Pipe-syntax sequence generation |
| `empty` / `single` | Pipe-syntax range factories |

</details>

<details>
<summary><b>Range Algorithms</b> (72)</summary>

All classic algorithms reimplemented for ranges with projection support:

| Algorithm | Purpose |
|:----------|:--------|
| `std::ranges::for_each` / `for_each_n` | Apply function to elements |
| `std::ranges::find` / `find_if` / `find_if_not` | Find elements by value or predicate |
| `std::ranges::find_end` / `find_first_of` | Find subsequences or candidates |
| `std::ranges::adjacent_find` | Find adjacent equal elements |
| `std::ranges::count` / `count_if` | Count elements |
| `std::ranges::mismatch` / `equal` | Compare ranges |
| `std::ranges::search` / `search_n` | Search for patterns |
| `std::ranges::copy` / `copy_if` / `copy_n` / `copy_backward` | Copy elements |
| `std::ranges::move` / `move_backward` | Move elements |
| `std::ranges::fill` / `fill_n` | Fill with values |
| `std::ranges::transform` | Transform elements |
| `std::ranges::generate` / `generate_n` | Generate values |
| `std::ranges::remove` / `remove_if` | Remove elements |
| `std::ranges::replace` / `replace_if` | Replace elements |
| `std::ranges::swap_ranges` | Swap range contents |
| `std::ranges::reverse` / `reverse_copy` | Reverse elements |
| `std::ranges::rotate` / `rotate_copy` | Rotate elements |
| `std::ranges::unique` / `unique_copy` | Remove consecutive duplicates |
| `std::ranges::partition` / `stable_partition` | Partition by predicate |
| `std::ranges::sort` / `stable_sort` | Sort elements |
| `std::ranges::partial_sort` / `partial_sort_copy` | Partial sorting |
| `std::ranges::nth_element` | Place Nth element correctly |
| `std::ranges::merge` / `inplace_merge` | Merge sorted ranges |
| `std::ranges::includes` | Sorted range inclusion |
| `std::ranges::set_union` / `set_intersection` | Set operations |
| `std::ranges::set_difference` / `set_symmetric_difference` | Set difference operations |
| `std::ranges::push_heap` / `pop_heap` / `make_heap` / `sort_heap` | Heap operations |
| `std::ranges::min` / `max` / `minmax` | Min/max of values |
| `std::ranges::min_element` / `max_element` / `minmax_element` | Min/max of ranges |
| `std::ranges::lexicographical_compare` | Lexicographic comparison |
| `std::ranges::next_permutation` / `prev_permutation` | Permutation generation |
| `std::ranges::all_of` / `any_of` / `none_of` | Predicate quantifiers |
| `std::ranges::is_sorted` / `is_sorted_until` | Sort verification |
| `std::ranges::is_permutation` | Permutation check |
| `std::ranges::is_heap` / `is_heap_until` | Heap verification |

</details>

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::bit_cast` | Reinterpret object representation as a different type |
| `std::starts_with` / `std::ends_with` | Check string/container prefix or suffix |
| `std::contains` | Check if a container holds a value |
| `std::erase` / `std::erase_if` | Uniform container erasure |
| `std::format` | Python-style type-safe string formatting |
| `std::format_to` / `format_to_n` / `formatted_size` | Format into iterators or compute size |
| `std::vformat` / `std::make_format_args` | Runtime format string support |
| `std::syncbuf` / `std::osyncstream` | Synchronized output preventing interleaved writes |
| `std::bind_front` | Bind leading arguments to a callable |
| `std::identity` | Function object that returns its argument unchanged |
| `std::unwrap_reference` / `std::unwrap_ref_decay` | Unwrap reference wrappers |
| `std::midpoint` | Compute midpoint without overflow |
| `std::lerp` | Linear interpolation between two values |
| `std::to_address` | Obtain raw pointer from a pointer-like type |
| `std::assume_aligned` | Assert pointer alignment for optimization |
| `std::make_shared_for_overwrite` | Allocate shared_ptr with default initialization |
| `std::make_unique_for_overwrite` | Allocate unique_ptr with default initialization |

<details>
<summary><b>Mathematical Constants</b> (12)</summary>

| Constant | Value |
|:---------|:------|
| `std::numbers::pi` | 3.14159... (ratio of circumference to diameter) |
| `std::numbers::e` | 2.71828... (Euler's number) |
| `std::numbers::sqrt2` | 1.41421... (square root of 2) |
| `std::numbers::sqrt3` | 1.73205... (square root of 3) |
| `std::numbers::ln2` | 0.69314... (natural log of 2) |
| `std::numbers::ln10` | 2.30258... (natural log of 10) |
| `std::numbers::log2e` | 1.44269... (log base 2 of e) |
| `std::numbers::log10e` | 0.43429... (log base 10 of e) |
| `std::numbers::phi` | 1.61803... (golden ratio) |
| `std::numbers::inv_pi` | 0.31830... (1/pi) |
| `std::numbers::inv_sqrtpi` | 0.56418... (1/sqrt(pi)) |
| `std::numbers::egamma` | 0.57721... (Euler-Mascheroni constant) |

</details>

<details>
<summary><b>Chrono Extensions</b> (25)</summary>

| Component | Description |
|:----------|:------------|
| `std::chrono::day` | Calendar day (1-31) |
| `std::chrono::month` | Calendar month (January-December) |
| `std::chrono::year` | Calendar year |
| `std::chrono::weekday` | Day of the week |
| `std::chrono::weekday_indexed` | Nth weekday in a month (e.g., 2nd Tuesday) |
| `std::chrono::weekday_last` | Last weekday in a month |
| `std::chrono::month_day` / `month_day_last` | Month + day combinations |
| `std::chrono::month_weekday` / `month_weekday_last` | Month + weekday combinations |
| `std::chrono::year_month` | Year + month combination |
| `std::chrono::year_month_day` | Full calendar date |
| `std::chrono::year_month_day_last` | Last day of a year/month |
| `std::chrono::year_month_weekday` | Year + month + weekday |
| `std::chrono::year_month_weekday_last` | Year + month + last weekday |
| `std::chrono::local_time` | Local time representation |
| `std::chrono::zoned_time` | Time point with associated time zone |
| `std::chrono::time_zone` | IANA time zone representation |
| `std::chrono::sys_time` | System clock time point alias |
| `std::chrono::utc_clock` | UTC clock accounting for leap seconds |
| `std::chrono::tai_clock` | International Atomic Time clock |
| `std::chrono::gps_clock` | GPS time clock |
| `std::chrono::file_clock` | Clock for file timestamps |
| `std::chrono::local_days` / `local_seconds` | Local time convenience aliases |

</details>

<details>
<summary><b>Bit Operations</b> (11)</summary>

| Function | Description |
|:---------|:------------|
| `std::bit_ceil` | Smallest power of two not less than value |
| `std::bit_floor` | Largest power of two not greater than value |
| `std::bit_width` | Number of bits needed to represent a value |
| `std::countl_zero` | Count leading zero bits |
| `std::countl_one` | Count leading one bits |
| `std::countr_zero` | Count trailing zero bits |
| `std::countr_one` | Count trailing one bits |
| `std::has_single_bit` | Check if value is a power of two |
| `std::popcount` | Count the number of set bits |
| `std::rotl` | Bitwise rotate left |
| `std::rotr` | Bitwise rotate right |

</details>

#### Threading

| Component | Description |
|:----------|:------------|
| `std::jthread` | Thread with automatic joining and stop-token support |
| `std::stop_token` | Query whether a stop has been requested |
| `std::stop_source` | Request a cooperative stop on associated threads |
| `std::latch` | Single-use thread barrier that counts down |
| `std::barrier` | Reusable thread synchronization barrier |
| `std::semaphore` / `std::counting_semaphore` | Semaphore for limiting concurrent access |
| `std::atomic_ref` | Atomic operations on a non-atomic object |
| `std::atomic_flag` enhancements | Additional atomic flag operations |
| `std::atomic_wait` / `notify_one` / `notify_all` | Efficient atomic waiting and notification |

---

## C++23 — Completing Modern C++

> **13 core language features · 76 STL additions** | [Core Language](C++23/core_language.md) · [STL](C++23/stl_concepts.md)

Polished C++20's additions and filled critical gaps: `std::expected`, `std::print`, deducing `this`, `std::flat_map`, and many new range views.

### Core Language

| Concept | Description |
|:--------|:------------|
| Deducing `this` | Explicit object parameter enables value-category overloading |
| Explicit `this` parameter in lambdas | Lambdas can take an explicit object parameter |
| `[[assume]]` attribute | Assert a condition for optimizer without runtime check |
| Multidimensional subscript operator | `operator[]` can accept multiple arguments |
| Static `operator()` | Call operator can be declared `static` |
| Static `operator[]` | Subscript operator can be declared `static` |
| `if consteval` | Branch on whether code is being constant-evaluated |
| `size_t` literal suffix (`uz`/`zu`) | Write `std::size_t` literals directly |
| `#warning` directive | Issue a compiler warning from preprocessor |
| `#elifdef` / `#elifndef` directives | Shorthand for `#elif defined(...)` |
| `auto(x)` / `auto{x}` decay-copy | Explicitly decay-copy an expression |
| `constexpr` improvements | More operations allowed in constant expressions |
| Lambda trailing return type scope changes | Name lookup in lambda trailing return type fixed |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::flat_map` | Sorted key-value container backed by contiguous storage |
| `std::flat_set` | Sorted unique container backed by contiguous storage |
| `std::flat_multimap` | Flat map allowing duplicate keys |
| `std::flat_multiset` | Flat set allowing duplicate elements |
| `std::mdspan` | Multi-dimensional non-owning view over contiguous data |
| `std::generator` | Coroutine-based synchronous element generator |

<details>
<summary><b>Range Views</b> (14)</summary>

| View | Description |
|:-----|:------------|
| `zip_view` | Iterate over multiple ranges in lockstep |
| `zip_transform_view` | Zip ranges and apply a transformation |
| `adjacent_view` | Sliding window of N adjacent elements |
| `adjacent_transform_view` | Adjacent window with transformation |
| `chunk_view` | Split a range into fixed-size chunks |
| `chunk_by_view` | Split range where predicate changes |
| `slide_view` | Sliding window over consecutive elements |
| `stride_view` | Take every Nth element from a range |
| `cartesian_product_view` | Cartesian product of multiple ranges |
| `repeat_view` | Infinite or bounded repetition of a value |
| `join_with_view` | Flatten with a delimiter between ranges |
| `as_rvalue_view` | Cast all elements to rvalues |
| `as_const_view` | Cast all elements to const |
| `enumerate_view` | Pair each element with its index |

</details>

<details>
<summary><b>Range Adaptors</b> (14)</summary>

| Adaptor (`std::views::`) | Description |
|:--------------------------|:------------|
| `zip` / `zip_transform` | Pipe-syntax zip operations |
| `adjacent` / `adjacent_transform` | Pipe-syntax adjacent operations |
| `chunk` / `chunk_by` | Pipe-syntax chunking |
| `slide` | Pipe-syntax sliding window |
| `stride` | Pipe-syntax striding |
| `cartesian_product` | Pipe-syntax cartesian product |
| `repeat` | Pipe-syntax repetition |
| `join_with` | Pipe-syntax join with delimiter |
| `as_rvalue` / `as_const` | Pipe-syntax value category conversion |
| `enumerate` | Pipe-syntax enumeration |

</details>

<details>
<summary><b>Range Algorithms</b> (11)</summary>

| Algorithm | Purpose |
|:----------|:--------|
| `std::ranges::fold_left` | Left fold (like `accumulate` for ranges) |
| `std::ranges::fold_right` | Right fold over a range |
| `std::ranges::fold_left_first` | Left fold using first element as initial value |
| `std::ranges::fold_right_last` | Right fold using last element as initial value |
| `std::ranges::find_last` / `find_last_if` / `find_last_if_not` | Find from the end of a range |
| `std::ranges::contains` | Check if a range contains a value |
| `std::ranges::starts_with` / `ends_with` | Check range prefix/suffix |
| `std::ranges::to` | Materialize a range into a container |

</details>

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::expected` | Value-or-error return type (alternative to exceptions) |
| `std::print` / `std::println` | Formatted output without streams overhead |
| `std::stacktrace` / `std::stacktrace_entry` / `std::basic_stacktrace` | Capture the current call stack at runtime |
| `std::to_underlying` | Convert enum to its underlying integer type |
| `std::byteswap` | Reverse byte order of an integer value |
| `std::unreachable` | Hint that a code path is never reached |
| `std::invoke_r` | Invoke a callable and convert result to a type |
| `std::forward_like` | Forward with the value category of another type |
| `std::move_only_function` | Type-erased callable that is move-only |
| `std::out_ptr` / `std::inout_ptr` | Adaptors for C APIs that output pointers |
| `std::spanstream` | Stream backed by a `std::span` buffer |
| `std::basic_string::contains` / `std::basic_string_view::contains` | Check if a string contains a substring |

<details>
<summary><b>Container Improvements</b> (7)</summary>

| Improvement | Description |
|:------------|:------------|
| `std::string` constexpr support | String operations usable at compile time |
| `std::vector` constexpr support | Vector operations usable at compile time |
| `std::optional` monadic operations | `and_then`, `transform`, `or_else` chaining |
| `std::variant` monadic operations | Monadic-style variant processing |
| `std::expected` monadic operations | `and_then`, `transform`, `or_else` chaining |
| `std::span` subspan / `as_bytes` / `as_writable_bytes` | Span slicing and byte-level access |
| `std::reference_wrapper` improvements | Enhanced reference wrapper functionality |

</details>

<details>
<summary><b>Chrono Improvements</b> (5)</summary>

| Component | Description |
|:----------|:------------|
| `std::chrono::parse` | Parse a time point from a string |
| `std::chrono::format` | Format a time point to a string |
| `std::chrono::zoned_traits` | Customization point for zoned_time behavior |
| `std::chrono::choose` | Disambiguation policy for ambiguous local times |
| `std::chrono::leap_second` | Leap second information entry |

</details>

#### Modules

| Component | Description |
|:----------|:------------|
| `import std` | Import the entire standard library as a single module |

---

## C++26 — The Next Frontier

> **11 core language features · 33 STL additions** | [Core Language](C++26/core_language.md) · [STL](C++26/stl_concepts.md)

The upcoming standard bringing contracts, static reflection, SIMD support, and the senders/receivers execution framework.

### Core Language

| Concept | Description |
|:--------|:------------|
| Contracts (preconditions, postconditions, assertions) | Formalized function contract specifications |
| Reflection (`P2996`, static reflection) | Inspect types, members, and attributes at compile time |
| `std::meta` | Compile-time metaprogramming primitives for reflection |
| Pack indexing | Access the Nth element of a parameter pack directly |
| Placeholder variables (`_`) | Discard unused bindings with multiple `_` declarations |
| Structured bindings as conditions | Use structured bindings directly in `if`/`while` |
| `constexpr` cast from `void*` | Allow `static_cast` from `void*` in constant expressions |
| Erroneous behavior for uninitialized reads | Formally define behavior of reading uninitialized variables |
| User-generated `static_assert` messages | `static_assert` with computed string messages |
| Extended floating-point types (`float16_t`, etc.) | Standardized fixed-width floating-point types |
| Pattern matching (proposed) | Declarative value inspection and decomposition |

### STL

#### Containers

| Container | Description |
|:----------|:------------|
| `std::inplace_vector` | Fixed-capacity vector with no heap allocation |
| `std::mdspan` improvements | Enhanced dynamic extent support |
| `std::flat_map` / `std::flat_set` improvements | Performance and API refinements |

#### Utilities

| Utility | Description |
|:--------|:------------|
| `std::text_encoding` | Query and represent character encoding information |
| `std::format` improvements | Range formatting and additional format specifiers |
| `std::print` improvements | Enhanced formatted output |
| `std::copyable_function` | Copyable type-erased callable wrapper |
| `std::function_ref` | Non-owning lightweight callable reference |

#### Saturation Arithmetic

| Function | Description |
|:---------|:------------|
| `std::add_sat` / `std::sub_sat` | Addition/subtraction clamped on overflow |
| `std::mul_sat` / `std::div_sat` | Multiplication/division clamped on overflow |
| `std::saturate_cast` | Numeric cast that saturates at target type limits |

#### Compile-Time Utilities

| Component | Description |
|:----------|:------------|
| `std::is_within_lifetime` | Check if an object is within its lifetime at compile time |

#### Container Improvements

| Component | Description |
|:----------|:------------|
| `std::string_view` improvements | Enhanced string view functionality |
| `std::u8string_view` | UTF-8 string view type |
| `std::u8string` improvements | Enhanced UTF-8 string functionality |

#### SIMD Support

| Component | Description |
|:----------|:------------|
| `std::simd` | Portable data-parallel vector type |
| `std::simd_mask` | Boolean mask for conditional SIMD operations |
| `std::simd::reduce` | Reduce SIMD vector to a scalar value |

<details>
<summary><b>Execution Framework</b> (10)</summary>

| Component | Description |
|:----------|:------------|
| `std::execution` (senders/receivers) | Structured async programming framework |
| `std::execution::scheduler` | Abstract source of execution contexts |
| `std::execution::sender` | Describe an asynchronous operation |
| `std::execution::receiver` | Consume the result of a sender |
| `std::execution::then` | Chain a continuation after a sender completes |
| `std::execution::when_all` | Wait for multiple senders to complete |
| `std::execution::let_value` | Dynamically compose senders based on results |
| `std::execution::bulk` | Execute work in bulk (data parallelism) |
| `std::execution::split` | Share a sender's result with multiple consumers |
| `std::execution::ensure_started` | Eagerly start a sender's execution |

</details>

#### Threading

| Component | Description |
|:----------|:------------|
| `std::hazard_pointer` | Safe memory reclamation for lock-free data structures |
| `std::rcu` (reader-copy-update) | Efficient concurrent reads with deferred reclamation |

---

<div align="center">

*This index covers **968 concepts** across **8 C++ standards** (1998–2026).*
*For full explanations, real-world scenarios, and code examples — visit the per-standard documents linked in each section.*

**[Back to CodeNebula README](../README.md)**

</div>
