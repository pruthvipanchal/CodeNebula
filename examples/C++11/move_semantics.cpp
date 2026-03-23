// CodeNebula - C++11 Example: Move Semantics
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_semantics.cpp

// Demonstrates move semantics with std::move and move-aware classes.
// Move semantics transfer ownership of resources instead of copying,
// dramatically improving performance for objects managing heap memory.

#include <iostream>
#include <string>
#include <vector>
#include <utility>

// Real-world scenario: a buffer class that manages dynamic memory
class Buffer {
    int* data_;
    std::size_t size_;
    std::string name_;

public:
    // Constructor
    Buffer(const std::string& name, std::size_t size)
        : data_(new int[size]()), size_(size), name_(name)
    {
        std::cout << "  [Construct] " << name_ << " (size=" << size_ << ")" << std::endl;
        for (std::size_t i = 0; i < size_; ++i) data_[i] = static_cast<int>(i);
    }

    // Copy constructor (expensive: allocates + copies)
    Buffer(const Buffer& other)
        : data_(new int[other.size_]), size_(other.size_), name_(other.name_ + "_copy")
    {
        std::cout << "  [Copy]      " << name_ << " from " << other.name_ << std::endl;
        for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    // Move constructor (cheap: steals resources)
    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_), name_(std::move(other.name_))
    {
        std::cout << "  [Move]      " << name_ << std::endl;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // Destructor
    ~Buffer()
    {
        std::cout << "  [Destroy]   " << (name_.empty() ? "(moved-from)" : name_)
                  << std::endl;
        delete[] data_;
    }

    void print() const
    {
        std::cout << "  " << name_ << ": [";
        for (std::size_t i = 0; i < size_; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]" << std::endl;
    }

    std::size_t size() const { return size_; }
};

// Function that returns a Buffer (benefits from move on return)
Buffer createBuffer(const std::string& name, std::size_t size)
{
    Buffer b(name, size);
    return b;  // move (or NRVO) applies here
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Copy vs move
    // ------------------------------------------------------------------
    std::cout << "=== Copy vs Move ===" << std::endl;
    Buffer original("Original", 5);
    original.print();

    Buffer copied(original);              // copy constructor
    copied.print();

    Buffer moved(std::move(original));    // move constructor
    moved.print();
    std::cout << "  Original size after move: " << original.size() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. std::move with standard library types
    // ------------------------------------------------------------------
    std::cout << "=== std::move with std::string ===" << std::endl;
    std::string src = "Hello, World!";
    std::string dst = std::move(src);
    std::cout << "  dst: \"" << dst << "\"" << std::endl;
    std::cout << "  src after move: \"" << src << "\"" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. std::move with vectors (moves entire internal buffer)
    // ------------------------------------------------------------------
    std::cout << "=== std::move with std::vector ===" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = std::move(v1);
    std::cout << "  v2 size: " << v2.size() << std::endl;
    std::cout << "  v1 size after move: " << v1.size() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Return value optimization with move
    // ------------------------------------------------------------------
    std::cout << "=== Factory function ===" << std::endl;
    Buffer fromFactory = createBuffer("Factory", 3);
    fromFactory.print();
    std::cout << std::endl;

    std::cout << "=== Cleanup ===" << std::endl;
    return 0;
}

/*
Expected output (destructor order may vary, NRVO may elide some moves):

=== Copy vs Move ===
  [Construct] Original (size=5)
  Original: [0, 1, 2, 3, 4]
  [Copy]      Original_copy from Original
  Original_copy: [0, 1, 2, 3, 4]
  [Move]      Original
  Original: [0, 1, 2, 3, 4]
  Original size after move: 0

=== std::move with std::string ===
  dst: "Hello, World!"
  src after move: ""

=== std::move with std::vector ===
  v2 size: 5
  v1 size after move: 0

=== Factory function ===
  [Construct] Factory (size=3)
  Factory: [0, 1, 2]

=== Cleanup ===
  [Destroy]   Factory
  [Destroy]   Original
  [Destroy]   Original_copy
  [Destroy]   (moved-from)
*/
