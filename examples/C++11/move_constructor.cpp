// CodeNebula - C++11 Example: Move Constructor Implementation
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_constructor.cpp

// Demonstrates how to implement a move constructor. The move constructor
// transfers ownership of resources from a temporary (rvalue) object,
// leaving the source in a valid but empty state. Essential for the Rule of Five.

#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>

// Real-world scenario: a string class that manages its own memory
class MyString {
    char* data_;
    std::size_t length_;

public:
    // Regular constructor
    MyString(const char* str = "")
        : data_(new char[std::strlen(str) + 1]), length_(std::strlen(str))
    {
        std::strcpy(data_, str);
        std::cout << "  [Ctor]  \"" << data_ << "\"" << std::endl;
    }

    // Copy constructor (deep copy)
    MyString(const MyString& other)
        : data_(new char[other.length_ + 1]), length_(other.length_)
    {
        std::strcpy(data_, other.data_);
        std::cout << "  [Copy]  \"" << data_ << "\"" << std::endl;
    }

    // Move constructor (resource theft - no allocation!)
    MyString(MyString&& other) noexcept
        : data_(other.data_),        // steal the pointer
          length_(other.length_)     // steal the length
    {
        // Leave source in valid empty state
        other.data_ = nullptr;
        other.length_ = 0;
        std::cout << "  [Move]  \"" << data_ << "\"" << std::endl;
    }

    // Copy assignment
    MyString& operator=(const MyString& other)
    {
        if (this != &other) {
            delete[] data_;
            length_ = other.length_;
            data_ = new char[length_ + 1];
            std::strcpy(data_, other.data_);
            std::cout << "  [Copy=] \"" << data_ << "\"" << std::endl;
        }
        return *this;
    }

    // Move assignment
    MyString& operator=(MyString&& other) noexcept
    {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            length_ = other.length_;
            other.data_ = nullptr;
            other.length_ = 0;
            std::cout << "  [Move=] \"" << data_ << "\"" << std::endl;
        }
        return *this;
    }

    // Destructor
    ~MyString()
    {
        std::cout << "  [Dtor]  " << (data_ ? data_ : "(null)") << std::endl;
        delete[] data_;
    }

    const char* c_str() const { return data_ ? data_ : ""; }
    std::size_t length() const { return length_; }
};

// Factory function: return value triggers move
MyString createGreeting(const char* name)
{
    MyString s(name);
    return s;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Move constructor via std::move
    // ------------------------------------------------------------------
    std::cout << "=== Direct move construction ===" << std::endl;
    MyString a("Hello");
    MyString b(std::move(a));   // move constructor
    std::cout << "  b = \"" << b.c_str() << "\"" << std::endl;
    std::cout << "  a = \"" << a.c_str() << "\" (moved-from)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Move constructor from temporary
    // ------------------------------------------------------------------
    std::cout << "=== Move from temporary ===" << std::endl;
    MyString c(MyString("Temporary"));  // may be elided by compiler
    std::cout << "  c = \"" << c.c_str() << "\"" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Move constructor from factory function
    // ------------------------------------------------------------------
    std::cout << "=== Factory return ===" << std::endl;
    MyString d = createGreeting("World");
    std::cout << "  d = \"" << d.c_str() << "\"" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Swap using moves (three moves, zero allocations)
    // ------------------------------------------------------------------
    std::cout << "=== Move-based swap ===" << std::endl;
    MyString x("First");
    MyString y("Second");
    std::cout << "  Before: x=\"" << x.c_str() << "\", y=\"" << y.c_str() << "\"" << std::endl;

    MyString temp(std::move(x));
    x = std::move(y);
    y = std::move(temp);
    std::cout << "  After:  x=\"" << x.c_str() << "\", y=\"" << y.c_str() << "\"" << std::endl;

    std::cout << std::endl << "=== Cleanup ===" << std::endl;
    return 0;
}

/*
Expected output (some moves may be elided by NRVO):

=== Direct move construction ===
  [Ctor]  "Hello"
  [Move]  "Hello"
  b = "Hello"
  a = "" (moved-from)

=== Move from temporary ===
  [Ctor]  "Temporary"
  c = "Temporary"

=== Factory return ===
  [Ctor]  "World"
  d = "World"

=== Move-based swap ===
  [Ctor]  "First"
  [Ctor]  "Second"
  Before: x="First", y="Second"
  [Move]  "First"
  [Move=] "Second"
  [Move=] "First"
  After:  x="Second", y="First"

=== Cleanup ===
  [Dtor]  (null)
  [Dtor]  First
  [Dtor]  Second
  [Dtor]  World
  [Dtor]  (null)
  [Dtor]  Hello
*/
