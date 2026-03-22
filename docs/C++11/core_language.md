# C++11 Core Language Concepts

This document covers new or evolved C++11 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++11/). Only additions or evolutions from C++98/C++03 are included.

## Rvalue References (C++11 Addition)
**Explanation**: References to temporary objects (`&&`), enabling move semantics for efficient resource transfer.  
**Real-World Scenario**: Optimize data transfer in a file copy operation by moving large buffers.  
**Snippet**:  
```cpp
void process(int&& rvalue) {}
```
**Example**: [rvalue_references.cpp](../examples/C++11/rvalue_references.cpp)

## Move Semantics (C++11 Addition)
**Explanation**: Transfers resources from temporary objects, avoiding copies, using rvalue references.  
**Real-World Scenario**: Move large data buffers in a network application to reduce overhead.  
**Snippet**:  
```cpp
std::vector<int> vec; vec = std::move(otherVec);
```
**Example**: [move_semantics.cpp](../examples/C++11/move_semantics.cpp)

## std::move (C++11 Addition)
**Explanation**: Converts an lvalue to an rvalue, enabling move semantics.  
**Real-World Scenario**: Transfer ownership of a resource in a resource manager.  
**Snippet**:  
```cpp
#include <utility> std::vector<int> vec = std::move(otherVec);
```
**Example**: [move.cpp](../examples/C++11/move.cpp)

## std::forward (C++11 Addition)
**Explanation**: Preserves value category (lvalue/rvalue) in template forwarding.  
**Real-World Scenario**: Write a generic wrapper function for a logging system.  
**Snippet**:  
```cpp
template<typename T> void forward(T&& arg) { func(std::forward<T>(arg)); }
```
**Example**: [forward.cpp](../examples/C++11/forward.cpp)

## Lambda Expressions (C++11 Addition)
**Explanation**: Anonymous functions for concise, inline logic, with capture lists for accessing variables.  
**Real-World Scenario**: Sort a list of players by score in a game using a custom comparator.  
**Snippet**:  
```cpp
auto lambda = [](int a, int b) { return a > b; };
```
**Example**: [lambda_expressions.cpp](../examples/C++11/lambda_expressions.cpp)

## Delegating Constructors (C++11 Addition)
**Explanation**: Constructors can call other constructors in the same class, reducing code duplication.  
**Real-World Scenario**: Initialize a player object with default values in a game.  
**Snippet**:  
```cpp
class Player { Player() : Player(100) {} Player(int health) {} };
```
**Example**: [delegating_constructors.cpp](../examples/C++11/delegating_constructors.cpp)

## Defaulted and Deleted Functions (C++11 Addition)
**Explanation**: Explicitly default or delete special member functions (e.g., copy constructor).  
**Real-World Scenario**: Prevent copying of a unique resource in a system.  
**Snippet**:  
```cpp
class Resource { Resource(const Resource&) = delete; };
```
**Example**: [defaulted_deleted_functions.cpp](../examples/C++11/defaulted_deleted_functions.cpp)

## Override Specifier (C++11 Addition)
**Explanation**: Ensures a function overrides a virtual function, improving code clarity.  
**Real-World Scenario**: Ensure correct overriding in a game’s enemy hierarchy.  
**Snippet**:  
```cpp
class Enemy { virtual void attack() {} }; class Boss : public Enemy { void attack() override {} };
```
**Example**: [override_specifier.cpp](../examples/C++11/override_specifier.cpp)

## Final Specifier (C++11 Addition)
**Explanation**: Prevents class inheritance or function overriding for safety.  
**Real-World Scenario**: Lock a critical class in a security system.  
**Snippet**:  
```cpp
class Secure final {};
```
**Example**: [final_specifier.cpp](../examples/C++11/final_specifier.cpp)

## Variadic Templates (C++11 Addition)
**Explanation**: Templates with a variable number of arguments for flexible generic programming.  
**Real-World Scenario**: Create a generic logger for multiple data types.  
**Snippet**:  
```cpp
template<typename... Args> void log(Args... args) {}
```
**Example**: [variadic_templates.cpp](../examples/C++11/variadic_templates.cpp)

