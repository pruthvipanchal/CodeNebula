// CodeNebula - C++11 Example: Move Assignment Operator
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_assignment.cpp

// Demonstrates implementing the move assignment operator. Unlike copy
// assignment, move assignment transfers resources without allocation,
// providing O(1) reassignment for resource-managing classes.

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

// Real-world scenario: a dynamic array class
class DynArray {
    int* data_;
    std::size_t size_;
    std::string tag_;

    void dump(const char* label) const
    {
        std::cout << "  [" << label << "] " << tag_
                  << " (size=" << size_ << ")" << std::endl;
    }

public:
    DynArray(const std::string& tag, std::initializer_list<int> init)
        : data_(new int[init.size()]), size_(init.size()), tag_(tag)
    {
        std::copy(init.begin(), init.end(), data_);
        dump("Ctor");
    }

    // Copy assignment (deep copy)
    DynArray& operator=(const DynArray& other)
    {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
            tag_ = other.tag_ + "_copy";
            dump("Copy=");
        }
        return *this;
    }

    // Move assignment operator
    DynArray& operator=(DynArray&& other) noexcept
    {
        if (this != &other) {
            // 1. Release our current resources
            delete[] data_;

            // 2. Steal the source's resources
            data_ = other.data_;
            size_ = other.size_;
            tag_  = std::move(other.tag_);

            // 3. Leave source in valid empty state
            other.data_ = nullptr;
            other.size_ = 0;

            dump("Move=");
        }
        return *this;
    }

    // Move constructor
    DynArray(DynArray&& other) noexcept
        : data_(other.data_), size_(other.size_), tag_(std::move(other.tag_))
    {
        other.data_ = nullptr;
        other.size_ = 0;
        dump("MoveCtor");
    }

    ~DynArray()
    {
        std::cout << "  [Dtor]     " << (tag_.empty() ? "(empty)" : tag_) << std::endl;
        delete[] data_;
    }

    void print() const
    {
        std::cout << "  " << (tag_.empty() ? "(empty)" : tag_) << ": [";
        for (std::size_t i = 0; i < size_; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]" << std::endl;
    }

    std::size_t size() const { return size_; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Move assignment via std::move
    // ------------------------------------------------------------------
    std::cout << "=== Move assignment ===" << std::endl;
    DynArray a("A", {1, 2, 3});
    DynArray b("B", {10, 20});
    a.print();
    b.print();

    a = std::move(b);   // move assignment: a steals b's resources
    std::cout << "  After a = std::move(b):" << std::endl;
    a.print();
    std::cout << "  b.size() = " << b.size() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Move assignment from temporary (rvalue)
    // ------------------------------------------------------------------
    std::cout << "=== Move from temporary ===" << std::endl;
    DynArray c("C", {100});
    c.print();
    c = DynArray("Temp", {7, 8, 9});   // temporary -> move assignment
    c.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Copy assignment for comparison
    // ------------------------------------------------------------------
    std::cout << "=== Copy assignment (for comparison) ===" << std::endl;
    DynArray d("D", {5, 6});
    DynArray e("E", {50, 60, 70});
    d = e;   // copy assignment: allocates new memory
    d.print();
    e.print();   // e is unchanged
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Chain of move assignments
    // ------------------------------------------------------------------
    std::cout << "=== Chained moves ===" << std::endl;
    DynArray x("X", {1});
    DynArray y("Y", {2});
    DynArray z("Z", {3});
    x = std::move(y);
    y = std::move(z);   // y was moved-from, now gets z's resources
    x.print();
    y.print();
    std::cout << "  z.size() = " << z.size() << std::endl;

    std::cout << std::endl << "=== Cleanup ===" << std::endl;
    return 0;
}

/*
Expected output:

=== Move assignment ===
  [Ctor]     A (size=3)
  [Ctor]     B (size=2)
  A: [1, 2, 3]
  B: [10, 20]
  [Move=]    B (size=2)
  After a = std::move(b):
  B: [10, 20]
  b.size() = 0

=== Move from temporary ===
  [Ctor]     C (size=1)
  C: [100]
  [Ctor]     Temp (size=3)
  [Move=]    Temp (size=3)
  [Dtor]     (empty)
  Temp: [7, 8, 9]

=== Copy assignment (for comparison) ===
  [Ctor]     D (size=2)
  [Ctor]     E (size=3)
  [Copy=]    E_copy (size=3)
  E_copy: [50, 60, 70]
  E: [50, 60, 70]

=== Chained moves ===
  [Ctor]     X (size=1)
  [Ctor]     Y (size=1)
  [Ctor]     Z (size=1)
  [Move=]    Y (size=1)
  [Move=]    Z (size=1)
  Y: [2]
  Z: [3]
  z.size() = 0

=== Cleanup ===
  [Dtor]     (empty)
  [Dtor]     Z
  [Dtor]     Y
  [Dtor]     E
  [Dtor]     E_copy
  [Dtor]     Temp
  [Dtor]     (empty)
  [Dtor]     B
*/
