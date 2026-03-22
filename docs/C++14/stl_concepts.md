# C++14 STL Concepts

This document covers new or evolved C++14 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++14/). Only additions or evolutions from C++98/C++03/C++11 are included.

## Utilities

### std::make_unique
**Explanation**: Creates a `std::unique_ptr` in a single expression, complementing `std::make_shared` from C++11. It eliminates the need for raw `new`, prevents memory leaks in expressions with multiple allocations, and makes ownership semantics explicit at the call site.
**Real-World Scenario**: A plugin system dynamically loads modules at startup. Each module is heap-allocated and owned by a unique pointer, ensuring automatic cleanup when the plugin manager shuts down.
**Snippet**:
```cpp
#include <memory>
#include <iostream>

struct Sensor {
    std::string name;
    Sensor(std::string n) : name(std::move(n)) {
        std::cout << name << " initialized\n";
    }
    ~Sensor() { std::cout << name << " destroyed\n"; }
};

int main() {
    auto temp = std::make_unique<Sensor>("Thermocouple");
    auto accel = std::make_unique<Sensor>("Accelerometer");
    // automatic cleanup in reverse order
}
```
**Example**: [make_unique.cpp](../examples/C++14/make_unique.cpp)

### std::quoted
**Explanation**: A stream manipulator that wraps a string in quotation marks on output and parses quoted strings (handling embedded escapes) on input. It uses a configurable delimiter and escape character, defaulting to `"` and `\\`.
**Real-World Scenario**: A CSV exporter needs to emit fields that may contain commas or spaces. Wrapping them with `std::quoted` ensures they are properly delimited and can be round-tripped back through an input stream.
**Snippet**:
```cpp
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string original = "Hello, \"World\"!";

    // Output with quotes and escaping
    std::cout << std::quoted(original) << "\n";
    // prints: "Hello, \"World\"!"

    // Round-trip through a stream
    std::stringstream ss;
    ss << std::quoted(original);

    std::string restored;
    ss >> std::quoted(restored);
    std::cout << restored << "\n"; // Hello, "World"!
}
```
**Example**: [quoted.cpp](../examples/C++14/quoted.cpp)

### std::exchange
**Explanation**: Replaces the value of an object with a new value and returns the old value in a single atomic-looking expression. It simplifies move constructors, state-machine transitions, and any pattern where you need the previous state before overwriting it.
**Real-World Scenario**: A state machine for a network connection transitions between states. `std::exchange` captures the previous state for logging while atomically updating to the new state.
**Snippet**:
```cpp
#include <utility>
#include <iostream>
#include <string>

enum class State { Idle, Connecting, Connected, Disconnected };

const char* to_string(State s) {
    switch (s) {
        case State::Idle:         return "Idle";
        case State::Connecting:   return "Connecting";
        case State::Connected:    return "Connected";
        case State::Disconnected: return "Disconnected";
    }
    return "Unknown";
}

int main() {
    State current = State::Idle;

    State prev = std::exchange(current, State::Connecting);
    std::cout << to_string(prev) << " -> " << to_string(current) << "\n";
    // Idle -> Connecting

    prev = std::exchange(current, State::Connected);
    std::cout << to_string(prev) << " -> " << to_string(current) << "\n";
    // Connecting -> Connected
}
```
**Example**: [exchange.cpp](../examples/C++14/exchange.cpp)

### std::integer_sequence / index_sequence / make_index_sequence / index_sequence_for
**Explanation**: `std::integer_sequence<T, Ints...>` represents a compile-time sequence of integers. The aliases `std::index_sequence`, `std::make_index_sequence<N>`, and `std::index_sequence_for<Types...>` provide convenient ways to generate sequences of `std::size_t` values. These are essential building blocks for tuple unpacking, variadic template expansion, and compile-time iteration.
**Real-World Scenario**: A lightweight dependency-injection framework stores constructor arguments in a tuple and needs to unpack them in order when invoking the constructor. `std::index_sequence` enables the expansion.
**Snippet**:
```cpp
#include <tuple>
#include <iostream>
#include <utility>

template<typename Tuple, std::size_t... Is>
void print_impl(const Tuple& t, std::index_sequence<Is...>) {
    ((std::cout << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
    std::cout << "\n";
}

template<typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    print_impl(t, std::index_sequence_for<Args...>{});
}

int main() {
    auto data = std::make_tuple(42, 3.14, "hello");
    print_tuple(data); // 42, 3.14, hello
}
```
**Example**: [integer_sequence.cpp](../examples/C++14/integer_sequence.cpp)