## Template Aliases (C++11 Addition)
**Explanation**: Simplifies template types using `using` declarations.  
**Real-World Scenario**: Simplify complex container types in a data processor.  
**Snippet**:  
```cpp
template<typename T> using Vec = std::vector<T>;
```
**Example**: [template_aliases.cpp](../examples/C++11/template_aliases.cpp)

## noexcept Specifier (C++11 Addition)
**Explanation**: Specifies whether a function can throw exceptions, aiding optimization.  
**Real-World Scenario**: Optimize performance in a critical system by guaranteeing no exceptions.  
**Snippet**:  
```cpp
void safeFunc() noexcept {}
```
**Example**: [noexcept_specifier.cpp](../examples/C++11/noexcept_specifier.cpp)

## Inline Namespaces (C++11 Addition)
**Explanation**: Automatically includes namespace contents in parent scope for versioning.  
**Real-World Scenario**: Version library functions without explicit scoping.  
**Snippet**:  
```cpp
inline namespace V1 { void func() {} }
```
**Example**: [inline_namespaces.cpp](../examples/C++11/inline_namespaces.cpp)

## std::unique_ptr (C++11 Addition)
**Explanation**: Smart pointer with single ownership semantics, replacing `std::auto_ptr`.  
**Real-World Scenario**: Manage a unique resource in a system without leaks.  
**Snippet**:  
```cpp
#include <memory> std::unique_ptr<int> ptr = std::make_unique<int>(5);
```
**Example**: [unique_ptr.cpp](../examples/C++11/unique_ptr.cpp)

## std::shared_ptr (C++11 Addition)
**Explanation**: Smart pointer with shared ownership, tracking reference counts.  
**Real-World Scenario**: Share a resource across multiple game objects.  
**Snippet**:  
```cpp
#include <memory> std::shared_ptr<int> ptr = std::make_shared<int>(5);
```
**Example**: [shared_ptr.cpp](../examples/C++11/shared_ptr.cpp)

## std::weak_ptr (C++11 Addition)
**Explanation**: Non-owning reference to a `shared_ptr` resource, prevents circular references.  
**Real-World Scenario**: Break circular references in a resource manager.  
**Snippet**:  
```cpp
#include <memory> std::weak_ptr<int> wptr;
```
**Example**: [weak_ptr.cpp](../examples/C++11/weak_ptr.cpp)

## static_assert (C++11 Addition)
**Explanation**: Compile-time assertions for type or condition checking.  
**Real-World Scenario**: Ensure template types meet requirements in a library.  
**Snippet**:  
```cpp
static_assert(sizeof(int) == 4, "Int size must be 4 bytes");
```
**Example**: [static_assert.cpp](../examples/C++11/static_assert.cpp)

## Type Traits (C++11 Addition)
**Explanation**: Provides compile-time type information (e.g., `is_integral`).  
**Real-World Scenario**: Check if a type is integral in a generic algorithm.  
**Snippet**:  
```cpp
#include <type_traits> std::is_integral<int>::value;
```
**Example**: [type_traits.cpp](../examples/C++11/type_traits.cpp)

## auto (C++11 Addition)
**Explanation**: Automatically deduces variable types, simplifying declarations.  
**Real-World Scenario**: Simplify iterator declarations in a loop.  
**Snippet**:  
```cpp
auto x = 10; // int
```
**Example**: [auto.cpp](../examples/C++11/auto.cpp)

## decltype (C++11 Addition)
**Explanation**: Deduce type of an expression at compile time.  
**Real-World Scenario**: Define return types in generic functions.  
**Snippet**:  
```cpp
decltype(10 + 20.0) x; // double
```
**Example**: [decltype.cpp](../examples/C++11/decltype.cpp)

## Range-based For Loop (C++11 Addition)
**Explanation**: Simplified loop syntax for iterating containers.  
**Real-World Scenario**: Print all items in a shopping cart.  
**Snippet**:  
```cpp
for (int x : std::vector<int>{1, 2, 3}) {}
```
**Example**: [range_based_for.cpp](../examples/C++11/range_based_for.cpp)

