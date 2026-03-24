// CodeNebula - C++20 Example: [[no_unique_address]] Attribute
// Compile: g++ -std=c++20 -Wall -Wextra -o example no_unique_address.cpp

// [[no_unique_address]] allows empty class members to occupy zero bytes,
// enabling the Empty Base Optimization (EBO) for member variables.
// Without it, even an empty class member takes at least 1 byte.

#include <iostream>
#include <functional>
#include <memory>

// An empty class (stateless allocator, comparator, etc.)
struct Empty {};

// Another empty class — a stateless deleter
struct DefaultDeleter {
    void operator()(int* p) const { delete p; }
};

// Without [[no_unique_address]]: empty member wastes space
struct WithoutAttribute {
    int value;
    Empty tag;      // takes at least 1 byte + padding
};

// With [[no_unique_address]]: empty member takes zero bytes
struct WithAttribute {
    int value;
    [[no_unique_address]] Empty tag;  // can overlap with padding
};

// Practical example: compressed pair (like boost::compressed_pair)
template <typename T, typename Tag>
struct CompressedPair {
    T first;
    [[no_unique_address]] Tag second;

    std::size_t total_size() const { return sizeof(*this); }
};

// Simulate unique_ptr with a stateless deleter
template <typename T, typename Deleter = DefaultDeleter>
struct SmartPtr {
    T* ptr = nullptr;
    [[no_unique_address]] Deleter deleter;

    explicit SmartPtr(T* p) : ptr(p) {}
    ~SmartPtr() { if (ptr) deleter(ptr); }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
};

// Stateful vs stateless functors
struct StatelessCompare {
    bool operator()(int a, int b) const { return a < b; }
};

struct StatefulCompare {
    int threshold;
    bool operator()(int a, int b) const { return (a - threshold) < (b - threshold); }
};

template <typename Compare>
struct Container {
    int data[4];
    [[no_unique_address]] Compare comp;
};

int main() {
    std::cout << "=== [[no_unique_address]] for EBO ===\n\n";

    // Size comparison
    std::cout << "sizeof(Empty):            " << sizeof(Empty) << "\n";
    std::cout << "sizeof(int):              " << sizeof(int) << "\n";
    std::cout << "sizeof(WithoutAttribute): " << sizeof(WithoutAttribute) << "\n";
    std::cout << "sizeof(WithAttribute):    " << sizeof(WithAttribute) << "\n\n";

    // Compressed pair saves space with empty types
    CompressedPair<int, Empty> p1{42, {}};
    CompressedPair<int, int>   p2{42, 10};
    std::cout << "CompressedPair<int, Empty> size: " << p1.total_size() << "\n";
    std::cout << "CompressedPair<int, int>   size: " << p2.total_size() << "\n\n";

    // Smart pointer with stateless deleter
    SmartPtr<int> sp(new int{99});
    std::cout << "SmartPtr<int, DefaultDeleter> size: " << sizeof(sp) << "\n";
    std::cout << "Raw pointer size:                   " << sizeof(int*) << "\n";
    std::cout << "SmartPtr value: " << *sp << "\n\n";

    // Container with stateless vs stateful comparator
    Container<StatelessCompare> c1{{1,2,3,4}, {}};
    Container<StatefulCompare>  c2{{1,2,3,4}, {5}};
    std::cout << "Container<StatelessCompare> size: " << sizeof(c1) << "\n";
    std::cout << "Container<StatefulCompare>  size: " << sizeof(c2) << "\n";

    return 0;
}

// Expected output (typical 64-bit platform):
// === [[no_unique_address]] for EBO ===
//
// sizeof(Empty):            1
// sizeof(int):              4
// sizeof(WithoutAttribute): 8
// sizeof(WithAttribute):    4
//
// CompressedPair<int, Empty> size: 4
// CompressedPair<int, int>   size: 8
//
// SmartPtr<int, DefaultDeleter> size: 8
// Raw pointer size:                   8
// SmartPtr value: 99
//
// Container<StatelessCompare> size: 16
// Container<StatefulCompare>  size: 20