### std::get&lt;Type&gt;() for Tuples
**Explanation**: Access tuple elements by their type instead of by index using `std::get<T>()`. Each type in the tuple must be unique for this overload to compile. This makes code more readable and less fragile when tuple layouts change.
**Real-World Scenario**: A multi-sensor reading is stored as a tuple of distinct measurement types. Retrieving values by type is clearer than remembering positional indices, especially as new sensor channels are added.
**Snippet**:
```cpp
#include <tuple>
#include <iostream>
#include <string>

int main() {
    using SensorReading = std::tuple<double, int, std::string>;
    SensorReading reading{36.6, 98, "normal"};

    double temperature = std::get<double>(reading);
    int    heart_rate  = std::get<int>(reading);
    auto&  status      = std::get<std::string>(reading);

    std::cout << "Temp: " << temperature
              << " HR: " << heart_rate
              << " Status: " << status << "\n";
}
```
**Example**: [get_type_tuple.cpp](../examples/C++14/get_type_tuple.cpp)

## Container Improvements

### Heterogeneous Lookup for map/set/unordered_map/unordered_set
**Explanation**: Associative containers with a transparent comparator (one that defines `is_transparent`) can now perform lookups with keys of different types, avoiding the construction of temporary key objects. For ordered containers like `std::map` and `std::set`, passing a comparator such as `std::less<>` enables this. For unordered containers, a transparent hash and key-equal are required (full support standardized in C++20, but the mechanism originates here).
**Real-World Scenario**: A web server stores route handlers in a `std::map<std::string, Handler>`. With heterogeneous lookup, incoming `const char*` or `std::string_view` request paths can be searched without allocating a temporary `std::string` for every request.
**Snippet**:
```cpp
#include <map>
#include <string>
#include <iostream>
#include <functional>

int main() {
    // std::less<> is a transparent comparator
    std::map<std::string, int, std::less<>> word_count;
    word_count["hello"] = 5;
    word_count["world"] = 3;

    // Lookup with const char* — no temporary std::string created
    const char* key = "hello";
    auto it = word_count.find(key);
    if (it != word_count.end())
        std::cout << it->first << ": " << it->second << "\n"; // hello: 5
}
```
**Example**: [heterogeneous_lookup.cpp](../examples/C++14/heterogeneous_lookup.cpp)

### Transparent Operator Functors (std::less<>, std::greater<>)
**Explanation**: The standard comparison functors (`std::less`, `std::greater`, `std::equal_to`, etc.) now have a `void` specialization (e.g., `std::less<>`) that is a transparent comparator. It defines `is_transparent` and uses a templated `operator()`, enabling heterogeneous comparison without constructing temporaries. This is the enabler for heterogeneous lookup in associative containers.
**Real-World Scenario**: A sorted set of file paths stored as `std::string` needs frequent lookups from C-style strings received from a POSIX API. Using `std::less<>` lets the set compare directly against `const char*`.
**Snippet**:
```cpp
#include <set>
#include <string>
#include <iostream>
#include <functional>

int main() {
    std::set<std::string, std::less<>> files;
    files.insert("/etc/hosts");
    files.insert("/var/log/syslog");
    files.insert("/tmp/data.csv");

    // Lookup with const char* — no std::string temporary
    if (files.count("/var/log/syslog"))
        std::cout << "Found syslog\n";

    // Works with std::greater<> too
    std::set<int, std::greater<>> descending = {3, 1, 4, 1, 5};
    for (int v : descending) std::cout << v << " "; // 5 4 3 1
    std::cout << "\n";
}
```
**Example**: [transparent_functors.cpp](../examples/C++14/transparent_functors.cpp)