## nullptr (C++11 Addition)
**Explanation**: Type-safe null pointer constant, replacing `NULL`.  
**Real-World Scenario**: Initialize pointers safely in a system.  
**Snippet**:  
```cpp
int* ptr = nullptr;
```
**Example**: [nullptr.cpp](../examples/C++11/nullptr.cpp)

## Uniform Initialization (C++11 Addition)
**Explanation**: Consistent initialization syntax using braces.  
**Real-World Scenario**: Initialize complex objects in a game.  
**Snippet**:  
```cpp
struct Point { int x, y; }; Point p{1, 2};
```
**Example**: [uniform_initialization.cpp](../examples/C++11/uniform_initialization.cpp)

## Initializer Lists (C++11 Addition)
**Explanation**: Initialize containers or objects with brace-enclosed lists.  
**Real-World Scenario**: Initialize a vector of scores in a game.  
**Snippet**:  
```cpp
#include <initializer_list> std::vector<int> vec{1, 2, 3};
```
**Example**: [initializer_lists.cpp](../examples/C++11/initializer_lists.cpp)

## constexpr (C++11 Addition)
**Explanation**: Evaluates expressions at compile time for performance.  
**Real-World Scenario**: Compute constants for physics calculations.  
**Snippet**:  
```cpp
constexpr int square(int x) { return x * x; }
```
**Example**: [constexpr.cpp](../examples/C++11/constexpr.cpp)

## enum class (C++11 Addition)
**Explanation**: Scoped enumerations with stronger type safety.  
**Real-World Scenario**: Define game states without name conflicts.  
**Snippet**:  
```cpp
enum class State { Idle, Running };
```
**Example**: [enum_class.cpp](../examples/C++11/enum_class.cpp)

## Attributes (C++11 Addition)
**Explanation**: Add metadata to code (e.g., `[[noreturn]]`).  
**Real-World Scenario**: Mark a function that never returns in a system.  
**Snippet**:  
```cpp
[[noreturn]] void exit() {}
```
**Example**: [attributes.cpp](../examples/C++11/attributes.cpp)

## alignas and alignof (C++11 Addition)
**Explanation**: Control and query alignment of variables for optimization.
**Real-World Scenario**: Optimize memory layout in a performance-critical app.
**Snippet**:
```cpp
alignas(16) int x; alignof(int);
```
**Example**: [alignment.cpp](../examples/C++11/alignment.cpp)

## Move Constructor (C++11 Addition)
**Explanation**: A constructor that transfers resources from a temporary object rather than copying them, enabling efficient object creation from rvalues.
**Real-World Scenario**: Construct a large image buffer by stealing the data from a temporary returned by a factory function, avoiding an expensive deep copy.
**Snippet**:
```cpp
class Buffer {
    int* data;
    size_t size;
public:
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
};
```
**Example**: [move_constructor.cpp](../examples/C++11/move_constructor.cpp)

## Move Assignment Operator (C++11 Addition)
**Explanation**: An assignment operator that transfers resources from a temporary object to an existing object, releasing the target's old resources and taking ownership of the source's resources.
**Real-World Scenario**: Reassign a network connection handler to a new connection by moving the socket data instead of duplicating it.
**Snippet**:
```cpp
class Connection {
    int* socket;
public:
    Connection& operator=(Connection&& other) noexcept {
        if (this != &other) {
            delete socket;
            socket = other.socket;
            other.socket = nullptr;
        }
        return *this;
    }
};
```
**Example**: [move_assignment.cpp](../examples/C++11/move_assignment.cpp)

## Perfect Forwarding (C++11 Addition)
**Explanation**: A technique using universal references and `std::forward` to pass arguments to another function while preserving their original value category (lvalue or rvalue). This is essential for writing generic wrapper functions.
**Real-World Scenario**: Build a factory function that constructs objects by forwarding constructor arguments exactly as the caller provided them.
**Snippet**:
```cpp
template<typename T, typename... Args>
std::unique_ptr<T> make(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```
**Example**: [perfect_forwarding.cpp](../examples/C++11/perfect_forwarding.cpp)

