// CodeNebula - C++11 Example: Perfect Forwarding
// Compile: g++ -std=c++11 -Wall -Wextra -o example perfect_forwarding.cpp

// Demonstrates perfect forwarding with std::forward and universal references.
// Perfect forwarding preserves the value category (lvalue/rvalue) of arguments
// through template layers, enabling efficient factory functions and wrappers.

#include <iostream>
#include <string>
#include <utility>
#include <memory>

// Target class that distinguishes how it receives arguments
class Widget {
    std::string name_;
public:
    Widget(const std::string& name) : name_(name)
    {
        std::cout << "  Widget(const string&): copy \"" << name_ << "\"" << std::endl;
    }

    Widget(std::string&& name) : name_(std::move(name))
    {
        std::cout << "  Widget(string&&): move \"" << name_ << "\"" << std::endl;
    }

    const std::string& name() const { return name_; }
};

// ------------------------------------------------------------------
// 1. Without forwarding: always copies
// ------------------------------------------------------------------
template <typename T>
Widget makeWidgetBad(T arg)
{
    return Widget(arg);   // always an lvalue, never moves
}

// ------------------------------------------------------------------
// 2. With perfect forwarding: preserves value category
// ------------------------------------------------------------------
template <typename T>
Widget makeWidgetGood(T&& arg)   // universal reference (T&&)
{
    return Widget(std::forward<T>(arg));   // forwards as lvalue or rvalue
}

// ------------------------------------------------------------------
// 3. Variadic perfect forwarding (emplace-style factory)
// ------------------------------------------------------------------
template <typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// ------------------------------------------------------------------
// 4. Wrapper that logs and forwards
// ------------------------------------------------------------------
void processImpl(const std::string& s)
{
    std::cout << "  processImpl(const&): \"" << s << "\"" << std::endl;
}

void processImpl(std::string&& s)
{
    std::cout << "  processImpl(&&): \"" << s << "\"" << std::endl;
}

template <typename T>
void logAndProcess(T&& arg)
{
    std::cout << "  [LOG] Processing argument..." << std::endl;
    processImpl(std::forward<T>(arg));   // preserve value category
}

int main()
{
    // ------------------------------------------------------------------
    // Without forwarding (always copies)
    // ------------------------------------------------------------------
    std::cout << "=== Without forwarding ===" << std::endl;
    std::string name = "Alice";
    makeWidgetBad(name);                  // copy (expected)
    makeWidgetBad(std::string("Bob"));    // still copy (bad!)
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // With perfect forwarding
    // ------------------------------------------------------------------
    std::cout << "=== With perfect forwarding ===" << std::endl;
    makeWidgetGood(name);                 // forwards as lvalue -> copy
    makeWidgetGood(std::string("Bob"));   // forwards as rvalue -> move
    makeWidgetGood("Charlie");            // forwards const char* -> copy ctor
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Variadic forwarding (like std::make_unique)
    // ------------------------------------------------------------------
    std::cout << "=== Variadic forwarding ===" << std::endl;
    auto w1 = makeUnique<Widget>(name);
    auto w2 = makeUnique<Widget>(std::string("Eve"));
    std::cout << "  w1->name(): " << w1->name() << std::endl;
    std::cout << "  w2->name(): " << w2->name() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Logging wrapper with forwarding
    // ------------------------------------------------------------------
    std::cout << "=== Log-and-forward wrapper ===" << std::endl;
    std::string msg = "lvalue message";
    logAndProcess(msg);                        // lvalue -> const&
    logAndProcess(std::string("rvalue msg"));  // rvalue -> &&

    return 0;
}

/*
Expected output:

=== Without forwarding ===
  Widget(const string&): copy "Alice"
  Widget(const string&): copy "Bob"

=== With perfect forwarding ===
  Widget(const string&): copy "Alice"
  Widget(string&&): move "Bob"
  Widget(const string&): copy "Charlie"

=== Variadic forwarding ===
  Widget(const string&): copy "Alice"
  Widget(string&&): move "Eve"
  w1->name(): Alice
  w2->name(): Eve

=== Log-and-forward wrapper ===
  [LOG] Processing argument...
  processImpl(const&): "lvalue message"
  [LOG] Processing argument...
  processImpl(&&): "rvalue msg"
*/
