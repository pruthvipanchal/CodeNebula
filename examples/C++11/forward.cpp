// CodeNebula - C++11 Example: std::forward Usage Patterns
// Compile: g++ -std=c++11 -Wall -Wextra -o example forward.cpp

// Demonstrates std::forward usage patterns: the key utility for perfect
// forwarding. std::forward conditionally casts to an rvalue reference based
// on the deduced template parameter, preserving the original value category.

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Overloaded receiver to show which overload is called
void receive(const std::string& s)
{
    std::cout << "  receive(const&): \"" << s << "\"" << std::endl;
}

void receive(std::string&& s)
{
    std::cout << "  receive(&&):     \"" << s << "\"" << std::endl;
}

// ------------------------------------------------------------------
// Pattern 1: Single-argument forwarding
// ------------------------------------------------------------------
template <typename T>
void relay(T&& arg)
{
    receive(std::forward<T>(arg));
}

// ------------------------------------------------------------------
// Pattern 2: Forwarding into a container (emplace pattern)
// ------------------------------------------------------------------
template <typename T>
void addToVector(std::vector<std::string>& vec, T&& value)
{
    vec.push_back(std::forward<T>(value));
}

// ------------------------------------------------------------------
// Pattern 3: Forwarding constructor arguments
// ------------------------------------------------------------------
class Wrapper {
    std::string value_;
public:
    template <typename T>
    explicit Wrapper(T&& val) : value_(std::forward<T>(val))
    {
        std::cout << "  Wrapper constructed: \"" << value_ << "\"" << std::endl;
    }
    const std::string& get() const { return value_; }
};

// ------------------------------------------------------------------
// Pattern 4: Forwarding multiple arguments
// ------------------------------------------------------------------
template <typename F, typename... Args>
void invoke(F&& func, Args&&... args)
{
    std::forward<F>(func)(std::forward<Args>(args)...);
}

int main()
{
    // ------------------------------------------------------------------
    // Pattern 1: Value category preservation
    // ------------------------------------------------------------------
    std::cout << "=== Single-argument forwarding ===" << std::endl;
    std::string name = "Alice";
    relay(name);                        // T=string&  -> forward keeps lvalue
    relay(std::string("Bob"));          // T=string   -> forward casts to rvalue
    relay(std::move(name));             // T=string   -> forward casts to rvalue
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Pattern 2: Emplace into container
    // ------------------------------------------------------------------
    std::cout << "=== Forwarding into vector ===" << std::endl;
    std::vector<std::string> vec;
    std::string item = "Lvalue item";
    addToVector(vec, item);                      // copy into vector
    addToVector(vec, std::string("Rvalue item")); // move into vector

    for (const auto& s : vec) {
        std::cout << "  vec: \"" << s << "\"" << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Pattern 3: Forwarding constructor
    // ------------------------------------------------------------------
    std::cout << "=== Forwarding constructor ===" << std::endl;
    std::string data = "Shared";
    Wrapper w1(data);                           // copies data
    Wrapper w2(std::string("Temporary"));       // moves temporary
    std::cout << "  w1: " << w1.get() << std::endl;
    std::cout << "  w2: " << w2.get() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Pattern 4: Forwarding into callable
    // ------------------------------------------------------------------
    std::cout << "=== Forwarding to callable ===" << std::endl;
    auto printer = [](const std::string& a, int b) {
        std::cout << "  printer: \"" << a << "\", " << b << std::endl;
    };

    std::string arg1 = "test";
    invoke(printer, arg1, 42);
    invoke(printer, std::string("temp"), 99);

    // ------------------------------------------------------------------
    // Pattern 5: Why NOT to use std::move when you mean std::forward
    // ------------------------------------------------------------------
    std::cout << std::endl << "=== forward vs move ===" << std::endl;
    std::cout << "  forward: preserves the caller's intent" << std::endl;
    std::cout << "  move:    always casts to rvalue (may steal from lvalues!)" << std::endl;

    return 0;
}

/*
Expected output:

=== Single-argument forwarding ===
  receive(const&): "Alice"
  receive(&&):     "Bob"
  receive(&&):     "Alice"

=== Forwarding into vector ===
  vec: "Lvalue item"
  vec: "Rvalue item"

=== Forwarding constructor ===
  Wrapper constructed: "Shared"
  Wrapper constructed: "Temporary"
  w1: Shared
  w2: Temporary

=== Forwarding to callable ===
  printer: "test", 42
  printer: "temp", 99

=== forward vs move ===
  forward: preserves the caller's intent
  move:    always casts to rvalue (may steal from lvalues!)
*/