## In-class Member Initializers (NSDMI) (C++11 Addition)
**Explanation**: Allows non-static data members to be initialized directly at the point of declaration inside the class body, providing default values without requiring constructor initialization lists.
**Real-World Scenario**: Set sensible defaults for a configuration struct so that newly constructed objects are immediately usable.
**Snippet**:
```cpp
class Config {
    int timeout = 30;
    std::string host = "localhost";
    bool verbose = false;
};
```
**Example**: [nsdmi.cpp](../examples/C++11/nsdmi.cpp)

## Explicit Conversion Operators (C++11 Addition)
**Explanation**: The `explicit` keyword can now be applied to conversion operators, preventing implicit type conversions that could lead to subtle bugs while still allowing explicit casts.
**Real-World Scenario**: A smart handle class that converts to `bool` for null-checking without accidentally participating in arithmetic expressions.
**Snippet**:
```cpp
class Handle {
    int fd;
public:
    explicit operator bool() const { return fd >= 0; }
};
// if (handle) {} // OK: explicit bool in boolean context
// int x = handle; // Error: no implicit conversion
```
**Example**: [explicit_conversion.cpp](../examples/C++11/explicit_conversion.cpp)

## User-defined Literals (C++11 Addition)
**Explanation**: Allows defining custom suffixes for literals, enabling expressive, type-safe constants by overloading the `operator""` syntax.
**Real-World Scenario**: Define a `_km` suffix to create distance values with compile-time unit safety in a navigation system.
**Snippet**:
```cpp
constexpr long double operator"" _km(long double val) {
    return val * 1000.0L; // convert to meters
}
auto distance = 5.0_km; // 5000.0 meters
```
**Example**: [user_defined_literals.cpp](../examples/C++11/user_defined_literals.cpp)

## Raw String Literals (C++11 Addition)
**Explanation**: String literals prefixed with `R` that ignore escape sequences, making it easy to embed regex patterns, file paths, and multi-line text without excessive backslash escaping.
**Real-World Scenario**: Embed a complex regular expression pattern in a log parser without worrying about escape characters.
**Snippet**:
```cpp
std::string pattern = R"((\d{4})-(\d{2})-(\d{2}))";
std::string multiline = R"(Line 1
Line 2
Line 3)";
```
**Example**: [raw_string_literals.cpp](../examples/C++11/raw_string_literals.cpp)

## Trailing Return Types (C++11 Addition)
**Explanation**: A syntax using `auto` and `->` to specify the return type after the parameter list, essential when the return type depends on parameter types in template functions.
**Real-World Scenario**: Write a generic add function where the return type depends on the types of the operands.
**Snippet**:
```cpp
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
```
**Example**: [trailing_return_types.cpp](../examples/C++11/trailing_return_types.cpp)

## extern template (C++11 Addition)
**Explanation**: Prevents implicit instantiation of a template in a translation unit, reducing compilation time by declaring that the instantiation exists elsewhere.
**Real-World Scenario**: Speed up build times in a large project by instantiating `std::vector<std::string>` in one source file and using `extern template` in all headers.
**Snippet**:
```cpp
// header.h
extern template class std::vector<std::string>; // suppress instantiation here

// source.cpp
template class std::vector<std::string>; // explicit instantiation here
```
**Example**: [extern_template.cpp](../examples/C++11/extern_template.cpp)

## thread_local Storage (C++11 Addition)
**Explanation**: The `thread_local` storage specifier declares variables with thread-local storage duration, meaning each thread gets its own independent copy of the variable.
**Real-World Scenario**: Maintain per-thread error codes or per-thread caches in a multi-threaded server without synchronization overhead.
**Snippet**:
```cpp
thread_local int errorCode = 0;

void processRequest() {
    errorCode = doWork(); // each thread has its own errorCode
}
```
**Example**: [thread_local.cpp](../examples/C++11/thread_local.cpp)

