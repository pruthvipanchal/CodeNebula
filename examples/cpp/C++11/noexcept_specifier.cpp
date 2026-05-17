// CodeNebula - C++11 Example: noexcept Specifier and Operator
// Compile: g++ -std=c++11 -Wall -Wextra -o example noexcept_specifier.cpp

// Demonstrates the noexcept specifier and operator. noexcept promises a
// function won't throw exceptions, enabling compiler optimizations and
// ensuring move operations work correctly with STL containers.

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <utility>

// ------------------------------------------------------------------
// 1. noexcept specifier on functions
// ------------------------------------------------------------------
void safeFunction() noexcept
{
    // Guaranteed not to throw
    std::cout << "  safeFunction: no exceptions possible" << std::endl;
}

void riskyFunction()   // may throw (implicit noexcept(false))
{
    std::cout << "  riskyFunction: might throw" << std::endl;
}

// Conditional noexcept
template <typename T>
void swap_values(T& a, T& b) noexcept(noexcept(T(std::move(a))))
{
    T temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}

// ------------------------------------------------------------------
// 2. Class with noexcept move operations (critical for STL)
// ------------------------------------------------------------------
class Buffer {
    int* data_;
    std::size_t size_;
    std::string tag_;

public:
    Buffer(const std::string& tag, std::size_t n)
        : data_(new int[n]()), size_(n), tag_(tag)
    {
        std::cout << "  [Ctor]  " << tag_ << std::endl;
    }

    // Copy (might throw due to allocation)
    Buffer(const Buffer& o) : data_(new int[o.size_]), size_(o.size_), tag_(o.tag_)
    {
        std::copy(o.data_, o.data_ + size_, data_);
        std::cout << "  [Copy]  " << tag_ << std::endl;
    }

    // Move (noexcept: no allocation, just pointer swap)
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_), tag_(std::move(o.tag_))
    {
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "  [Move]  " << tag_ << std::endl;
    }

    // Move assignment (noexcept)
    Buffer& operator=(Buffer&& o) noexcept
    {
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;  size_ = o.size_;  tag_ = std::move(o.tag_);
            o.data_ = nullptr; o.size_ = 0;
        }
        return *this;
    }

    ~Buffer() { delete[] data_; }
    const std::string& tag() const { return tag_; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. noexcept operator (compile-time query)
    // ------------------------------------------------------------------
    std::cout << "=== noexcept operator ===" << std::endl;
    std::cout << "  noexcept(safeFunction())  : "
              << noexcept(safeFunction()) << std::endl;
    std::cout << "  noexcept(riskyFunction()) : "
              << noexcept(riskyFunction()) << std::endl;
    std::cout << "  noexcept(1 + 2)           : "
              << noexcept(1 + 2) << std::endl;
    std::cout << "  noexcept(new int)         : "
              << noexcept(new int) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. noexcept functions
    // ------------------------------------------------------------------
    std::cout << "=== noexcept functions ===" << std::endl;
    safeFunction();
    riskyFunction();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. noexcept move enables vector optimization
    // ------------------------------------------------------------------
    std::cout << "=== Vector reallocation (noexcept move) ===" << std::endl;
    std::cout << "  With noexcept move, vector uses move during realloc:" << std::endl;
    std::vector<Buffer> vec;
    vec.reserve(2);
    vec.emplace_back("A", 10);
    vec.emplace_back("B", 10);
    std::cout << "  -- Triggering reallocation --" << std::endl;
    vec.emplace_back("C", 10);   // reallocation: moves A,B (not copies!)
    std::cout << std::endl;

    std::cout << "  Vector contents:" << std::endl;
    for (const auto& b : vec) {
        std::cout << "    " << b.tag() << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Type traits for noexcept
    // ------------------------------------------------------------------
    std::cout << "=== Move noexcept traits ===" << std::endl;
    std::cout << "  is_nothrow_move_constructible<Buffer>: "
              << std::is_nothrow_move_constructible<Buffer>::value << std::endl;
    std::cout << "  is_nothrow_move_constructible<string>: "
              << std::is_nothrow_move_constructible<std::string>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Conditional noexcept with swap
    // ------------------------------------------------------------------
    std::cout << "=== Conditional noexcept ===" << std::endl;
    int a = 1, b = 2;
    swap_values(a, b);
    std::cout << "  After swap: a=" << a << ", b=" << b << std::endl;
    std::cout << "  noexcept(swap_values(a,b)): "
              << noexcept(swap_values(a, b)) << std::endl;

    return 0;
}

/*
Expected output:

=== noexcept operator ===
  noexcept(safeFunction())  : 1
  noexcept(riskyFunction()) : 0
  noexcept(1 + 2)           : 1
  noexcept(new int)         : 0

=== noexcept functions ===
  safeFunction: no exceptions possible
  riskyFunction: might throw

=== Vector reallocation (noexcept move) ===
  With noexcept move, vector uses move during realloc:
  [Ctor]  A
  [Ctor]  B
  -- Triggering reallocation --
  [Ctor]  C
  [Move]  A
  [Move]  B

  Vector contents:
    A
    B
    C

=== Move noexcept traits ===
  is_nothrow_move_constructible<Buffer>: 1
  is_nothrow_move_constructible<string>: 1

=== Conditional noexcept ===
  After swap: a=2, b=1
  noexcept(swap_values(a,b)): 1
*/
