// CodeNebula - C++98 Example: std::allocator
// Compile: g++ -std=c++98 -Wall -Wextra -o example allocator.cpp

#include <iostream>
#include <memory>

int main() {
    std::allocator<int> alloc;

    // Allocate raw memory for 5 ints (no construction)
    int* p = alloc.allocate(5);
    std::cout << "Allocated memory for 5 ints" << std::endl;

    // Construct objects in allocated memory
    for (int i = 0; i < 5; ++i) {
        alloc.construct(p + i, (i + 1) * 10);
    }

    std::cout << "Constructed values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << p[i] << " ";
    }
    std::cout << std::endl;

    // Destroy objects (call destructors)
    for (int i = 0; i < 5; ++i) {
        alloc.destroy(p + i);
    }
    std::cout << "Objects destroyed" << std::endl;

    // Deallocate raw memory
    alloc.deallocate(p, 5);
    std::cout << "Memory deallocated" << std::endl;

    // Allocator properties
    std::cout << "max_size: " << alloc.max_size() << std::endl;

    // Allocator for a custom type
    std::allocator<std::string> salloc;
    std::string* sp = salloc.allocate(1);
    salloc.construct(sp, "Hello, allocator!");
    std::cout << "String: " << *sp << std::endl;
    salloc.destroy(sp);
    salloc.deallocate(sp, 1);

    return 0;
}

// Expected output:
// Allocated memory for 5 ints
// Constructed values: 10 20 30 40 50
// Objects destroyed
// Memory deallocated
// max_size: <platform-dependent large number>
// String: Hello, allocator!