## char16_t/char32_t (C++11 Addition)
**Explanation**: New character types `char16_t` and `char32_t` provide guaranteed-width types for UTF-16 and UTF-32 encoded characters, enabling portable Unicode handling.
**Real-World Scenario**: Process internationalized text data from a database that stores content in UTF-16 encoding.
**Snippet**:
```cpp
char16_t c16 = u'A';       // UTF-16 character
char32_t c32 = U'\U0001F600'; // UTF-32 character (emoji)
```
**Example**: [char16_char32.cpp](../examples/C++11/char16_char32.cpp)

## Unicode String Literals (C++11 Addition)
**Explanation**: New string literal prefixes `u8`, `u`, and `U` create strings encoded in UTF-8, UTF-16, and UTF-32 respectively, providing explicit control over string encoding.
**Real-World Scenario**: Define multi-language UI strings with guaranteed encoding for an internationalized application.
**Snippet**:
```cpp
const char* utf8 = u8"Hello \u00E9";           // UTF-8
const char16_t* utf16 = u"Hello \u00E9";       // UTF-16
const char32_t* utf32 = U"Hello \U0001F600";   // UTF-32
```
**Example**: [unicode_string_literals.cpp](../examples/C++11/unicode_string_literals.cpp)

## Inheriting Constructors (C++11 Addition)
**Explanation**: A derived class can inherit all constructors from a base class using a `using` declaration, eliminating the need to manually write forwarding constructors.
**Real-World Scenario**: Extend a base widget class in a UI framework without rewriting all its constructor overloads.
**Snippet**:
```cpp
class Base {
public:
    Base(int x) {}
    Base(int x, int y) {}
};
class Derived : public Base {
    using Base::Base; // inherits all Base constructors
};
```
**Example**: [inheriting_constructors.cpp](../examples/C++11/inheriting_constructors.cpp)

## Unrestricted Unions (C++11 Addition)
**Explanation**: Unions can now contain members with non-trivial constructors, destructors, and copy/move operations, though the programmer must manually manage construction and destruction of such members.
**Real-World Scenario**: Implement a variant-like type that can hold either a string or a numeric value in a memory-efficient tagged union.
**Snippet**:
```cpp
union Variant {
    int num;
    std::string str;
    Variant() : num(0) {}
    ~Variant() {} // must manually manage non-trivial members
};
```
**Example**: [unrestricted_unions.cpp](../examples/C++11/unrestricted_unions.cpp)

## std::thread (C++11 Addition)
**Explanation**: Provides a portable, standard way to create and manage threads, replacing platform-specific threading APIs.
**Real-World Scenario**: Offload a heavy file compression task to a background thread to keep the UI responsive.
**Snippet**:
```cpp
#include <thread>
void compress(const std::string& file) { /* ... */ }
std::thread t(compress, "data.bin");
t.join();
```
**Example**: [thread.cpp](../examples/C++11/thread.cpp)

## std::mutex (C++11 Addition)
**Explanation**: A synchronization primitive that provides mutual exclusion, ensuring only one thread accesses a shared resource at a time.
**Real-World Scenario**: Protect a shared log file from concurrent writes in a multi-threaded server.
**Snippet**:
```cpp
#include <mutex>
std::mutex mtx;
void safeWrite(const std::string& msg) {
    mtx.lock();
    // write to shared resource
    mtx.unlock();
}
```
**Example**: [mutex.cpp](../examples/C++11/mutex.cpp)

## std::lock_guard (C++11 Addition)
**Explanation**: A RAII wrapper that acquires a mutex on construction and releases it on destruction, guaranteeing the mutex is always released even if an exception occurs.
**Real-World Scenario**: Safely update a shared counter in a multi-threaded hit counter without risking deadlocks from forgotten unlocks.
**Snippet**:
```cpp
#include <mutex>
std::mutex mtx;
void increment(int& counter) {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter; // mutex released when lock goes out of scope
}
```
**Example**: [lock_guard.cpp](../examples/C++11/lock_guard.cpp)