## Type Traits

### std::is_final
**Explanation**: A compile-time type trait that evaluates to `true` if a class is declared `final` (cannot be inherited from). This is useful in template metaprogramming to select optimized implementations — for example, using the Empty Base Optimization (EBO) only when a type is not final.
**Real-World Scenario**: A generic compressed-pair implementation (like the one inside many standard library `unique_ptr` implementations) checks `std::is_final` to decide whether it can inherit from the deleter type to exploit EBO, or must store it as a member instead.
**Snippet**:
```cpp
#include <type_traits>
#include <iostream>

class Base {};
class Derived final : public Base {};

template<typename T>
void describe() {
    if constexpr (std::is_final<T>::value)
        std::cout << "Type is final — cannot derive from it\n";
    else
        std::cout << "Type is not final — inheritance allowed\n";
}

int main() {
    describe<Base>();    // not final
    describe<Derived>(); // final
}
```
**Example**: [is_final.cpp](../examples/C++14/is_final.cpp)

## Threading

### std::shared_timed_mutex
**Explanation**: A mutex that supports both exclusive (write) and shared (read) ownership, with the ability to specify timeouts via `try_lock_for` and `try_lock_shared_for`. Multiple threads can hold a shared lock simultaneously for reading, while an exclusive lock blocks all other access for writing.
**Real-World Scenario**: A real-time stock ticker serves thousands of reader threads displaying prices while a single writer thread updates quotes from the exchange feed. `std::shared_timed_mutex` maximizes read concurrency while ensuring safe writes, with timeouts preventing reader starvation.
**Snippet**:
```cpp
#include <shared_mutex>
#include <thread>
#include <iostream>
#include <chrono>

std::shared_timed_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    rw_mutex.lock_shared();
    std::cout << "Reader " << id << " sees: " << shared_data << "\n";
    rw_mutex.unlock_shared();
}

void writer(int value) {
    rw_mutex.lock();
    shared_data = value;
    std::cout << "Writer set: " << value << "\n";
    rw_mutex.unlock();
}

int main() {
    std::thread w(writer, 42);
    w.join();
    std::thread r1(reader, 1), r2(reader, 2);
    r1.join(); r2.join();
}
```
**Example**: [shared_timed_mutex.cpp](../examples/C++14/shared_timed_mutex.cpp)

### std::shared_lock
**Explanation**: An RAII lock guard that acquires shared (read) ownership of a `SharedMutex` (typically `std::shared_timed_mutex`). It is the shared-ownership counterpart of `std::unique_lock` and supports deferred locking, timed locking, and manual lock/unlock, all with automatic release on destruction.
**Real-World Scenario**: A DNS cache is read by many resolver threads concurrently. Each reader acquires a `std::shared_lock` for the duration of its lookup, while cache updates use a `std::unique_lock` for exclusive access.
**Snippet**:
```cpp
#include <shared_mutex>
#include <map>
#include <string>
#include <thread>
#include <iostream>
#include <vector>

class DnsCache {
    mutable std::shared_timed_mutex mtx_;
    std::map<std::string, std::string> cache_;
public:
    std::string resolve(const std::string& host) const {
        std::shared_lock<std::shared_timed_mutex> lock(mtx_); // shared read
        auto it = cache_.find(host);
        return it != cache_.end() ? it->second : "NOT_FOUND";
    }

    void update(const std::string& host, const std::string& ip) {
        std::unique_lock<std::shared_timed_mutex> lock(mtx_); // exclusive write
        cache_[host] = ip;
    }
};

int main() {
    DnsCache cache;
    cache.update("example.com", "93.184.216.34");

    std::vector<std::thread> readers;
    for (int i = 0; i < 4; ++i)
        readers.emplace_back([&cache, i] {
            std::cout << "Thread " << i << ": "
                      << cache.resolve("example.com") << "\n";
        });
    for (auto& t : readers) t.join();
}
```
**Example**: [shared_lock.cpp](../examples/C++14/shared_lock.cpp)