## std::unique_lock (C++11 Addition)
**Explanation**: A flexible RAII mutex wrapper that supports deferred locking, timed locking, recursive locking, and transfer of lock ownership. More versatile than `std::lock_guard`.
**Real-World Scenario**: Implement a timed lock on a shared resource that gives up if the lock is not acquired within a deadline.
**Snippet**:
```cpp
#include <mutex>
std::mutex mtx;
void timedAccess() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    if (lock.try_lock()) {
        // access shared resource
    }
}
```
**Example**: [unique_lock.cpp](../examples/C++11/unique_lock.cpp)

## std::condition_variable (C++11 Addition)
**Explanation**: A synchronization primitive that allows threads to wait until a condition is met, enabling producer-consumer patterns and other thread coordination scenarios.
**Real-World Scenario**: Implement a thread-safe task queue where worker threads sleep until new tasks arrive.
**Snippet**:
```cpp
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    // proceed with work
}
```
**Example**: [condition_variable.cpp](../examples/C++11/condition_variable.cpp)

## std::atomic (C++11 Addition)
**Explanation**: Provides lock-free atomic operations on fundamental types, enabling safe concurrent access without mutexes for simple shared variables.
**Real-World Scenario**: Implement a thread-safe reference counter or a shared flag indicating shutdown in a multi-threaded application.
**Snippet**:
```cpp
#include <atomic>
std::atomic<int> counter(0);

void increment() {
    counter.fetch_add(1, std::memory_order_relaxed);
}
```
**Example**: [atomic.cpp](../examples/C++11/atomic.cpp)

## Memory Model (C++11 Addition)
**Explanation**: C++11 defines a formal memory model that specifies how threads interact through memory, including ordering guarantees such as `memory_order_relaxed`, `memory_order_acquire`, `memory_order_release`, and `memory_order_seq_cst`.
**Real-World Scenario**: Build a lock-free single-producer single-consumer queue using acquire/release semantics for correct inter-thread communication.
**Snippet**:
```cpp
#include <atomic>
std::atomic<bool> flag(false);
int data = 0;

void producer() {
    data = 42;
    flag.store(true, std::memory_order_release);
}
void consumer() {
    while (!flag.load(std::memory_order_acquire)) {}
    assert(data == 42); // guaranteed by acquire/release
}
```
**Example**: [memory_model.cpp](../examples/C++11/memory_model.cpp)

## std::future (C++11 Addition)
**Explanation**: Represents a value that will be available in the future, providing a mechanism to retrieve the result of an asynchronous operation.
**Real-World Scenario**: Submit a database query asynchronously and retrieve the results when they are ready.
**Snippet**:
```cpp
#include <future>
std::future<int> fut = std::async(std::launch::async, [] { return 42; });
int result = fut.get(); // blocks until ready
```
**Example**: [future.cpp](../examples/C++11/future.cpp)

## std::promise (C++11 Addition)
**Explanation**: A mechanism for a thread to set a value or exception that can be retrieved by an associated `std::future`, providing explicit control over asynchronous result delivery.
**Real-World Scenario**: A worker thread computes a result and delivers it to the main thread through a promise/future pair.
**Snippet**:
```cpp
#include <future>
#include <thread>
std::promise<int> prom;
std::future<int> fut = prom.get_future();

std::thread t([&prom] { prom.set_value(42); });
int result = fut.get(); // 42
t.join();
```
**Example**: [promise.cpp](../examples/C++11/promise.cpp)

## std::async (C++11 Addition)
**Explanation**: Launches a function asynchronously (potentially in a new thread) and returns a `std::future` holding the result, providing the simplest way to run tasks concurrently.
**Real-World Scenario**: Fetch data from multiple remote services in parallel and combine the results.
**Snippet**:
```cpp
#include <future>
auto fut1 = std::async(std::launch::async, fetchFromServiceA);
auto fut2 = std::async(std::launch::async, fetchFromServiceB);
auto result = combine(fut1.get(), fut2.get());
```
**Example**: [async.cpp](../examples/C++11/async.cpp)